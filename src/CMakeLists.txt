
ADD_SUBDIRECTORY(Systems)
ADD_SUBDIRECTORY(Graphics)
ADD_SUBDIRECTORY(Components)
ADD_SUBDIRECTORY(Messages)
ADD_SUBDIRECTORY(Utility)
add_subdirectory(Audio)
add_subdirectory(Resources)

set(KTENGINE_SOURCE 
                 ${CMAKE_CURRENT_SOURCE_DIR}/GameEngine.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/GameObject.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/IGameScene.cpp
    )


IF(EMSCRIPTEN)
set(EXTERNAL_HEADER 
	         "${KTEngine_SOURCE_DIR}/include/"
                 "${KTEngine_SOURCE_DIR}/external/glm/"
                 "${KTEngine_SOURCE_DIR}/external/stb/"
                 "${KTEngine_SOURCE_DIR}/external/jsoncpp/include/"
                 "${KTEngine_SOURCE_DIR}/external/portaudio/include/" 
)
ELSE(EMSCRIPTEN)
set(EXTERNAL_HEADER 
	         "${KTEngine_SOURCE_DIR}/include/"
                 "${KTEngine_SOURCE_DIR}/external/glm/"
                 "${KTEngine_SOURCE_DIR}/external/glfw/include/"
		 "${KTEngine_SOURCE_DIR}/external/glew/include/"
                 "${KTEngine_SOURCE_DIR}/external/stb/"
                 "${KTEngine_SOURCE_DIR}/external/jsoncpp/include/"
                 "${KTEngine_SOURCE_DIR}/external/portaudio/include/"
                 "${KTEngine_SOURCE_DIR}/external/enet/include/"
                 )
ENDIF(EMSCRIPTEN)
#needed for VS filter
set(KTENGINE_HEADER 
                 ${KTEngine_SOURCE_DIR}/include/GameEngine.h
                 ${KTEngine_SOURCE_DIR}/include/Window.h
                 ${KTEngine_SOURCE_DIR}/include/GameObject.h
                 ${KTEngine_SOURCE_DIR}/include/IGameScene.h
                 ${KTEngine_SOURCE_DIR}/include/Resources.h
                 ${KTEngine_SOURCE_DIR}/include/Input.h
                 )



set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)
set(HEADER_FILES ${HEADER_FILES} ${EXTERNAL_HEADER} PARENT_SCOPE)
set(SOURCE_FILES ${SOURCE_FILES} ${KTENGINE_SOURCE} ${KTENGINE_HEADER} PARENT_SCOPE)

set(DATA_FILES ${DATA_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" PARENT_SCOPE)
set_source_files_properties(" ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" PROPERTIES HEADER_FILE_ONLY TRUE)


