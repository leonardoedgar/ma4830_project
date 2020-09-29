#include <math.h>
#include <string.h>
#include <stdio.h>
#include "planning_utils.h"

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
 * A function to check if a trajectory is collision-free.
 * @param launchConfig represents the mortar's launch configuration.
 * @param terrain represents the obstacle information.
 * @return whether the trajectory is free from collision or not.
 */
bool is_collision_free_trajectory(const LaunchConfig *launchConfig, const ObstacleInfo *terrain) {
    if (fabs(terrain->distanceFromMortar) < FLOATING_POINT_PRECISION &&
        fabs(terrain->height) < FLOATING_POINT_PRECISION) {
        return true;
    }
    else if (launchConfig->velocity == 0) {
        return false;
    }
    return get_trajectory_height_by_distance(launchConfig, terrain->distanceFromMortar) > terrain->height;
}

/**
 * A function to compute the trajectory angle to hit a target.
 * @param launchConfig represents the mortar's launch configuration.
 * @param distance of the target from the mortar.
 * @param angles contains an array of feasible angles.
 * @return the status of the function result.
 */
FunctionStatus compute_trajectory_angle_to_hit_target(const LaunchConfig *launchConfig, double distance,
        double *angles) {
    FunctionStatus status;
    angles[0] = asin(distance*GRAVITY_ACCEL/pow(launchConfig->velocity, 2))/2*180/PI;
    angles[1] = 90 - angles[0];
    if (angles[0] < 0 || angles[0] > 180) {
        status.success = false;
        strcpy(status.errorMessage, "");
        sprintf(status.errorMessage, "Angle computation failed. The angle computed %.2f deg is beyond the "
                                     "theoretical constraint.", angles[0]);
    }
    else if (angles[1] < 0 || angles[1] > 180) {
        status.success = false;
        strcpy(status.errorMessage, "");
        sprintf(status.errorMessage, "Angle computation failed. The angle computed %.2f deg is beyond the "
                                     "theoretical constraint.", angles[1]);
    }
    else {
        status.success = true;
    }
    return status;
}

/**
 * A function to get collision-free trajectories from the launch configurations given.
 * @param launchConfigArr represents an array of launch configurations.
 * @param lengthOfArr represents the size of the launch configuration array.
 * @param terrain represents the obstacle information.
 * @return the status of the function result.
 */
FunctionStatus get_collision_free_trajectories(LaunchConfig *launchConfigArr, int lengthOfArr, const ObstacleInfo *terrain) {
    int collisionFreeTrajectoryIndexes[lengthOfArr+1], index;
    int copyIndex = 0;
    FunctionStatus status;
    for(index=0; index<lengthOfArr; index++) {
        if (launchConfigArr[index].velocity == 0 && fabs(launchConfigArr[index].angle) < FLOATING_POINT_PRECISION) {
            break;
        }
        else if (is_collision_free_trajectory(launchConfigArr+index, terrain)) {
            collisionFreeTrajectoryIndexes[copyIndex] = index;
            copyIndex += 1;
        }
    }
    collisionFreeTrajectoryIndexes[copyIndex] = -1;
    for (index=0; index<lengthOfArr; index++) {
        if (collisionFreeTrajectoryIndexes[index] == -1) {
            LaunchConfig launch;
            launch.angle = 0.0;
            launch.velocity = 0;
            launchConfigArr[index] = launch;
            break;
        }
        launchConfigArr[index] = launchConfigArr[collisionFreeTrajectoryIndexes[index]];
    }
    status.success = true;
    return status;
}
