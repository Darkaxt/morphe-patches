#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <dlfcn.h>
#include <vector>
#include <android/log.h>

#include "arm64_hook.h"
#include "hud_draw.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "DJMod", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "DJMod", __VA_ARGS__)

// ============================================================================
// 1. Proxy forwarding to libDoodleJump_orig.so (12 JNI exports, zero-overhead)
// ============================================================================
static void* g_orig_handle = nullptr;
static uintptr_t g_base = 0;

extern "C" __attribute__((visibility("hidden"))) void* g_jni_ptrs[12] = {};

#define DEFINE_JNI_PROXY(IDX, NAME)                                            \
    extern "C" __attribute__((visibility("default"), naked)) void NAME() {     \
        asm volatile(                                                          \
            "adrp x16, g_jni_ptrs\n"                                           \
            "add  x16, x16, :lo12:g_jni_ptrs\n"                                \
            "ldr  x16, [x16, #" #IDX "*8]\n"                                   \
            "br   x16\n"                                                       \
        );                                                                     \
    }

DEFINE_JNI_PROXY(0,  Java_com_limasky_doodlejumpandroid_MainApplication_initializeNativeAudio)
DEFINE_JNI_PROXY(1,  Java_com_limasky_doodlejumpandroid_AdsMediationManager_isAudioMuted)
DEFINE_JNI_PROXY(2,  Java_com_limasky_doodlejumpandroid_AudioTrack_readAndDecodeOgg)
DEFINE_JNI_PROXY(3,  Java_com_limasky_doodlejumpandroid_MainApplication_setUpBreakpad)
DEFINE_JNI_PROXY(4,  Java_com_limasky_doodlejumpandroid_Util_plca)
DEFINE_JNI_PROXY(5,  Java_com_limasky_doodlejumpandroid_NotificationCenter_updateScheduler)
DEFINE_JNI_PROXY(6,  Java_com_limasky_doodlejumpandroid_NotificationCenter_sendMessageNative)
DEFINE_JNI_PROXY(7,  Java_com_limasky_doodlejumpandroid_NotificationCenter_runGameLoopNative)
DEFINE_JNI_PROXY(8,  Java_com_limasky_doodlejumpandroid_NotificationCenter_initSensors)
DEFINE_JNI_PROXY(9,  Java_com_limasky_doodlejumpandroid_NotificationCenter_surfaceChangedSensors)
DEFINE_JNI_PROXY(10, Java_com_limasky_doodlejumpandroid_NotificationCenter_pauseSensors)
DEFINE_JNI_PROXY(11, Java_com_limasky_doodlejumpandroid_NotificationCenter_resumeSensors)

static const char* kJniNames[12] = {
    "Java_com_limasky_doodlejumpandroid_MainApplication_initializeNativeAudio",
    "Java_com_limasky_doodlejumpandroid_AdsMediationManager_isAudioMuted",
    "Java_com_limasky_doodlejumpandroid_AudioTrack_readAndDecodeOgg",
    "Java_com_limasky_doodlejumpandroid_MainApplication_setUpBreakpad",
    "Java_com_limasky_doodlejumpandroid_Util_plca",
    "Java_com_limasky_doodlejumpandroid_NotificationCenter_updateScheduler",
    "Java_com_limasky_doodlejumpandroid_NotificationCenter_sendMessageNative",
    "Java_com_limasky_doodlejumpandroid_NotificationCenter_runGameLoopNative",
    "Java_com_limasky_doodlejumpandroid_NotificationCenter_initSensors",
    "Java_com_limasky_doodlejumpandroid_NotificationCenter_surfaceChangedSensors",
    "Java_com_limasky_doodlejumpandroid_NotificationCenter_pauseSensors",
    "Java_com_limasky_doodlejumpandroid_NotificationCenter_resumeSensors",
};

