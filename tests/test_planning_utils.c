#include <math.h>
#include <stdlib.h>
#include "planning_utils.h"
#include "utils.h"

/**
 * A function to test the trajectory height computed from a given launch config distance from the mortar.
 */
double test_get_trajectory_height_by_distance() {
    LaunchConfig launch = create_test_launch_config(37.5, 110);
    double distance = 20.5;
    double height = (distance*tan(PI/180*launch.angle)) -
            (0.5*GRAVITY_ACCEL*pow(distance, 2)/pow(launch.velocity*cos(PI/180*launch.angle), 2));
    TEST_ASSERT_EQUAL_FLOAT(height, get_trajectory_height_by_distance(&launch, distance));
}


/**
 * A function to test if a trajectory is free from collision.
 */
void test_is_collision_free_trajectory() {
    LaunchConfig launch = create_test_launch_config(37.5, 110);
    ObstacleInfo terrain;
    TEST_ASSERT_EQUAL(true, is_collision_free_trajectory(&launch, &terrain));
    terrain.distanceFromMortar = 100.0;
    terrain.height = 70.2;
    TEST_ASSERT_EQUAL(true, is_collision_free_trajectory(&launch, &terrain));
    terrain.height += 0.2;
    TEST_ASSERT_EQUAL(false, is_collision_free_trajectory(&launch, &terrain));
}

/**
 * A function to compute trajectory angle to hit a pre-defined target.
 */
void test_compute_trajectory_angle_to_hit_target() {
    double distance = 50.5;
    double angles[2];
    LaunchConfig launch = create_test_launch_config(0.0, 30);
    FunctionStatus status = compute_trajectory_angle_to_hit_target(&launch, distance, angles);
    TEST_ASSERT_EQUAL(true, status.success);
    TEST_ASSERT_EQUAL_FLOAT(16.69223, angles[0]);
    TEST_ASSERT_EQUAL_FLOAT(73.30777, angles[1]);
    distance = -50.5;
    status = compute_trajectory_angle_to_hit_target(&launch, distance, angles);
    TEST_ASSERT_EQUAL(false, status.success);
    TEST_ASSERT_EQUAL_STRING("Angle computation failed. The angle computed -16.69deg is beyond the "
                             "theoretical constraint.", status.errorMessage);
}

/**
 * A function to test whether collision free trajectories are able to be retrieved.
 */
void test_get_collision_free_trajectories() {
    LaunchConfig inFeasibleLaunchConfigArr[] = {create_test_launch_config(0, 150),
                                                create_test_launch_config(90, 30),
                                                create_test_launch_config(10, 300)};
    LaunchConfig feasibleLaunchConfigArr[] = {create_test_launch_config(30, 125),
                                              create_test_launch_config(45, 115),
                                              create_test_launch_config(60, 110)};
    LaunchConfig mixedLaunchConfigArr[] = {create_test_launch_config(30, 125),
                                           create_test_launch_config(45, 115),
                                           create_test_launch_config(10,300),
                                           create_test_launch_config(60, 110)};
    ObstacleInfo terrain;
    FunctionStatus status;
    int lengthOfArr, index;
    terrain.distanceFromMortar = 74.5;
    terrain.height=37.5;
    status = get_collision_free_trajectories(inFeasibleLaunchConfigArr, 3, &terrain);
    TEST_ASSERT_EQUAL(true, status.success);
    TEST_ASSERT_EQUAL_FLOAT(0, inFeasibleLaunchConfigArr[0].angle);
    TEST_ASSERT_EQUAL_INT(0, inFeasibleLaunchConfigArr[0].velocity);

    status = get_collision_free_trajectories(mixedLaunchConfigArr, 4, &terrain);
    TEST_ASSERT_EQUAL(true, status.success);
    lengthOfArr = (int)(sizeof(mixedLaunchConfigArr) / sizeof(mixedLaunchConfigArr[0]));
    for(index=0; index<lengthOfArr; index++) {
        if(abs(mixedLaunchConfigArr[index].velocity) > 0 &&
            fabs(mixedLaunchConfigArr[index].angle) > FLOATING_POINT_PRECISION) {
            TEST_ASSERT_EQUAL_FLOAT(feasibleLaunchConfigArr[index].angle, mixedLaunchConfigArr[index].angle);
            TEST_ASSERT_EQUAL_INT(feasibleLaunchConfigArr[index].velocity, mixedLaunchConfigArr[index].velocity);
        }
        else {
            break;
        }
    }
}