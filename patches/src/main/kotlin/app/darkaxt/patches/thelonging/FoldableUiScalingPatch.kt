package app.darkaxt.patches.thelonging

import app.darkaxt.patches.shared.Constants.COMPATIBILITY_THE_LONGING
import app.morphe.patcher.patch.PatchException
import app.morphe.patcher.patch.patch
import app.morphe.patcher.patch.resourceFile
import app.morphe.patcher.patch.resourceXml

private const val IL2CPP_LIB_PATH = "lib/arm64-v8a/libil2cpp.so"

// Unique 20-byte ARM64 sequence in UnityEngine.UI.CanvasScaler::HandleScaleWithScreenSize:
//   ldr  w8, [x19, #0x34]   ; 68 36 40 b9  (m_ScreenMatchMode: 0=MatchWidthOrHeight, 1=Expand, 2=Shrink)
//   cmp  w8, #2             ; 1f 09 00 71
//   b.eq +0xe0              ; 00 07 00 54  (Shrink)
//   cmp  w8, #1             ; 1f 05 00 71
//   b.eq +0xf0              ; 80 07 00 54  (Expand: min(screenW/refW, screenH/refH))
private val CANVAS_SCALER_MATCH_SIG = byteArrayOf(
    0x68, 0x36, 0x40, 0xb9.toByte(),
    0x1f, 0x09, 0x00, 0x71,
    0x00, 0x07, 0x00, 0x54,
    0x1f, 0x05, 0x00, 0x71,
    0x80.toByte(), 0x07, 0x00, 0x54,
)

// Replacement for the first 4 bytes: mov w8, #1 (ScreenMatchMode.Expand)
// - On 16:9 and 21:9 screens: min(screenW/refW, screenH/refH) == screenH/refH (unchanged from vanilla)
// - On 4:3 / unfolded Z Fold screens: min(screenW/refW, screenH/refH) == screenW/refW so books,
//   menus, and dialogs fit cleanly inside the horizontal width without left/right clipping.
private val MOV_W8_1 = byteArrayOf(0x28, 0x00, 0x80.toByte(), 0x52)

private fun findBytes(haystack: ByteArray, needle: ByteArray): Int {
    outer@ for (i in 0..(haystack.size - needle.size)) {
        for (j in needle.indices) {
            if (haystack[i + j] != needle[j]) continue@outer
        }
        return i
    }
    return -1
}

@Suppress("unused")
val foldableUiScalingPatch = patch(
    name = "Fix 4:3 / Foldable UI Scaling",
    description = "Switches Unity CanvasScaler to Expand mode (min of width/height scale) so " +
        "books, menus, and UI panels fit cleanly on 4:3 tablets and unfolded foldables (such as " +
        "Galaxy Z Fold) without left/right clipping, while keeping 16:9 and 21:9 screens unchanged.",
    default = true,
) {
    compatibleWith(COMPATIBILITY_THE_LONGING)

    execute {
        val libFile = resourceFile(IL2CPP_LIB_PATH)
        if (!libFile.exists()) {
            throw PatchException("$IL2CPP_LIB_PATH not found in APK (arm64-v8a APK required).")
        }

        val bytes = libFile.readBytes()
        val off = findBytes(bytes, CANVAS_SCALER_MATCH_SIG)
        if (off < 0) {
            throw PatchException("CanvasScaler::HandleScaleWithScreenSize signature not found in $IL2CPP_LIB_PATH.")
        }

        System.arraycopy(MOV_W8_1, 0, bytes, off, MOV_W8_1.size)
        libFile.writeBytes(bytes)

        resourceXml("AndroidManifest.xml").use { manifest ->
            val app = manifest.root.children("application").firstOrNull()
                ?: throw PatchException("No <application> element found in AndroidManifest.xml.")
            app.setAttribute("android:extractNativeLibs", "true")
        }
    }
}
