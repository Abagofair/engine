project('game', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17', 
    '@0@=@1@/install'.format('prefix', meson.source_root())])

install_path = '@0@/install/bin'.format(meson.source_root())

cpp = meson.get_compiler('cpp')
sdl2_main_lib = cpp.find_library('SDL2main', dirs: 'C:\\development\\SDL2-2.0.16\\lib\\x64')
sdl2_include = include_directories('C:\\development\\SDL2-2.0.16\\include')
sdl2_img_include = include_directories('C:\\development\\SDL2_image-2.0.5\\include')
sdl2_img_include = include_directories('C:\\development\\SDL2_image-2.0.5\\include')

lua_include = include_directories('C:\\development\\luajit_2.0.5\\include')

enginelib = subproject('engine')
engine_dep = enginelib.get_variable('engine_dep')

executable(
    'Game',
    'src/main.cpp',
    include_directories: [sdl2_include, sdl2_img_include, lua_include],
    dependencies: [sdl2_main_lib, engine_dep],
    win_subsystem: 'console',
    install: true)

configure_file(
    input : 'C:\\development\\SDL2-2.0.16\\lib\\x64\\SDL2.dll',
    output : 'SDL2.dll',
    copy: true,
    install: true,
    install_dir: install_path)

configure_file(
    input : 'C:\\development\\luajit_2.0.5\\lua51.dll',
    output : 'lua51.dll',
    copy: true,
    install: true,
    install_dir: install_path)

configure_file(
    input : 'C:\\development\\SDL2_image-2.0.5\\lib\\x64\\SDL2_image.dll',
    output : 'SDL2_image.dll',
    copy: true,
    install: true,
    install_dir: install_path)

configure_file(
    input : 'C:\\development\\SDL2_image-2.0.5\\lib\\x64\\zlib1.dll',
    output : 'zlib1.dll',
    copy: true,
    install: true,
    install_dir: install_path)

configure_file(
    input : 'C:\\development\\SDL2_image-2.0.5\\lib\\x64\\libpng16-16.dll',
    output : 'libpng16-16.dll',
    copy: true,
    install: true,
    install_dir: install_path)