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
 * A function to test that all trajectories that hit the target can be retrieved.
 */
void test_get_all_trajectories_that_hit_target_by_speed(){
    int index;
    LaunchConfig launchConfigArr[12] = {create_test_launch_config(0, 125),
                                       create_test_launch_config(0, 115),
                                       create_test_launch_config(0, 110),
                                       create_test_launch_config(0, 41),
                                       create_test_launch_config(0, 30),
                                       create_test_launch_config(0, 0)};
    double solutionAngles[] = {2.985433, 87.014567, 3.529759, 86.470241, 3.859854, 86.140146, 37.63689, 52.36311};
    double solutionVelocities[] = {125, 125, 115, 115, 110, 110, 41, 41};
    double distance = 165.75;
    FunctionStatus status = get_all_trajectories_that_hit_target_by_speed(launchConfigArr, 12, distance);
    TEST_ASSERT_EQUAL(true, status.success);
    for (index=0; index < 12; index++) {
        if (launchConfigArr[index].velocity == 0 && fabs(launchConfigArr[index].angle) < FLOATING_POINT_PRECISION) {
            break;
        }
        TEST_ASSERT_EQUAL_INT(solutionVelocities[index], launchConfigArr[index].velocity);
        TEST_ASSERT_EQUAL_FLOAT(solutionAngles[index], launchConfigArr[index].angle);
    }
}
