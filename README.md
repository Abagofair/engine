setup

vcpkg
    - vcpkg install SDL2:x64-windows
    - vcpkg install SDL2-image:x64-windows

cmake
    - msvc, clang-cl, amd64, lldb
    - OPTIONS: -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake
    --verbose