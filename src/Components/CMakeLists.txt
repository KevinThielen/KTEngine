#KTEngine/Components

set(KTENGINE_SOURCE

)
set(KTENGINE_HEADER
				  ${KTEngine_SOURCE_DIR}/include/Components/Animator.h
				  ${KTEngine_SOURCE_DIR}/include/Components/BoxCollider.h
				  ${KTEngine_SOURCE_DIR}/include/Components/Camera.h
				  ${KTEngine_SOURCE_DIR}/include/Components/IComponent.h
				  ${KTEngine_SOURCE_DIR}/include/Components/MovementComponent.h
				  ${KTEngine_SOURCE_DIR}/include/Components/SpriteComponent.h
				  ${KTEngine_SOURCE_DIR}/include/Components/TransformationComponent.h

)

set(DATA_FILES ${DATA_FILES} "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" PARENT_SCOPE)
set_source_files_properties(" ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt" PROPERTIES HEADER_FILE_ONLY TRUE)

set(LIBRARIES ${LIBRARIES} PARENT_SCOPE)
set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
set(SOURCE_FILES ${SOURCE_FILES} ${KTENGINE_SOURCE} ${KTENGINE_HEADER} PARENT_SCOPE)