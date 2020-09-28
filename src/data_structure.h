#ifndef MA4830_PROJECT_DATA_STRUCTURE_H
#define MA4830_PROJECT_DATA_STRUCTURE_H
#include <stdbool.h>

#define GRAVITY_ACCEL 9.81
#define PI 3.14285714
#define ERROR_MESSAGE_SIZE 100
#define FLOATING_POINT_PRECISION 1e-7

/**
 * A data type definition to represent the mortar's launch configuration.
 */
typedef struct LaunchConfig {
    double angle;
    int velocity;
} LaunchConfig;

/**
 * A data type that contains the obstacle's information.
 */
typedef struct ObstacleInfo {
    double distanceFromMortar;
    double height;
} ObstacleInfo;

/**
 * A data type to represent the status of function used.
 */

typedef struct FunctionStatus {
    bool success;
    char errorMessage[ERROR_MESSAGE_SIZE];
} FunctionStatus;

#endif
