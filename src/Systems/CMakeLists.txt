#KTEngine/Systems

set(KTENGINE_SOURCE
                 ${CMAKE_CURRENT_SOURCE_DIR}/RenderSystem.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/AnimationSystem.cpp
)
set(KTENGINE_HEADER
                "${KTEngine_SOURCE_DIR}/include/Systems/ISystem.h"
                 "${KTEngine_SOURCE_DIR}/include/Systems/RenderSystem.h"
                 "${KTEngine_SOURCE_DIR}/include/Systems/AnimationSystem.h"
)


set(DATA_FILES ${DATA_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" PARENT_SCOPE)
set_source_files_properties(" ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" PROPERTIES HEADER_FILE_ONLY TRUE)

set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)
set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
set(SOURCE_FILES ${SOURCE_FILES} ${KTENGINE_SOURCE} ${KTENGINE_HEADER} PARENT_SCOPE)