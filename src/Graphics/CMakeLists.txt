#KTEngine/Graphics

set(KTENGINE_SOURCE
                 ${CMAKE_CURRENT_SOURCE_DIR}/GameSprite.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/Quad.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/ShaderManager.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/SpriteTechnique.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/Texture.cpp
)
set(KTENGINE_HEADER
				  ${KTEngine_SOURCE_DIR}/include/Graphics/GameSprite.h
                  ${KTEngine_SOURCE_DIR}/include/Graphics/Quad.h
                  ${KTEngine_SOURCE_DIR}/include/Graphics/ShaderManager.h
                  ${KTEngine_SOURCE_DIR}/include/Graphics/SpriteTechnique.h
                  ${KTEngine_SOURCE_DIR}/include/Graphics/Texture.h
                  ${KTEngine_SOURCE_DIR}/include/Graphics/Animation.h
                  ${KTEngine_SOURCE_DIR}/include/Graphics/Mesh.h
                  ${KTEngine_SOURCE_DIR}/include/Graphics/RenderTechnique.h
)


set(DATA_FILES ${DATA_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" PARENT_SCOPE)
set_source_files_properties(" ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" PROPERTIES HEADER_FILE_ONLY TRUE)

set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)
set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
set(SOURCE_FILES ${SOURCE_FILES} ${KTENGINE_SOURCE} ${KTENGINE_HEADER} PARENT_SCOPE)