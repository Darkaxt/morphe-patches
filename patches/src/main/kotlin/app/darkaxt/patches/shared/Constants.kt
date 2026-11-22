package app.darkaxt.patches.shared

import app.morphe.patcher.patch.ApkFileType
import app.morphe.patcher.patch.AppTarget
import app.morphe.patcher.patch.Compatibility
import app.morphe.patcher.patch.SupportedAbi

object Constants {
    val COMPATIBILITY_DOODLE_JUMP = Compatibility(
        name = "Doodle Jump",
        packageName = "com.lima.doodlejump",
        apkFileType = ApkFileType.APK,
        appIconColor = 0x7EC850,
        targets = listOf(
            AppTarget(
                version = "3.11.40",
                versionCodes = mapOf(
                    SupportedAbi.ARM64_V8A to 3920090,
                ),
                minSdk = 24,
            ),
        ),
    )
}
