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
 * A function to get the trajectory height at a distance from the mortar.
 * @param launchConfig represents the mortar's launch configuration.
 * @param distance represents the distance from the mortar.
 * @return the trajectory height.
 */
double get_trajectory_height_by_distance(const LaunchConfig *launchConfig, double distance);

/**
 * A function to get the trajectory distance.
 * @param launchConfig represents the mortar's launch configuration.
 * @return the distance of the trajectory.
 */
double get_trajectory_distance(const LaunchConfig* launchConfig);

/**
 * A function to get the trajectory maximum distance.
 * @param launchConfig represents the mortar's launch configuration.
 * @return the maximum distance of the trajectory.
 */
double get_trajectory_max_distance(const LaunchConfig* launchConfig);
#endif