// ============================================================================
// 2. Game struct offsets & function RVAs (Doodle Jump 3.11.40 arm64-v8a)
// ============================================================================
namespace offsets {
// Function RVAs (Ghidra VA - 0x100000)
constexpr uintptr_t kRunGameLoopNative = 0x3820c0;
constexpr uintptr_t kResetLevel        = 0x2ee3b0;
constexpr uintptr_t kRecyclePlatform   = 0x2f36b0;
constexpr uintptr_t kUpdateGameplay    = 0x2f5c60;
constexpr uintptr_t kScrollWorld       = 0x2f9c88;
constexpr uintptr_t kTriggerGameOver   = 0x2fb658;
constexpr uintptr_t kCheckCollisions   = 0x2fbeb0;
constexpr uintptr_t kRenderHUD         = 0x30d6ac;
constexpr uintptr_t kCullOffscreen     = 0x30eeb4;
constexpr uintptr_t kPlatformReset     = 0x343bec;
constexpr uintptr_t kPlatformSetType   = 0x343cb8;
constexpr uintptr_t kGetScreenHeight   = 0x3466ac;
constexpr uintptr_t kGetTopInset       = 0x346604;

// Game struct (&DAT_008e6e60) field offsets
constexpr size_t kDt                 = 0x34;   // float
constexpr size_t kPhase              = 0x40;   // int (6 = playing, 7 = gameover, 10 = falling)
constexpr size_t kIsPlaying          = 0x44;   // int
constexpr size_t kIsFallingDead      = 0x90;   // int
constexpr size_t kDoodlerY           = 0x6f0;  // float (screen space Y, 0 = bottom)
constexpr size_t kIsFalling          = 0x6f4;  // int
constexpr size_t kDoodlerVy          = 0x6f8;  // float
constexpr size_t kScore              = 0x740;  // float
constexpr size_t kScreenRectPtr      = 0x73a8; // float* [x, y, w, h]
constexpr size_t kWorldY             = 0x73c8; // float
constexpr size_t kIsBlackHole        = 0x73f0; // int
constexpr size_t kIsAbductedUFO      = 0x73f4; // int
constexpr size_t kIsHitMonsterDizzy  = 0x73f8; // int
constexpr size_t kIsHitOtherHazard   = 0x73fc; // int
constexpr size_t kDeathAnimState     = 0x740c; // int
constexpr size_t kPlatformsBegin     = 0x74d0; // void**
constexpr size_t kPlatformsEnd       = 0x74d8; // void**
constexpr size_t kPlatformsCap       = 0x74e0; // void**
constexpr size_t kPoolBegin          = 0x74e8; // void**
constexpr size_t kPoolEnd            = 0x74f0; // void**
constexpr size_t kProtectedPlatform  = 0x8580; // void*

// PlatformObject field offsets
constexpr size_t kPlatType      = 0x50; // int (0=green, 1=moving, 2=brown, 10=white, ...)
constexpr size_t kPlatMoveMode  = 0x60; // int
constexpr size_t kPlatX         = 0x64; // float
constexpr size_t kPlatY         = 0x68; // float (screen space Y)
constexpr size_t kPlatMoveSpeed = 0x78; // float
constexpr size_t kPlatBroken    = 0x90; // int (non-zero if broken/destroyed)
} // namespace offsets

template <typename T>
inline T& field(void* base, size_t off) {
    return *reinterpret_cast<T*>(static_cast<uint8_t*>(base) + off);
}

// ============================================================================
// 3. Mod configuration & runtime state
// ============================================================================
static constexpr int   kMaxLives            = 3;
static constexpr float kLowerScrollY        = 150.0f; // Scroll camera down when falling below this Y
static constexpr float kFloorBounceY        = 28.0f;  // Starting floor bounce height at worldY == 0
static constexpr float kNormalJumpVy        = 9.0f;   // Vanilla jump impulse (0x41100000)
static constexpr float kFallDamage1LifeDist = 750.0f; // ~1.5 screens -> -1 life
static constexpr float kFallDamage2LifeDist = 1750.0f;// ~3.5 screens -> -2 lives
static constexpr float kInvulnDuration      = 2.0f;   // Invulnerability after monster/UFO hit

struct SavedPlatform {
    float worldY;
    float x;
    int   type;
    int   moveMode;
    float moveSpeed;
};

static std::vector<SavedPlatform> g_belowScreen;
static int   g_lives          = kMaxLives;
static float g_peakScore      = 0.0f;
static float g_invulnTimer    = 0.0f;
static float g_damageFlash    = 0.0f;
static bool  g_scrollingDown  = false;
static bool  g_trackingFall   = false;
static float g_fallStartWorld = 0.0f;
static bool  g_gameOverArmed  = false;

