#include "trajectory.h"
#include "utils.h"

/**
 * A function to check proper augmentation number received from a given launch configuration.
 */
void test_get_augmentation_number() {
    LaunchConfig launch = create_test_launch_config(45.0, 110);
    FunctionStatus status;
    int testNumber;
    int numValidTestCases = 5;
    for (testNumber=0; testNumber<numValidTestCases; testNumber++) {
        TEST_ASSERT_EQUAL(testNumber, get_augmentation_number(&launch, &status));
        TEST_ASSERT(status.success);
        launch.velocity += 5;
    }
    TEST_ASSERT_EQUAL(-1, get_augmentation_number(&launch, &status));
    TEST_ASSERT(!status.success);
    TEST_ASSERT_EQUAL_STRING("The augmentation number with the launch speed of 135 m/s does not exist.",
            status.errorMessage);
}

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
 * A function to test that the max distance of a trajectory can be computed.
 */
void test_get_trajectory_max_distance() {
    LaunchConfig launch = create_test_launch_config(30.0, 115);
    double max_distance = pow(launch.velocity, 2)/GRAVITY_ACCEL;
    FunctionStatus status;
    TEST_ASSERT_EQUAL_FLOAT(max_distance, get_trajectory_max_distance(&launch, &status));
    TEST_ASSERT_EQUAL(true, status.success);
}
