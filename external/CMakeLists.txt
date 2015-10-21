set(HEADER_FILES ${HEADER_FILES}  PARENT_SCOPE)

set(SOURCE_FILES ${SOURCE_FILES} "${KTEngine_SOURCE_DIR}/external/jsoncpp/src/lib_json/json_reader.cpp"
                                 "${KTEngine_SOURCE_DIR}/external/jsoncpp/src/lib_json/json_value.cpp"
				 "${KTEngine_SOURCE_DIR}/external/jsoncpp/src/lib_json/json_writer.cpp"
PARENT_SCOPE)

IF(NOT EMSCRIPTEN)
    add_subdirectory(enet)
    add_subdirectory(glfw)
ENDIF(NOT EMSCRIPTEN)