// Original / helper function pointers
using VoidGameFn        = void (*)(void*);
using RenderHudFn       = void (*)(void*, int);
using ScrollWorldFn     = void (*)(void*, float);
using RecyclePlatformFn = void (*)(void*, void*);
using PlatformResetFn   = void (*)(void*);
using PlatformSetTypeFn = void (*)(void*, int);
using GetFloatFn        = float (*)();

static VoidGameFn        orig_resetLevel      = nullptr;
static VoidGameFn        orig_updateGameplay  = nullptr;
static VoidGameFn        orig_cullOffscreen   = nullptr;
static VoidGameFn        orig_checkCollisions = nullptr;
static RenderHudFn       orig_renderHUD       = nullptr;
static VoidGameFn        orig_triggerGameOver = nullptr;

static ScrollWorldFn     fn_scrollWorld       = nullptr;
static RecyclePlatformFn fn_recyclePlatform   = nullptr;
static PlatformResetFn   fn_platformReset     = nullptr;
static PlatformSetTypeFn fn_platformSetType   = nullptr;
static GetFloatFn        fn_getScreenHeight   = nullptr;
static GetFloatFn        fn_getTopInset       = nullptr;

// ============================================================================
// 4. Platform vector / pool helpers
// ============================================================================
static void insert_platform_front(void* game, void* plat) {
    auto*& begin = field<void**>(game, offsets::kPlatformsBegin);
    auto*& end   = field<void**>(game, offsets::kPlatformsEnd);
    auto*& cap   = field<void**>(game, offsets::kPlatformsCap);

    size_t count = static_cast<size_t>(end - begin);
    size_t capacity = static_cast<size_t>(cap - begin);

    if (count >= capacity) {
        // Safety: if vector is at capacity, avoid raw allocator mismatch — just don't overflow.
        // In practice we free top platforms before restoring bottom ones, so count < capacity.
        fn_recyclePlatform(game, plat);
        return;
    }

    if (count > 0) {
        std::memmove(begin + 1, begin, count * sizeof(void*));
    }
    begin[0] = plat;
    end = begin + count + 1;
}

static void* pop_platform_from_pool(void* game) {
    auto*& pool_begin = field<void**>(game, offsets::kPoolBegin);
    auto*& pool_end   = field<void**>(game, offsets::kPoolEnd);
    if (pool_end <= pool_begin) return nullptr;
    pool_end -= 1;
    return *pool_end;
}

static void scroll_down_with_history(void* game, float scroll_down) {
    g_scrollingDown = true;

    // 1. Shift world objects UP by +scroll_down, and reduce worldY & score by -scroll_down.
    fn_scrollWorld(game, -scroll_down);

    // 2. Free platforms that scrolled above the top of the screen back into the pool.
    float* rect = field<float*>(game, offsets::kScreenRectPtr);
    float screen_top = rect ? (rect[1] + rect[3]) : 540.0f;

    auto*& begin = field<void**>(game, offsets::kPlatformsBegin);
    auto*& end   = field<void**>(game, offsets::kPlatformsEnd);
    void* protected_plat = field<void*>(game, offsets::kProtectedPlatform);

    while ((end - begin) > 1) {
        void* top_plat = *(end - 1);
        if (top_plat == protected_plat) break;
        float py = field<float>(top_plat, offsets::kPlatY);
        if (py > screen_top + 30.0f) {
            end -= 1;
            fn_recyclePlatform(game, top_plat);
        } else {
            break;
        }
    }

    // 3. Restore previous platforms from g_belowScreen as they re-enter from the bottom.
    float cur_world_y = field<float>(game, offsets::kWorldY);
    int restored = 0;
    while (!g_belowScreen.empty() && restored < 24) {
        const SavedPlatform& sp = g_belowScreen.back();
        if (sp.worldY < cur_world_y - 6.0f) {
            break;
        }
        void* p = pop_platform_from_pool(game);
        if (!p) break;

        fn_platformReset(p);
        fn_platformSetType(p, sp.type);
        field<float>(p, offsets::kPlatX)         = sp.x;
        field<float>(p, offsets::kPlatY)         = sp.worldY - cur_world_y;
        field<int>(p, offsets::kPlatMoveMode)    = sp.moveMode;
        field<float>(p, offsets::kPlatMoveSpeed) = sp.moveSpeed;

        insert_platform_front(game, p);
        g_belowScreen.pop_back();
        restored++;
    }

    g_scrollingDown = false;
}

