/**********************************************************************
 * This file is used to calculate all the possible collision free 
 * trajectories with distance of target and distance, height 
 * information of terrian given.
 * 
 * It contains functions:
 *      bool is_collision_free_trajectory(const LaunchConfig *launchConfig, 
 *          const ObstacleInfo *terrain)
 *      FunctionStatus compute_trajectory_angle_to_hit_target(
 *          const LaunchConfig *launchConfig, double distance,double *angles)
 *      FunctionStatus get_all_trajectories_that_hit_target_by_speed(
 *          LaunchConfig* launchConfigArr, int lengthOfArr, double distance)
 *      FunctionStatus get_collision_free_trajectories(LaunchConfig *launchConfigArr, 
 *          int lengthOfArr, const ObstacleInfo *terrain)
 * 
 * Authors: Tao Shuailin, Leonador Edgar, Yuet Choon, He Zhanxin
 * 
 **********************************************************************/

#include <math.h>
#include <string.h>
#include <stdio.h>
#include "planning_utils.h"
#include "trajectory.h"

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
    double max_distance = get_trajectory_max_distance(launchConfig);
    if (max_distance < distance) {
        status.success = false;
        strcpy(status.errorMessage, "");
    }
    else {
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
    }
    return status;
}

/**
 * A function to get all trajectories that are feasible to hit the target.
 * @param launchConfigArr represents the launch configuration whose angle to be computed to hit the target.
 * @param lengthOfArr represents the length of the launch configuration array.
 * @param distance of the target from the mortar.
 * @return the status of the function result.
 */
FunctionStatus get_all_trajectories_that_hit_target_by_speed(LaunchConfig* launchConfigArr, int lengthOfArr,
                                                             double distance) {
    FunctionStatus status;
    LaunchConfig solutionLaunchConfigArr[lengthOfArr];
    int index, numSolutionFound=0;
    double angles[2];
    for(index=0; index<lengthOfArr; index++) {
        if (launchConfigArr[index].velocity == 0) {
            break;
        }
        status = compute_trajectory_angle_to_hit_target(&launchConfigArr[index], distance, angles);
        if (!status.success) {
            printf("%s", status.errorMessage);
        }
        else if (fabs(angles[1]-angles[0]) > FLOATING_POINT_PRECISION) {
            LaunchConfig feasibleLaunchOne, feasibleLaunchTwo;
            feasibleLaunchOne.velocity = launchConfigArr[index].velocity;
            feasibleLaunchOne.angle = angles[0];
            feasibleLaunchTwo.velocity = launchConfigArr[index].velocity;
            feasibleLaunchTwo.angle = angles[1];
            solutionLaunchConfigArr[numSolutionFound] = feasibleLaunchOne;
            solutionLaunchConfigArr[numSolutionFound+1] = feasibleLaunchTwo;
            numSolutionFound += 2;
        }
        else if (fabs(angles[1] - angles[0]) <= FLOATING_POINT_PRECISION) {
            LaunchConfig feasibleLaunch;
            feasibleLaunch.velocity = launchConfigArr[index].velocity;
            feasibleLaunch.angle = angles[0];
            solutionLaunchConfigArr[numSolutionFound] = feasibleLaunch;
            numSolutionFound += 1;
        }
    }
    index=0;
    if (numSolutionFound != 0) {
        for (index=0; index<numSolutionFound; index++) {
            launchConfigArr[index] = solutionLaunchConfigArr[index];
        }
    }
    LaunchConfig launch;
    launch.velocity = 0;
    launch.angle = 0.0;
    launchConfigArr[index] = launch;
    status.success = true;
    strcpy(status.errorMessage, "");
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
