project(
  'enginelib', 
  'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

add_project_arguments('-DDLLDIR_EX=true', language : 'cpp')

cpp = meson.get_compiler('cpp')
sdl2_lib = cpp.find_library('SDL2', dirs: 'C:\\development\\SDL2-2.0.16\\lib\\x64')
sdl2_include = include_directories('C:\\development\\SDL2-2.0.16\\include')

sdl2_img_lib = cpp.find_library('SDL2_image', dirs: 'C:\\development\\SDL2_image-2.0.5\\lib\\x64')
sdl2_img_include = include_directories('C:\\development\\SDL2_image-2.0.5\\include')

sdl2_dep = declare_dependency(
    dependencies: [sdl2_lib, sdl2_img_lib],
    include_directories: [sdl2_include, sdl2_img_include]
)

lua_lib = cpp.find_library('lua51', dirs: 'C:\\development\\luajit_2.0.5\\lib')
lua_include = include_directories('C:\\development\\luajit_2.0.5\\include')

lua_dep = declare_dependency(
  dependencies: [lua_lib],
  include_directories: [lua_include]
)

engine_include = include_directories('include')
lib = shared_library(
  'Engine',
  ['src/Window.cpp',
  'src/glad.cpp'],
  include_directories : [engine_include, sdl2_include, sdl2_img_include, lua_include],
  dependencies: [sdl2_lib, sdl2_img_lib, lua_lib],
  install : true)

engine_dep = declare_dependency(
    dependencies: [sdl2_lib, sdl2_img_lib, lua_lib],
    include_directories : [engine_include],
    link_with : [lib])