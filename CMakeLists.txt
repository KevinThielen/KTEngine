cmake_minimum_required(VERSION 2.8.11)
project(KTEngine)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/")
SET(CMAKE_C++_CREATE_STATIC_LIBRARY 1)
SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall")
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Wall -Wno-reorder")

find_package(OpenGL REQUIRED)

#GLEW libraries, static linking
add_library(glew_static STATIC IMPORTED GLOBAL)
set_target_properties(glew_static PROPERTIES
IMPORTED_LOCATION "${KTEngine_SOURCE_DIR}/external/glew/lib/libGLEW.a")

#FREETYPE libraries, static linking
add_library(freetype_static STATIC IMPORTED GLOBAL)
set_target_properties(freetype_static PROPERTIES
IMPORTED_LOCATION "/usr/local/lib/libfreetype.a")

#zlib libraries, static linking
add_library(zlib_static STATIC IMPORTED GLOBAL)
set_target_properties(zlib_static PROPERTIES
IMPORTED_LOCATION "/usr/local/lib/libz.a")


ADD_SUBDIRECTORY(external)
ADD_SUBDIRECTORY(src)

set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)

set(LIBRARIES ${LIBRARIES} glew_static glfw ${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} freetype_static zlib_static PARENT_SCOPE)

