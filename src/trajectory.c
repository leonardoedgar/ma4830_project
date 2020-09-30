#include <string.h>
#include <math.h>
#include <stdio.h>
#include "trajectory.h"

/**
 * A function to get the augmentation number of a mortar's launch configuration.
 * @param launch represents the mortar's launch configuration.
 * @param status represents the status of the function.
 * @return the augmentation number of the launch configuration.
 */
int get_augmentation_number(const LaunchConfig* launch, FunctionStatus* status) {
    switch(launch->velocity) {
        case 110: {
            status->success=true;
            return 0;
        }
        case 115: {
            status->success=true;
            return 1;
        }
        case 120: {
            status->success=true;
            return 2;
        }
        case 125: {
            status->success=true;
            return 3;
        }
        case 130: {
            status->success=true;
            return 4;
        }
        default: {
            status->success=false;
            strcpy(status->errorMessage, "");
            sprintf(status->errorMessage, "The augmentation number with the launch speed of %d m/s "
                                          "does not exist.", launch->velocity);
            return -1;
        }
    }
}

/**
 * A function to get the trajectory height at a distance from the mortar.
 * @param launchConfig represents the mortar's launch configuration.
 * @param distance represents the distance from the mortar.
 * @return the trajectory height.
 */
double get_trajectory_height_by_distance(const LaunchConfig *launchConfig, double distance) {
    return (distance*tan(PI/180*launchConfig->angle)) -
           (0.5*GRAVITY_ACCEL*pow(distance, 2)/pow(launchConfig->velocity*cos(PI/180*launchConfig->angle), 2));
}

/**
 * A function to get the trajectory distance.
 * @param launchConfig represents the mortar's launch configuration.
 * @return the distance of the trajectory.
 */
double get_trajectory_distance(const LaunchConfig* launchConfig) {
    return pow(launchConfig->velocity, 2)*sin(2*launchConfig->angle*PI/180)/GRAVITY_ACCEL;
}


/**
 * A function to get the trajectory maximum distance.
 * @param launchConfig represents the mortar's launch configuration.
 * @return the maximum distance of the trajectory.
 */
double get_trajectory_max_distance(const LaunchConfig* launchConfig) {
    LaunchConfig launch;
    launch.velocity = launchConfig->velocity;
    launch.angle = 45.0;
    return get_trajectory_distance(&launch);
}
