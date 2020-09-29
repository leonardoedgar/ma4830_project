project(ma4830_project C)
set(SOURCES ${SOURCES})

add_library(unity STATIC ../lib/unity/src/unity.c)
target_include_directories(unity PUBLIC ../lib/unity/src)

add_library(tests_lib STATIC ../src/data_structure.h ../src/planning_utils.h ../src/planning_utils.c
        ../src/trajectory.h ../src/trajectory.c utils.h utils.c)
target_include_directories(tests_lib PUBLIC ${SOURCES})

add_executable(run_unit_tests main.c)
target_link_libraries(run_unit_tests unity tests_lib m)
