cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME gui_application_draw_tree)
project( ${PROJECT_NAME} )

option(BUILD_EXECUTABLE "Build executable." ON)

include("compiler_options.cmake")

add_library(
    ${PROJECT_NAME} 
    STATIC 
    src/application.cpp
    src/entity_browser.cpp
    src/gui_cameras.cpp
    src/random.cpp
    src/renderer.cpp
    src/simulation_clock.cpp
    src/time.cpp    
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

find_package(glm REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)

target_link_libraries(${PROJECT_NAME} PUBLIC gl_classes)
target_link_libraries(${PROJECT_NAME} PUBLIC chunky_mem)
target_link_libraries(${PROJECT_NAME} PUBLIC transform_tree_glm)
target_link_libraries(${PROJECT_NAME} PUBLIC draw_tree_gl)
target_link_libraries(${PROJECT_NAME} PUBLIC cameras_gl)
target_link_libraries(${PROJECT_NAME} PUBLIC gui_application)

if (BUILD_EXECUTABLE)
    add_executable(${PROJECT_NAME}_app src/main.cpp)
    target_link_libraries(${PROJECT_NAME}_app PRIVATE ${PROJECT_NAME})
endif()
