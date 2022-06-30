1. mkdir build
2. meson setup build && cd build  # pip3 install meson
3. meson  --cross-file=../cross_file.txt 
meson --cross-file=../cross_file.txt \
    -D amdgpu=false \
    -D cairo-tests=false \
    -D etnaviv=false \
    -D exynos=true \
    -D freedreno=false \
    -D freedreno-kgsl=false \
    -D install-test-programs=true \
    -D intel=false \
    -D libkms=false \
    -D man-pages=false \
    -D nouveau=false \
    -D omap=false \
    -D radeon=false \
    -D tegra=false \
    -D udev=false \
    -D valgrind=false  -D vc4=false -D vmwgfx=false
4. ninja
