cmake_minimum_required(VERSION 3.22)
project(hello-triangle)

include(FetchContent)

fetchcontent_declare(
        big2
        GIT_REPOSITORY "https://github.com/Paper-Cranes-Ltd/big2-stack.git"
        GIT_TAG "v0.0.9"
        GIT_SHALLOW TRUE
)

fetchcontent_makeavailable(big2)

add_subdirectory(triangle)