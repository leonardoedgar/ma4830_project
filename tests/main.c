#include "unity.h"
#include "test_planning_utils.c"
#include "test_trajectory.c"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_planning_utils() {
    test_is_collision_free_trajectory();
    test_compute_trajectory_angle_to_hit_target();
    test_get_all_trajectories_that_hit_target_by_speed();
    test_get_collision_free_trajectories();
}

void test_trajectory() {
    test_get_augmentation_number();
    test_get_trajectory_height_by_distance();
    test_get_trajectory_distance();
    test_get_trajectory_max_distance();
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_planning_utils);
    RUN_TEST(test_trajectory);
    return UNITY_END();
}