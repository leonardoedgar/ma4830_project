#include <stdio.h>
#include <math.h>
#include "user_interface.h"
#include "planning_utils.h"
#define LAUNCH_CONFIG_ARR_SIZE 11

int main() {
    ObstacleInfo terrain;
    double distance;
    distance = get_user_input(&terrain);
    LaunchConfig launchConfigArr[LAUNCH_CONFIG_ARR_SIZE] = {};
    int validProjectileVelocities[] = {110, 115, 120, 125, 130}, index;
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
            if (fabs(launchConfigArr[0].angle) < FLOATING_POINT_PRECISION && launchConfigArr[0].velocity == 0) {
                printf("There is no any feasible configurations to hit the target.\n");
            }
            else {
                printf("Here are all possible configurations to hit the target.\n");
                for (index=0; index<LAUNCH_CONFIG_ARR_SIZE; index++) {
                    if (fabs(launchConfigArr[index].angle) < FLOATING_POINT_PRECISION && launchConfigArr[index].velocity == 0) {
                        break;
                    }
                    printf("velocity: %d m/s\t angle: %.2f deg\n", launchConfigArr[index].velocity,
                           launchConfigArr[index].angle);
                }
            }
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
