cmake_minimum_required(VERSION 2.6)

project(Vectorial)

add_definitions(-DDEBUG)

set_property( GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")
set(HEADER_FILES "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_FILES main.cpp )
set(DATA_FILES "CMakeLists.txt")
set(LIBRARIES)
set(ENGINE_PATH "${PROJECT_SOURCE_DIR}/external/KTEngine")

set(HEADER_FILES  ${HEADER_FILES} )
set(LIBRARIES ${LIBRARIES} )
set(SOURCE_FILES ${SOURCE_FILES} )


if(WIN32)
    set(HEADER_FILES  ${HEADER_FILES} "${PROJECT_SOURCE_DIR}/external/KTEngine/include/" "${PROJECT_SOURCE_DIR}/external/KTEngine/external/")
    #KTEngine libraries, static linking
    add_library(KTEngine_static STATIC IMPORTED GLOBAL)
    set_target_properties(KTEngine_static PROPERTIES
    IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/external/KTEngine/KTEngine.lib")
ELSEIF(UNIX)
   add_subdirectory(${ENGINE_PATH} KTEngine)

ENDIF(WIN32)


add_definitions(-DRESOURCE_PATH="${PROJECT_SOURCE_DIR}/Resources/")
add_subdirectory(src)



include_directories( ${HEADER_FILES} )

set_source_files_properties("CMakeLists.txt" PROPERTIES HEADER_FILE_ONLY TRUE)

add_executable(Vectorial ${SOURCE_FILES} ${DATA_FILES})
target_link_libraries(Vectorial ${LIBRARIES})