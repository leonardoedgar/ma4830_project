#include "utils.h"
/**
 * A function to create launch configuration for testing purpose.
 * @return the launch configuration
 */
LaunchConfig create_test_launch_config(double angle, int velocity) {
    LaunchConfig launch;
    launch.angle = angle;
    launch.velocity = velocity;
    return launch;
}
