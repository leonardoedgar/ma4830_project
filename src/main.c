/**********************************************************************
 * This is the main program. The workflow is listed below:
 *      1. Print a table containing maximum range and height for diffrent 
 *         launching configuration (Augmentations);
 *      2. Ask user input of target distance, the existence of terrian and
 *         distance, height of it (Four values).
 *      3. Print out all possible combinations of launching speed and angles
 *         indicated with augmentation numbers. 
 * 
 * It contains functions:
 *      double get_positive_float_from_user_input(char *message)
 *      double get_user_input(ObstacleInfo *obstacle)
 * 
 * Authors: Tao Shuailin, Leonador Edgar, Yuet Choon, He Zhanxin
 * 
 **********************************************************************/

#include <stdio.h>
#include <math.h>
#include "user_interface.h"
#include "planning_utils.h"
#define LAUNCH_CONFIG_ARR_SIZE 11

int main() {
    ObstacleInfo terrain;
    double distance;
    LaunchConfig launchConfigArr[LAUNCH_CONFIG_ARR_SIZE] = {};
    int validProjectileVelocities[] = {110, 115, 120, 125, 130}, index;
    print_augmentation_table(validProjectileVelocities, 5, 45.0, 5.0, 85.0);
    distance = get_user_input(&terrain);
    for (index=0; index<5; index++) {
        LaunchConfig launch;
        launch.velocity = validProjectileVelocities[index];
        launchConfigArr[index] = launch;
    }
    FunctionStatus status = get_all_trajectories_that_hit_target_by_speed(launchConfigArr, LAUNCH_CONFIG_ARR_SIZE,
            distance);
    if (status.success) {
        status = get_collision_free_trajectories(launchConfigArr, LAUNCH_CONFIG_ARR_SIZE, &terrain);
        if (status.success) {
            print_launch_configuration_table(launchConfigArr, LAUNCH_CONFIG_ARR_SIZE);
        }
        else {
            printf("%s", status.errorMessage);
        }
    }
    else {
        printf("%s", status.errorMessage);
    }
    return 0;
}
