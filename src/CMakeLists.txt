project(ma4830_project C)
set(SOURCES ${SOURCES})

# Add dependencies needed to run the main executable file
add_library(${CMAKE_PROJECT_NAME}_lib STATIC data_structure.h planning_utils.h planning_utils.c trajectory.h
        trajectory.c user_interface.h user_interface.c)
target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC ${SOURCES})

add_executable(main main.c)
target_link_libraries(main PRIVATE ${CMAKE_PROJECT_NAME}_lib m)
