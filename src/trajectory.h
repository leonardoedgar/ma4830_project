#ifndef MA4830_PROJECT_TRAJECTORY_H
#define MA4830_PROJECT_TRAJECTORY_H
#include "data_structure.h"

/**
 * A function to get the augmentation number of a mortar's launch configuration.
 * @param launch represents the mortar's launch configuration.
 * @param status represents the status of the function.
 * @return the augmentation number of the launch configuration.
 */
int get_augmentation_number(const LaunchConfig* launch, FunctionStatus* status);

/**
 * A function to get all trajectories that are feasible to hit the target.
 * @param launchConfigArr represents the launch configuration whose angle to be computed to hit the target.
 * @param lengthOfArr represents the length of the launch configuration array.
 * @param distance of the target from the mortar.
 * @return the status of the function result.
 */
FunctionStatus get_all_trajectories_that_hit_target_by_speed(LaunchConfig* launchConfigArr, int lengthOfArr,
                                                             double distance);

#endif
