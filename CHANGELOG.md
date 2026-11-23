## [1.1.0-dev.4](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.3...v1.1.0-dev.4) (2026-11-23)

### ✨ New Features

* **doodlejump:** fix pool exhaustion, monster knockback, Game Over transition, top-bar HUD, and +1 life per 10k pts ([390df2e](https://github.com/Darkaxt/morphe-patches/commit/390df2ecf94b9d5fd355b580ff530770f302f6b7))
* **doodlejump:** render life icons using the active theme's Doodler sprite ([8d0e9dc](https://github.com/Darkaxt/morphe-patches/commit/8d0e9dc082c347e94e007bd6d923e0031839edc4))

### 🐛 Bug Fixes

* **doodlejump:** bridge post-pattern vertical gaps immediately off-top instead of after delay ([71a475e](https://github.com/Darkaxt/morphe-patches/commit/71a475e2e92d2b3f8925a4fe25224045a06bdf71))
* **doodlejump:** bridge unreachable >130-unit vertical platform gaps during climbing and falling ([55799d9](https://github.com/Darkaxt/morphe-patches/commit/55799d98f729e04f2fdde1393edbb401ebd83f40))
* **doodlejump:** end run immediately at 0 lives on monster/UFO KO and restore GLES texture/env state ([a575b96](https://github.com/Darkaxt/morphe-patches/commit/a575b96d21120da730fc7871f8666a522d653ff1))
* **doodlejump:** handle all theme special platforms/hazards polymorphically via vtable across all 17 themes ([bffc3c4](https://github.com/Darkaxt/morphe-patches/commit/bffc3c4d3af9a419361bcfaac36106c1e3d969bf))
* **doodlejump:** link libc++ statically so libDoodleJump.so has no libc++_shared.so dependency ([320246e](https://github.com/Darkaxt/morphe-patches/commit/320246e6a2c3b7d4b8e97ef16fc8d26b32731266))
* **doodlejump:** preserve sorted platform history and prevent empty-screen gaps on fall ([e526860](https://github.com/Darkaxt/morphe-patches/commit/e526860eed1ea85d31fd6d4d88b9051f44283f12))
* **doodlejump:** read active theme Doodler sprite from game+0x9010 table ([d197355](https://github.com/Darkaxt/morphe-patches/commit/d19735515271f2931125b711a1bb95598c89f21d))
* **doodlejump:** recognize Winter icicle platforms, prevent platform/monster overlap, and keep top edge populated ([e94f74d](https://github.com/Darkaxt/morphe-patches/commit/e94f74d6224a27b41b2593fe5911ef363c363e63))
* **doodlejump:** recover +1 life per 10,000 clean climb since last damage ([a0bf18f](https://github.com/Darkaxt/morphe-patches/commit/a0bf18f17bee5b13c511dc95bf75c06919c2b28b))

## [1.1.0-dev.4](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.3...v1.1.0-dev.4) (2026-11-23)

### ✨ New Features

* **doodlejump:** fix pool exhaustion, monster knockback, Game Over transition, top-bar HUD, and +1 life per 10k pts ([390df2e](https://github.com/Darkaxt/morphe-patches/commit/390df2ecf94b9d5fd355b580ff530770f302f6b7))
* **doodlejump:** render life icons using the active theme's Doodler sprite ([8d0e9dc](https://github.com/Darkaxt/morphe-patches/commit/8d0e9dc082c347e94e007bd6d923e0031839edc4))

### 🐛 Bug Fixes

* **doodlejump:** bridge post-pattern vertical gaps immediately off-top instead of after delay ([71a475e](https://github.com/Darkaxt/morphe-patches/commit/71a475e2e92d2b3f8925a4fe25224045a06bdf71))
* **doodlejump:** bridge unreachable >130-unit vertical platform gaps during climbing and falling ([55799d9](https://github.com/Darkaxt/morphe-patches/commit/55799d98f729e04f2fdde1393edbb401ebd83f40))
* **doodlejump:** end run immediately at 0 lives on monster/UFO KO and restore GLES texture/env state ([a575b96](https://github.com/Darkaxt/morphe-patches/commit/a575b96d21120da730fc7871f8666a522d653ff1))
* **doodlejump:** link libc++ statically so libDoodleJump.so has no libc++_shared.so dependency ([320246e](https://github.com/Darkaxt/morphe-patches/commit/320246e6a2c3b7d4b8e97ef16fc8d26b32731266))
* **doodlejump:** preserve sorted platform history and prevent empty-screen gaps on fall ([e526860](https://github.com/Darkaxt/morphe-patches/commit/e526860eed1ea85d31fd6d4d88b9051f44283f12))
* **doodlejump:** read active theme Doodler sprite from game+0x9010 table ([d197355](https://github.com/Darkaxt/morphe-patches/commit/d19735515271f2931125b711a1bb95598c89f21d))
* **doodlejump:** recognize Winter icicle platforms, prevent platform/monster overlap, and keep top edge populated ([e94f74d](https://github.com/Darkaxt/morphe-patches/commit/e94f74d6224a27b41b2593fe5911ef363c363e63))
* **doodlejump:** recover +1 life per 10,000 clean climb since last damage ([a0bf18f](https://github.com/Darkaxt/morphe-patches/commit/a0bf18f17bee5b13c511dc95bf75c06919c2b28b))

## [1.1.0-dev.4](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.3...v1.1.0-dev.4) (2026-11-23)

### ✨ New Features

* **doodlejump:** fix pool exhaustion, monster knockback, Game Over transition, top-bar HUD, and +1 life per 10k pts ([390df2e](https://github.com/Darkaxt/morphe-patches/commit/390df2ecf94b9d5fd355b580ff530770f302f6b7))
* **doodlejump:** render life icons using the active theme's Doodler sprite ([8d0e9dc](https://github.com/Darkaxt/morphe-patches/commit/8d0e9dc082c347e94e007bd6d923e0031839edc4))

### 🐛 Bug Fixes

* **doodlejump:** bridge post-pattern vertical gaps immediately off-top instead of after delay ([71a475e](https://github.com/Darkaxt/morphe-patches/commit/71a475e2e92d2b3f8925a4fe25224045a06bdf71))
* **doodlejump:** bridge unreachable >130-unit vertical platform gaps during climbing and falling ([55799d9](https://github.com/Darkaxt/morphe-patches/commit/55799d98f729e04f2fdde1393edbb401ebd83f40))
* **doodlejump:** end run immediately at 0 lives on monster/UFO KO and restore GLES texture/env state ([a575b96](https://github.com/Darkaxt/morphe-patches/commit/a575b96d21120da730fc7871f8666a522d653ff1))
* **doodlejump:** link libc++ statically so libDoodleJump.so has no libc++_shared.so dependency ([320246e](https://github.com/Darkaxt/morphe-patches/commit/320246e6a2c3b7d4b8e97ef16fc8d26b32731266))
* **doodlejump:** preserve sorted platform history and prevent empty-screen gaps on fall ([e526860](https://github.com/Darkaxt/morphe-patches/commit/e526860eed1ea85d31fd6d4d88b9051f44283f12))
* **doodlejump:** read active theme Doodler sprite from game+0x9010 table ([d197355](https://github.com/Darkaxt/morphe-patches/commit/d19735515271f2931125b711a1bb95598c89f21d))
* **doodlejump:** recover +1 life per 10,000 clean climb since last damage ([a0bf18f](https://github.com/Darkaxt/morphe-patches/commit/a0bf18f17bee5b13c511dc95bf75c06919c2b28b))

## [1.1.0-dev.4](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.3...v1.1.0-dev.4) (2026-11-23)

### ✨ New Features

* **doodlejump:** fix pool exhaustion, monster knockback, Game Over transition, top-bar HUD, and +1 life per 10k pts ([390df2e](https://github.com/Darkaxt/morphe-patches/commit/390df2ecf94b9d5fd355b580ff530770f302f6b7))
* **doodlejump:** render life icons using the active theme's Doodler sprite ([8d0e9dc](https://github.com/Darkaxt/morphe-patches/commit/8d0e9dc082c347e94e007bd6d923e0031839edc4))

### 🐛 Bug Fixes

* **doodlejump:** bridge unreachable >130-unit vertical platform gaps during climbing and falling ([55799d9](https://github.com/Darkaxt/morphe-patches/commit/55799d98f729e04f2fdde1393edbb401ebd83f40))
* **doodlejump:** end run immediately at 0 lives on monster/UFO KO and restore GLES texture/env state ([a575b96](https://github.com/Darkaxt/morphe-patches/commit/a575b96d21120da730fc7871f8666a522d653ff1))
* **doodlejump:** link libc++ statically so libDoodleJump.so has no libc++_shared.so dependency ([320246e](https://github.com/Darkaxt/morphe-patches/commit/320246e6a2c3b7d4b8e97ef16fc8d26b32731266))
* **doodlejump:** preserve sorted platform history and prevent empty-screen gaps on fall ([e526860](https://github.com/Darkaxt/morphe-patches/commit/e526860eed1ea85d31fd6d4d88b9051f44283f12))
* **doodlejump:** read active theme Doodler sprite from game+0x9010 table ([d197355](https://github.com/Darkaxt/morphe-patches/commit/d19735515271f2931125b711a1bb95598c89f21d))
* **doodlejump:** recover +1 life per 10,000 clean climb since last damage ([a0bf18f](https://github.com/Darkaxt/morphe-patches/commit/a0bf18f17bee5b13c511dc95bf75c06919c2b28b))

## [1.1.0-dev.4](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.3...v1.1.0-dev.4) (2026-11-23)

### ✨ New Features

* **doodlejump:** fix pool exhaustion, monster knockback, Game Over transition, top-bar HUD, and +1 life per 10k pts ([390df2e](https://github.com/Darkaxt/morphe-patches/commit/390df2ecf94b9d5fd355b580ff530770f302f6b7))
* **doodlejump:** render life icons using the active theme's Doodler sprite ([8d0e9dc](https://github.com/Darkaxt/morphe-patches/commit/8d0e9dc082c347e94e007bd6d923e0031839edc4))

### 🐛 Bug Fixes

* **doodlejump:** end run immediately at 0 lives on monster/UFO KO and restore GLES texture/env state ([a575b96](https://github.com/Darkaxt/morphe-patches/commit/a575b96d21120da730fc7871f8666a522d653ff1))
* **doodlejump:** link libc++ statically so libDoodleJump.so has no libc++_shared.so dependency ([320246e](https://github.com/Darkaxt/morphe-patches/commit/320246e6a2c3b7d4b8e97ef16fc8d26b32731266))
* **doodlejump:** preserve sorted platform history and prevent empty-screen gaps on fall ([e526860](https://github.com/Darkaxt/morphe-patches/commit/e526860eed1ea85d31fd6d4d88b9051f44283f12))
* **doodlejump:** read active theme Doodler sprite from game+0x9010 table ([d197355](https://github.com/Darkaxt/morphe-patches/commit/d19735515271f2931125b711a1bb95598c89f21d))
* **doodlejump:** recover +1 life per 10,000 clean climb since last damage ([a0bf18f](https://github.com/Darkaxt/morphe-patches/commit/a0bf18f17bee5b13c511dc95bf75c06919c2b28b))

## [1.1.0-dev.4](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.3...v1.1.0-dev.4) (2026-11-23)

### ✨ New Features

* **doodlejump:** fix pool exhaustion, monster knockback, Game Over transition, top-bar HUD, and +1 life per 10k pts ([390df2e](https://github.com/Darkaxt/morphe-patches/commit/390df2ecf94b9d5fd355b580ff530770f302f6b7))
* **doodlejump:** render life icons using the active theme's Doodler sprite ([8d0e9dc](https://github.com/Darkaxt/morphe-patches/commit/8d0e9dc082c347e94e007bd6d923e0031839edc4))

### 🐛 Bug Fixes

* **doodlejump:** end run immediately at 0 lives on monster/UFO KO and restore GLES texture/env state ([a575b96](https://github.com/Darkaxt/morphe-patches/commit/a575b96d21120da730fc7871f8666a522d653ff1))
* **doodlejump:** link libc++ statically so libDoodleJump.so has no libc++_shared.so dependency ([320246e](https://github.com/Darkaxt/morphe-patches/commit/320246e6a2c3b7d4b8e97ef16fc8d26b32731266))
* **doodlejump:** read active theme Doodler sprite from game+0x9010 table ([d197355](https://github.com/Darkaxt/morphe-patches/commit/d19735515271f2931125b711a1bb95598c89f21d))
* **doodlejump:** recover +1 life per 10,000 clean climb since last damage ([a0bf18f](https://github.com/Darkaxt/morphe-patches/commit/a0bf18f17bee5b13c511dc95bf75c06919c2b28b))

## [1.1.0-dev.4](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.3...v1.1.0-dev.4) (2026-11-23)

### ✨ New Features

* **doodlejump:** fix pool exhaustion, monster knockback, Game Over transition, top-bar HUD, and +1 life per 10k pts ([390df2e](https://github.com/Darkaxt/morphe-patches/commit/390df2ecf94b9d5fd355b580ff530770f302f6b7))
* **doodlejump:** render life icons using the active theme's Doodler sprite ([8d0e9dc](https://github.com/Darkaxt/morphe-patches/commit/8d0e9dc082c347e94e007bd6d923e0031839edc4))

### 🐛 Bug Fixes

* **doodlejump:** link libc++ statically so libDoodleJump.so has no libc++_shared.so dependency ([320246e](https://github.com/Darkaxt/morphe-patches/commit/320246e6a2c3b7d4b8e97ef16fc8d26b32731266))
* **doodlejump:** read active theme Doodler sprite from game+0x9010 table ([d197355](https://github.com/Darkaxt/morphe-patches/commit/d19735515271f2931125b711a1bb95598c89f21d))
* **doodlejump:** recover +1 life per 10,000 clean climb since last damage ([a0bf18f](https://github.com/Darkaxt/morphe-patches/commit/a0bf18f17bee5b13c511dc95bf75c06919c2b28b))

## [1.1.0-dev.4](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.3...v1.1.0-dev.4) (2026-11-23)

### ✨ New Features

* **doodlejump:** fix pool exhaustion, monster knockback, Game Over transition, top-bar HUD, and +1 life per 10k pts ([390df2e](https://github.com/Darkaxt/morphe-patches/commit/390df2ecf94b9d5fd355b580ff530770f302f6b7))
* **doodlejump:** render life icons using the active theme's Doodler sprite ([8d0e9dc](https://github.com/Darkaxt/morphe-patches/commit/8d0e9dc082c347e94e007bd6d923e0031839edc4))

### 🐛 Bug Fixes

* **doodlejump:** link libc++ statically so libDoodleJump.so has no libc++_shared.so dependency ([320246e](https://github.com/Darkaxt/morphe-patches/commit/320246e6a2c3b7d4b8e97ef16fc8d26b32731266))
* **doodlejump:** recover +1 life per 10,000 clean climb since last damage ([a0bf18f](https://github.com/Darkaxt/morphe-patches/commit/a0bf18f17bee5b13c511dc95bf75c06919c2b28b))

## [1.1.0-dev.4](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.3...v1.1.0-dev.4) (2026-11-23)

### ✨ New Features

* **doodlejump:** fix pool exhaustion, monster knockback, Game Over transition, top-bar HUD, and +1 life per 10k pts ([390df2e](https://github.com/Darkaxt/morphe-patches/commit/390df2ecf94b9d5fd355b580ff530770f302f6b7))

### 🐛 Bug Fixes

* **doodlejump:** link libc++ statically so libDoodleJump.so has no libc++_shared.so dependency ([320246e](https://github.com/Darkaxt/morphe-patches/commit/320246e6a2c3b7d4b8e97ef16fc8d26b32731266))
* **doodlejump:** recover +1 life per 10,000 clean climb since last damage ([a0bf18f](https://github.com/Darkaxt/morphe-patches/commit/a0bf18f17bee5b13c511dc95bf75c06919c2b28b))

## [1.1.0-dev.4](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.3...v1.1.0-dev.4) (2026-11-22)

### ✨ New Features

* **doodlejump:** fix pool exhaustion, monster knockback, Game Over transition, top-bar HUD, and +1 life per 10k pts ([390df2e](https://github.com/Darkaxt/morphe-patches/commit/390df2ecf94b9d5fd355b580ff530770f302f6b7))

### 🐛 Bug Fixes

* **doodlejump:** link libc++ statically so libDoodleJump.so has no libc++_shared.so dependency ([320246e](https://github.com/Darkaxt/morphe-patches/commit/320246e6a2c3b7d4b8e97ef16fc8d26b32731266))

## [1.1.0-dev.4](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.3...v1.1.0-dev.4) (2026-11-22)

### 🐛 Bug Fixes

* **doodlejump:** link libc++ statically so libDoodleJump.so has no libc++_shared.so dependency ([320246e](https://github.com/Darkaxt/morphe-patches/commit/320246e6a2c3b7d4b8e97ef16fc8d26b32731266))

## [1.1.0-dev.3](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.2...v1.1.0-dev.3) (2026-11-22)

### 🐛 Bug Fixes

* **doodlejump:** set android:extractNativeLibs=true for newly added native lib ([cd56999](https://github.com/Darkaxt/morphe-patches/commit/cd569993e71daa52eaf6cba9d19dbec9ab189ac1))

## [1.1.0-dev.2](https://github.com/Darkaxt/morphe-patches/compare/v1.1.0-dev.1...v1.1.0-dev.2) (2026-11-22)

### 🐛 Bug Fixes

* **doodlejump:** load bundled mod library from patch bundle classloader ([7335dbd](https://github.com/Darkaxt/morphe-patches/commit/7335dbdd3a119a91b2e3b3511feeadfb9ce27f17))

## [1.1.0-dev.1](https://github.com/Darkaxt/morphe-patches/compare/v1.0.0...v1.1.0-dev.1) (2026-11-22)

### ✨ New Features

* **doodlejump:** add Foldable Seamless Wide View patch with cylindrical wrap-around rendering ([31ce220](https://github.com/Darkaxt/morphe-patches/commit/31ce220f94eb57b606dff28eb6324809758d06df))

### 🐛 Bug Fixes

* remove template example patch ([3af4c48](https://github.com/Darkaxt/morphe-patches/commit/3af4c48b7a141e7e931002fb40610d1a99e2c07f))

## 1.0.0 (2026-11-22)

### ✨ New Features

* **doodlejump:** add Endless Fall & 3-Lives patch ([3535081](https://github.com/Darkaxt/morphe-patches/commit/353508101bac1fb87c0ca96cb21522a073f1f275))
* **doodlejump:** release v1.0.0 with Endless Fall & 3-Lives patch ([99c8ad8](https://github.com/Darkaxt/morphe-patches/commit/99c8ad8188e0940dc511a4a2ce3c33d71d518f4b))

## 1.0.0-dev.1 (2026-11-22)

### ✨ New Features

* **doodlejump:** add Endless Fall & 3-Lives patch ([3535081](https://github.com/Darkaxt/morphe-patches/commit/353508101bac1fb87c0ca96cb21522a073f1f275))
