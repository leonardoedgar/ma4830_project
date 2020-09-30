#ifndef MA4830_PROJECT_USER_INTERFACE_H
#define MA4830_PROJECT_USER_INTERFACE_H

#include "data_structure.h"

/**
 * A function to get a positive floating point number from the user.
 * @param message to prompt for user input.
 * @return the floating point number user inputted.
 */
double get_positive_float_from_user_input(char* message);

/**
 * A function to get user input about the obstacle and mortar's target.
 * @param obstacle represents the obstacle information user specified.
 * @return the distance to the mortar's target.
 */
double get_user_input(ObstacleInfo* obstacle);

/**
 * A function to print a table that contains the maximum speed and height given an array of velocities of the trajectory.
 * @param launchVelocityArr contains launch velocities of the trajectory.
 * @param arraySize indicates the launch velocity array size.
 * @param startAngle indicates the projectile launch start angle.
 * @param stepAngle indicates the projectile launch step angle.
 * @param endAngle indicates the projectile launch end angle.
 */
void print_launch_velocities_table(const int* launchVelocityArr, int arraySize, double startAngle, double stepAngle,
                                   double endAngle);

#endif
