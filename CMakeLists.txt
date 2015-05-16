cmake_minimum_required(VERSION 2.8.11)
project(KTEngine)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/")
Set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/build/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build/")

SET(CMAKE_C++_CREATE_STATIC_LIBRARY 1)
SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall")
SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Wall")
#set_property( GLOBAL PROPERTY USE_FOLDERS ON)
add_definitions(-DGLEW_STATIC)


find_package(OpenGL REQUIRED)
#set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

IF(WIN32)

#	IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/glew32s.lib")

#	IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/external/freetype/lib/libfreetype.lib")
	#FREETYPE libraries, static linking
	add_library(freetype_static STATIC IMPORTED GLOBAL)
	set_target_properties(freetype_static PROPERTIES
	IMPORTED_LOCATION ${freetype_path})
ELSEIF(UNIX)
#	set(freetype_path "/usr/local/lib/libfreetype.a")

	find_package(Freetype REQUIRED)
  #  add_library(freetype_static STATIC IMPORTED GLOBAL)
	#set_target_properties(freetype_static PROPERTIES
	#IMPORTED_LOCATION ${freetype_path})

ENDIF(WIN32)
	#GLEW libraries, static linking
	add_library(glew_static STATIC IMPORTED GLOBAL)
	set_target_properties(glew_static PROPERTIES
	IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/libGLEW.a")


set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)



ADD_SUBDIRECTORY(external)
ADD_SUBDIRECTORY(src)

set(HEADER_FILES ${HEADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/external/freetype/include/  PARENT_SCOPE)
set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
set(DATA_FILES ${DATA_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" PARENT_SCOPE)


set_source_files_properties(" ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" PROPERTIES HEADER_FILE_ONLY TRUE)

if(WIN32)
    include_directories( ${HEADER_FILES} )
	set(LIBRARIES ${LIBRARIES} glew_static  glfw ${GLFW_LIBRARIES} ${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY} Freetype)

	add_library(KTEngine STATIC ${SOURCE_FILES} ${DATA_FILES})
	target_link_libraries(KTEngine ${LIBRARIES})

	SET_TARGET_PROPERTIES(KTEngine PROPERTIES
	STATIC_LIBRARY_FLAGS
						"${freetype_path}
						 ${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/glew32s.lib
						 ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/src/Debug/glfw3.lib")

ELSEIF (UNIX)

    set(HEADER_FILES ${HEADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/include "/usr/local/include/freetype" PARENT_SCOPE)
	set(LIBRARIES ${LIBRARIES} glew_static  glfw ${GLFW_LIBRARIES} ${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY} ${FREETYPE_LIBRARIES} PARENT_SCOPE)

#	add_library(KTEngine STATIC ${SOURCE_FILES} ${DATA_FILES})
#	target_link_libraries(KTEngine ${LIBRARIES})

ENDIF(WIN32)



###################################################################################################
#VISUAL STUDIO FILTERS

	IF(WIN32)
	SOURCE_GROUP("CMakeLists" FILES "CMakeLists.txt")
	###################################################################################################
	#source groups
	#KTEngine
	FILE(GLOB KTEngineSrc  "src/*.cpp")
	SOURCE_GROUP("Src" FILES  ${KTEngineSrc} )

	FILE(GLOB KTEngineSrc "include/*.h")
	SOURCE_GROUP("Include" FILES  ${KTEngineSrc} )
	SOURCE_GROUP("CMakeLists\\src" FILES "${PROJECT_SOURCE_DIR}/src/CMakeLists.txt")

	###################################################################################################
	#KTEngine/Graphics
	FILE(GLOB KTEngineSrc "src/Graphics/*.cpp")
	SOURCE_GROUP("Src\\Graphics" FILES  ${KTEngineSrc} )

	FILE(GLOB KTEngineSrc "include/Graphics/*.h")
	SOURCE_GROUP("Include\\Graphics" FILES  ${KTEngineSrc} )

	SOURCE_GROUP("CMakeLists\\src\\Graphics" FILES "${PROJECT_SOURCE_DIR}/src/Graphics/CMakeLists.txt")
	###################################################################################################
	#KTEngine/Messages
	FILE(GLOB KTEngineSrc "src/Messages/*.cpp")
	SOURCE_GROUP("Src\\Messages" FILES  ${KTEngineSrc} )

	FILE(GLOB KTEngineSrc "include/Messages/*.h")
	SOURCE_GROUP("Include\\Messages" FILES  ${KTEngineSrc} )

	SOURCE_GROUP("CMakeLists\\src\\Messages" FILES "${PROJECT_SOURCE_DIR}/src/Messages/CMakeLists.txt")
	###################################################################################################
	#KTEngine/Systems
	FILE(GLOB KTEngineSrc "src/Systems/*.cpp")
	SOURCE_GROUP("Src\\Systems" FILES  ${KTEngineSrc} )

	FILE(GLOB KTEngineSrc "include/Systems/*.h")
	SOURCE_GROUP("Include\\Systems" FILES  ${KTEngineSrc} )

	SOURCE_GROUP("CMakeLists\\src\\Systems" FILES "${PROJECT_SOURCE_DIR}/src/Systems/CMakeLists.txt")

	###################################################################################################
	#KTEngine/Components
	FILE(GLOB KTEngineSrc "src/Components/*.cpp")
	SOURCE_GROUP("Src\\Components" FILES  ${KTEngineSrc} )

	FILE(GLOB KTEngineSrc "include/Components/*.h")
	SOURCE_GROUP("Include\\Components" FILES  ${KTEngineSrc} )

	SOURCE_GROUP("CMakeLists\\src\\Components" FILES "${PROJECT_SOURCE_DIR}/src/Components/CMakeLists.txt")

	###################################################################################################
	#KTEngine/Utility
	FILE(GLOB KTEngineSrc "src/Utility/*.cpp")
	SOURCE_GROUP("Src\\Utility" FILES  ${KTEngineSrc} )

	FILE(GLOB KTEngineSrc "include/Utility/*.h")
	SOURCE_GROUP("Include\\Utility" FILES  ${KTEngineSrc} )

	SOURCE_GROUP("CMakeLists\\src\\Utility" FILES "${PROJECT_SOURCE_DIR}/src/Utility/CMakeLists.txt")
ENDIF(WIN32)