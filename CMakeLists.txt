project(greedySnake)

find_package(SDL2 REQUIRED)

set(CMAKE_C_STANDARD 11)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} snake.c)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

