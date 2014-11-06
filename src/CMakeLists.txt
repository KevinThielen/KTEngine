
message("Engine: =======================================")

ADD_SUBDIRECTORY(Graphics)
ADD_SUBDIRECTORY(Window)
ADD_SUBDIRECTORY(Components)


set(SOURCE_FILES ${SOURCE_FILES} ${KTEngine_SOURCE_DIR}/src/Engine.cpp ${KTEngine_SOURCE_DIR}/src/GameObject.cpp PARENT_SCOPE)
set(HEADER_FILES ${HEADER_FILES}
                 "${KTEngine_SOURCE_DIR}/include"
                 "${KTEngine_SOURCE_DIR}/external/glm/"
                 "${KTEngine_SOURCE_DIR}/external/glfw/include/"
                 "${KTEngine_SOURCE_DIR}/external/freetype/include/freetype/"
                 "${KTEngine_SOURCE_DIR}/external/stb"
                 PARENT_SCOPE)

set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)
#add_library(KTEngine STATIC ${SOURCE_FILES} Graphics Window)

#target_include_directories(${TARGET} PUBLIC
   #             ${HEADER_FILES} )

