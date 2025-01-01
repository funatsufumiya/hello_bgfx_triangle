project(triangle)

add_shaders_directory("${CMAKE_CURRENT_SOURCE_DIR}/shaders" SHADERS_TARGET_NAME)

add_executable("${PROJECT_NAME}" src/main.cpp)
target_link_libraries("${PROJECT_NAME}" PUBLIC "${SHADERS_TARGET_NAME}")