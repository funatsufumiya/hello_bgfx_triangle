project(triangle)

set(COMMON_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/shader_loader.cpp"
)

file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
list(REMOVE_ITEM EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/shader_loader.cpp")

add_shaders_directory(shaders SHADERS_TARGET_NAME)

find_package(OpenGL)

foreach (EXAMPLE_SOURCE IN LISTS EXAMPLE_SOURCES)
    get_filename_component(SAFE_EXAMPLE_NAME "${EXAMPLE_SOURCE}" NAME_WE)
    set(SAFE_EXAMPLE_NAME "big2_example_${SAFE_EXAMPLE_NAME}")
    add_executable(${SAFE_EXAMPLE_NAME} ${EXAMPLE_SOURCE} ${COMMON_SOURCES})
    target_link_libraries(${SAFE_EXAMPLE_NAME} PUBLIC BIG2)
    target_link_libraries(${SAFE_EXAMPLE_NAME} PUBLIC ${SHADERS_TARGET_NAME})
    if (OPENGL_FOUND)
        target_link_libraries(${SAFE_EXAMPLE_NAME} PUBLIC OpenGL::GL)
    endif ()
    target_include_directories(${SAFE_EXAMPLE_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
endforeach ()