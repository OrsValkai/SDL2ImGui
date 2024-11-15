# CMakeList.txt : CMake project for MySDL, include source and define
# project specific logic here.
#

set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/dep/SDL2/cmake/)
set(SDL2_image_DIR ${CMAKE_CURRENT_LIST_DIR}/dep/SDL2_image/cmake/)

find_package(SDL2 CONFIG REQUIRED)
find_package(sdl2_image CONFIG REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/dep/SDL2_image/include
    ${PROJECT_SOURCE_DIR}/dep/SDL2/include
    ${PROJECT_SOURCE_DIR}/include
)

file(GLOB ALL_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/include/*.inl"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} ${ALL_SRCS})

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

if (CMAKE_VERSION VERSION_GREATER 3.5)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()

# TODO: Add tests and install targets if needed.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
)