# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/oop_practice/practical-tools-for-simple-design/lib/sdl2"
  "C:/oop_practice/oop_game/_deps/sdl2-build"
  "C:/oop_practice/oop_game/_deps/sdl2-subbuild/sdl2-populate-prefix"
  "C:/oop_practice/oop_game/_deps/sdl2-subbuild/sdl2-populate-prefix/tmp"
  "C:/oop_practice/oop_game/_deps/sdl2-subbuild/sdl2-populate-prefix/src/sdl2-populate-stamp"
  "C:/oop_practice/oop_game/_deps/sdl2-subbuild/sdl2-populate-prefix/src"
  "C:/oop_practice/oop_game/_deps/sdl2-subbuild/sdl2-populate-prefix/src/sdl2-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/oop_practice/oop_game/_deps/sdl2-subbuild/sdl2-populate-prefix/src/sdl2-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/oop_practice/oop_game/_deps/sdl2-subbuild/sdl2-populate-prefix/src/sdl2-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
