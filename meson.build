project('game', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17', 
    '@0@=@1@/install'.format('prefix', meson.source_root())])

install_path = '@0@/install/bin'.format(meson.source_root())

cpp = meson.get_compiler('cpp')
sdl2_main_lib = cpp.find_library('SDL2main', dirs: 'C:\\devlibraries\\SDL2-2.0.16\\lib\\x64')
sdl2_lib = cpp.find_library('SDL2', dirs: 'C:\\devlibraries\\SDL2-2.0.16\\lib\\x64')
sdl2_include = include_directories('C:\\devlibraries\\SDL2-2.0.16\\include')
sdl2_img_lib = cpp.find_library('SDL2_image', dirs: 'C:\\devlibraries\\SDL2_image-2.0.5\\lib\\x64')
sdl2_img_include = include_directories('C:\\devlibraries\\SDL2_image-2.0.5\\include')

sdl2_dep = declare_dependency(
    dependencies: [sdl2_lib, sdl2_main_lib, sdl2_img_lib],
    include_directories: [sdl2_include, sdl2_img_include]
)

lua_lib = cpp.find_library('lua51', dirs: 'C:\\devlibraries\\luajit_2.0.5\\lib')
lua_include = include_directories('C:\\devlibraries\\luajit_2.0.5\\include')

lua_dep = declare_dependency(
  dependencies: [lua_lib],
  include_directories: [lua_include]
)

base_include = include_directories('include')

executable(
    'Game',
    ['src/Window.cpp',
  'src/glad.cpp',
  'src/Systems/SpriteRender.cpp',
  'src/Shader.cpp',
  'src/Scene.cpp',
  'src/Window.cpp',
  'src/main.cpp',
  'src/ShaderManager.cpp',
  'src/Renderer/Renderable.cpp',
  'src/Input/InputHandler.cpp'],
    include_directories: [base_include, sdl2_include, sdl2_img_include, lua_include],
    dependencies: [sdl2_lib, sdl2_main_lib, sdl2_img_lib, lua_dep],
    win_subsystem: 'console',
    install: true)

configure_file(
    input : 'C:\\devlibraries\\SDL2-2.0.16\\lib\\x64\\SDL2.dll',
    output : 'SDL2.dll',
    copy: true,
    install: true,
    install_dir: install_path)

configure_file(
    input : 'C:\\devlibraries\\luajit_2.0.5\\lua51.dll',
    output : 'lua51.dll',
    copy: true,
    install: true,
    install_dir: install_path)

configure_file(
    input : 'C:\\devlibraries\\SDL2_image-2.0.5\\lib\\x64\\SDL2_image.dll',
    output : 'SDL2_image.dll',
    copy: true,
    install: true,
    install_dir: install_path)

configure_file(
    input : 'C:\\devlibraries\\SDL2_image-2.0.5\\lib\\x64\\zlib1.dll',
    output : 'zlib1.dll',
    copy: true,
    install: true,
    install_dir: install_path)

configure_file(
    input : 'C:\\devlibraries\\SDL2_image-2.0.5\\lib\\x64\\libpng16-16.dll',
    output : 'libpng16-16.dll',
    copy: true,
    install: true,
    install_dir: install_path)

configure_file(
    input : 'C:\\repos\\engine\\data\\shaders\\dynamicSprite.glsl',
    output : 'dynamicSprite.glsl',
    copy: true,
    install: true,
    install_dir: install_path)

configure_file(
    input : 'C:\\repos\\engine\\data\\shaders\\staticSprite.glsl',
    output : 'staticSprite.glsl',
    copy: true,
    install: true,
    install_dir: install_path)