

set(SOURCE_FILES ${SOURCE_FILES}  ${KTEngine_SOURCE_DIR}/src/Graphics/Font.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/FontManager.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/MeshManager.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/Quad.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/RenderSystem.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/ShaderManager.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/Text.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/Texture.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/TextureManager.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/RenderTechniques/BasicTechnique.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/RenderTechniques/FontTechnique.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/RenderTechniques/SpriteTechnique.cpp
                                  ${KTEngine_SOURCE_DIR}/src/Graphics/RenderTechniques/RenderTechniqueManagager.cpp
                                  PARENT_SCOPE)

#add_library(KTEGraphics STATIC ${SOURCE_FILES})
set(LIBRARIES ${LIBRARIES} glew_static glfw ${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} freetype_static zlib_static PARENT_SCOPE)

#target_link_libraries(KTEGraphics )
