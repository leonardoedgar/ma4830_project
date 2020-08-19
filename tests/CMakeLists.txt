project(ma4830_project C)
set(SOURCES ${SOURCES})

add_library(Unity STATIC ../lib/unity/src/unity.c)
target_include_directories(Unity PUBLIC ../lib/unity/src)

add_library(tests_lib STATIC ../src/int_header.h ../src/add_int.c ../src/multiply_int.c)
target_include_directories(tests_lib PUBLIC ${SOURCES})

add_executable(run_unit_tests main.c)
target_link_libraries(run_unit_tests Unity tests_lib)