static void apply_fall_damage(void* game, int dmg) {
    if (dmg <= 0 || g_lives <= 0) return;
    g_lives = std::max(0, g_lives - dmg);
    g_damageFlash = 0.6f;
    LOGI("Fall damage: -%d life (remaining: %d)", dmg, g_lives);
    if (g_lives <= 0) {
        g_gameOverArmed = true;
        orig_triggerGameOver(game);
    }
}

// ============================================================================
// 5. Hooks
// ============================================================================
static void hook_resetLevel(void* game) {
    g_belowScreen.clear();
    g_lives          = kMaxLives;
    g_peakScore      = 0.0f;
    g_invulnTimer    = 0.0f;
    g_damageFlash    = 0.0f;
    g_scrollingDown  = false;
    g_trackingFall   = false;
    g_fallStartWorld = 0.0f;
    g_gameOverArmed  = false;
    LOGI("Level reset -> lives=%d", g_lives);
    orig_resetLevel(game);
}

static void hook_cullOffscreen(void* game) {
    if (g_scrollingDown) {
        return;
    }

    // Snapshot platforms about to be culled by vanilla FUN_0040eeb4 (y < -6.0f)
    void** begin = field<void**>(game, offsets::kPlatformsBegin);
    void** end   = field<void**>(game, offsets::kPlatformsEnd);
    void* protected_plat = field<void*>(game, offsets::kProtectedPlatform);
    float cur_world_y = field<float>(game, offsets::kWorldY);

    int scanned = 0;
    for (void** it = begin; it < end && scanned < 25; ++it, ++scanned) {
        void* p = *it;
        if (!p || p == protected_plat) continue;
        float py = field<float>(p, offsets::kPlatY);
        if (py >= -6.0f) break;

        int type = field<int>(p, offsets::kPlatType);
        int broken = field<int>(p, offsets::kPlatBroken);
        // Do not save already-broken brown platforms
        if (type == 2 && broken != 0) continue;

        SavedPlatform sp;
        sp.worldY    = cur_world_y + py;
        sp.x         = field<float>(p, offsets::kPlatX);
        sp.type      = type;
        sp.moveMode  = field<int>(p, offsets::kPlatMoveMode);
        sp.moveSpeed = field<float>(p, offsets::kPlatMoveSpeed);

        // Keep history monotonic (avoid duplicate entries if anything oscillates)
        if (g_belowScreen.empty() || sp.worldY >= g_belowScreen.back().worldY - 1.0f) {
            g_belowScreen.push_back(sp);
        }
    }

    orig_cullOffscreen(game);
}

