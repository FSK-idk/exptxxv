cmake_minimum_required(VERSION 4.1.2 FATAL_ERROR)

project(xxvc LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_26)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE MODULES CONFIGURE_DEPENDS src/*.mpp)
target_sources(${PROJECT_NAME}
    PRIVATE
        ${SOURCES}
    PUBLIC
        FILE_SET CXX_MODULES
        FILES ${MODULES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC LLVM)
