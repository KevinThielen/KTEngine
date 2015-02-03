
ADD_SUBDIRECTORY(Systems)
ADD_SUBDIRECTORY(Graphics)

set(SOURCE_FILES ${SOURCE_FILES}
                 ${CMAKE_CURRENT_SOURCE_DIR}/GameEngine.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/Window.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/GameObject.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/IGameScene.cpp
    PARENT_SCOPE)

set(HEADER_FILES ${HEADER_FILES}
                 "${KTEngine_SOURCE_DIR}/include/"
                 "${KTEngine_SOURCE_DIR}/external/glm/"
                 "${KTEngine_SOURCE_DIR}/external/glfw/include/"
                 "${KTEngine_SOURCE_DIR}/external/freetype/include/freetype/"
                 "${KTEngine_SOURCE_DIR}/external/stb/"
                 "${KTEngine_SOURCE_DIR}/external/jsoncpp/include/"
                 PARENT_SCOPE)

set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)