static void hook_updateGameplay(void* game) {
    float dt = field<float>(game, offsets::kDt);
    if (dt <= 0.0f || dt > 0.25f) dt = 1.0f / 60.0f;

    if (g_invulnTimer > 0.0f) g_invulnTimer = std::max(0.0f, g_invulnTimer - dt);
    if (g_damageFlash > 0.0f) g_damageFlash = std::max(0.0f, g_damageFlash - dt);

    int phase        = field<int>(game, offsets::kPhase);
    int is_playing   = field<int>(game, offsets::kIsPlaying);
    int falling_dead = field<int>(game, offsets::kIsFallingDead);
    int black_hole   = field<int>(game, offsets::kIsBlackHole);

    if (phase == 6 && is_playing == 1 && falling_dead == 0 && black_hole == 0 && !g_gameOverArmed) {
        float& dy = field<float>(game, offsets::kDoodlerY);
        float& vy = field<float>(game, offsets::kDoodlerVy);
        float& wy = field<float>(game, offsets::kWorldY);

        // 1. Downward camera scroll when falling below kLowerScrollY
        if (dy < kLowerScrollY && vy < 0.0f && wy > 0.0f) {
            float want_down = kLowerScrollY - dy;
            float scroll_down = std::min(want_down, wy);
            if (scroll_down > 0.0f) {
                dy += scroll_down;
                scroll_down_with_history(game, scroll_down);
            }
        }

        // 2. Starting floor bounce at worldY == 0
        if (wy <= 1.0f && dy < kFloorBounceY && vy < 0.0f) {
            if (g_trackingFall) {
                float fall_dist = g_fallStartWorld - (wy + dy);
                g_trackingFall = false;
                if (fall_dist > kFallDamage2LifeDist) {
                    apply_fall_damage(game, 2);
                } else if (fall_dist > kFallDamage1LifeDist) {
                    apply_fall_damage(game, 1);
                }
            }
            if (g_lives > 0 && !g_gameOverArmed) {
                dy = kFloorBounceY;
                vy = kNormalJumpVy;
                field<int>(game, offsets::kIsFalling) = 0;
            }
        }
    }

    orig_updateGameplay(game);

    // Post-tick: clamp score >= 0, track peak score, detect platform landings for fall damage
    float& score = field<float>(game, offsets::kScore);
    if (score < 0.0f) score = 0.0f;
    if (score > g_peakScore) g_peakScore = score;

    if (field<int>(game, offsets::kPhase) == 6 &&
        field<int>(game, offsets::kIsPlaying) == 1 &&
        field<int>(game, offsets::kIsFallingDead) == 0 &&
        field<int>(game, offsets::kIsBlackHole) == 0 &&
        !g_gameOverArmed) {
        float dy = field<float>(game, offsets::kDoodlerY);
        float vy = field<float>(game, offsets::kDoodlerVy);
        float wy = field<float>(game, offsets::kWorldY);

        if (vy < 0.0f) {
            if (!g_trackingFall) {
                g_trackingFall = true;
                g_fallStartWorld = wy + dy;
            }
        } else if (vy > 0.0f && g_trackingFall) {
            float fall_dist = g_fallStartWorld - (wy + dy);
            g_trackingFall = false;
            if (fall_dist > kFallDamage2LifeDist) {
                apply_fall_damage(game, 2);
            } else if (fall_dist > kFallDamage1LifeDist) {
                apply_fall_damage(game, 1);
            }
        }
    }
}

static void hook_checkCollisions(void* game) {
    int prev_monster = field<int>(game, offsets::kIsHitMonsterDizzy);
    int prev_ufo     = field<int>(game, offsets::kIsAbductedUFO);
    int prev_other   = field<int>(game, offsets::kIsHitOtherHazard);

    orig_checkCollisions(game);

    // Black Holes always end the run immediately
    if (field<int>(game, offsets::kIsBlackHole) != 0) {
        return;
    }

    int now_monster = field<int>(game, offsets::kIsHitMonsterDizzy);
    int now_ufo     = field<int>(game, offsets::kIsAbductedUFO);
    int now_other   = field<int>(game, offsets::kIsHitOtherHazard);

    bool new_hit = (prev_monster == 0 && now_monster != 0) ||
                   (prev_ufo     == 0 && now_ufo     != 0) ||
                   (prev_other   == 0 && now_other   != 0);

    if (!new_hit) return;

    auto cancel_ko = [&]() {
        field<int>(game, offsets::kIsHitMonsterDizzy) = 0;
        field<int>(game, offsets::kIsAbductedUFO)     = 0;
        field<int>(game, offsets::kIsHitOtherHazard)  = 0;
        field<int>(game, offsets::kDeathAnimState)    = 0;
        field<int>(game, offsets::kIsPlaying)         = 1;
        field<int>(game, offsets::kIsFalling)         = 0;
        field<float>(game, offsets::kDoodlerVy)       = kNormalJumpVy;
        // Clear dizzy stars / stun timers set by monster hit
        field<int>(game, 0x8eb8) = 0;
        field<int>(game, 0x9140) = 0;
        field<int>(game, 0x95e4) = 0;
        g_trackingFall = false;
    };

    if (g_invulnTimer > 0.0f) {
        cancel_ko();
        return;
    }

    g_lives = std::max(0, g_lives - 1);
    g_damageFlash = 0.6f;
    LOGI("Monster/UFO hit -> -1 life (remaining: %d)", g_lives);

    if (g_lives > 0) {
        g_invulnTimer = kInvulnDuration;
        cancel_ko();
    }
    // If g_lives == 0, leave the vanilla KO flag set so Game Over triggers normally
}

