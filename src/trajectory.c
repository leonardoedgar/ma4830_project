#include <string.h>
#include <math.h>
#include <stdio.h>
#include "trajectory.h"
#include "planning_utils.h"

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
            sprintf(status->errorMessage, "The augmentation number with the launch speed of %dm/s does not exist.",
                    launch->velocity);
            return -1;
        }
    }
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
