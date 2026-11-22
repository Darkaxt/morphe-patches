package app.darkaxt.patches.doodlejump

import app.darkaxt.patches.shared.Constants.COMPATIBILITY_DOODLE_JUMP
import app.morphe.patcher.patch.PatchException
import app.morphe.patcher.patch.patch
import app.morphe.patcher.patch.resourceFile

private const val LIB_PATH = "lib/arm64-v8a/libDoodleJump.so"
private const val ORIG_LIB_PATH = "lib/arm64-v8a/libDoodleJump_orig.so"
private const val BUNDLED_MOD_RESOURCE = "doodlejump/arm64-v8a/libDoodleJump.so"

@Suppress("unused")
val endlessFallPatch = patch(
    name = "Endless Fall & 3-Lives",
    description = "Replaces instant fall-death with continuous falling onto previous platforms " +
        "with live score reduction, adds a 3-lives HUD system with balanced fall damage and " +
        "monster/UFO damage with brief invulnerability, and tracks Peak Score. " +
        "Black Holes remain instant Game Over.",
    default = true,
) {
    compatibleWith(COMPATIBILITY_DOODLE_JUMP)

    execute {
        val targetLib = resourceFile(LIB_PATH)
        if (!targetLib.exists()) {
            throw PatchException("$LIB_PATH not found in APK (arm64-v8a APK required).")
        }

        val origLib = resourceFile(ORIG_LIB_PATH, copy = false)
        origLib.parentFile?.mkdirs()
        targetLib.copyTo(origLib, overwrite = true)

        val modStream = this::class.java.classLoader
            ?.getResourceAsStream(BUNDLED_MOD_RESOURCE)
            ?: throw PatchException("Bundled mod library $BUNDLED_MOD_RESOURCE not found.")

        modStream.use { input ->
            targetLib.outputStream().use { output ->
                input.copyTo(output)
            }
        }
    }
}