static void hook_triggerGameOver(void* game) {
    float& score = field<float>(game, offsets::kScore);
    if (g_peakScore > score) {
        score = g_peakScore;
    }
    orig_triggerGameOver(game);
}

static void hook_renderHUD(void* game, int flag) {
    orig_renderHUD(game, flag);

    int phase = field<int>(game, offsets::kPhase);
    if (phase == 6 || phase == 10) {
        float* rect = field<float*>(game, offsets::kScreenRectPtr);
        float screen_left  = rect ? rect[0] : 0.0f;
        float screen_width = rect ? rect[2] : 320.0f;
        float screen_h     = fn_getScreenHeight ? fn_getScreenHeight() : 533.0f;
        float top_inset    = fn_getTopInset ? fn_getTopInset() : 0.0f;

        hud_draw::render_overlay(
            g_lives, kMaxLives, static_cast<int>(g_peakScore),
            screen_left, screen_width, screen_h, top_inset,
            g_invulnTimer, g_damageFlash);
    }
}

// ============================================================================
// 6. Constructor: load libDoodleJump_orig.so & install all 6 hooks
// ============================================================================
__attribute__((constructor))
static void djmod_init() {
    g_orig_handle = dlopen("libDoodleJump_orig.so", RTLD_NOW | RTLD_GLOBAL);
    if (!g_orig_handle) {
        LOGE("dlopen(libDoodleJump_orig.so) failed: %s", dlerror());
        return;
    }

    for (int i = 0; i < 12; ++i) {
        g_jni_ptrs[i] = dlsym(g_orig_handle, kJniNames[i]);
        if (!g_jni_ptrs[i]) {
            LOGE("dlsym(%s) failed", kJniNames[i]);
        }
    }

    if (!g_jni_ptrs[7]) {
        LOGE("Cannot compute libDoodleJump_orig.so base address");
        return;
    }

    g_base = reinterpret_cast<uintptr_t>(g_jni_ptrs[7]) - offsets::kRunGameLoopNative;
    LOGI("libDoodleJump_orig.so loaded at base=0x%lx", static_cast<unsigned long>(g_base));

    fn_scrollWorld     = reinterpret_cast<ScrollWorldFn>(g_base + offsets::kScrollWorld);
    fn_recyclePlatform = reinterpret_cast<RecyclePlatformFn>(g_base + offsets::kRecyclePlatform);
    fn_platformReset   = reinterpret_cast<PlatformResetFn>(g_base + offsets::kPlatformReset);
    fn_platformSetType = reinterpret_cast<PlatformSetTypeFn>(g_base + offsets::kPlatformSetType);
    fn_getScreenHeight = reinterpret_cast<GetFloatFn>(g_base + offsets::kGetScreenHeight);
    fn_getTopInset     = reinterpret_cast<GetFloatFn>(g_base + offsets::kGetTopInset);

    bool ok = true;
    ok &= arm64_hook::install(reinterpret_cast<void*>(g_base + offsets::kResetLevel),      hook_resetLevel,      &orig_resetLevel);
    ok &= arm64_hook::install(reinterpret_cast<void*>(g_base + offsets::kUpdateGameplay),  hook_updateGameplay,  &orig_updateGameplay);
    ok &= arm64_hook::install(reinterpret_cast<void*>(g_base + offsets::kCullOffscreen),   hook_cullOffscreen,   &orig_cullOffscreen);
    ok &= arm64_hook::install(reinterpret_cast<void*>(g_base + offsets::kCheckCollisions), hook_checkCollisions, &orig_checkCollisions);
    ok &= arm64_hook::install(reinterpret_cast<void*>(g_base + offsets::kRenderHUD),       hook_renderHUD,       &orig_renderHUD);
    ok &= arm64_hook::install(reinterpret_cast<void*>(g_base + offsets::kTriggerGameOver), hook_triggerGameOver, &orig_triggerGameOver);

    LOGI("DJMod hooks installed: %s", ok ? "ALL OK" : "SOME FAILED");
}
