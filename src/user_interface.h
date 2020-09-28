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
#endif
