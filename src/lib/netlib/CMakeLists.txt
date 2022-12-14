aux_source_directory(. SRC_LIST)
add_library(net ${SRC_LIST})
target_include_directories(net PUBLIC ${PROJECT_SOURCE_DIR}/include)
