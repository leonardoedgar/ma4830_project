#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include "user_interface.h"

/**
 * A function to get a positive floating point number from the user.
 * @param message to prompt for user input.
 * @return the floating point number user inputted.
 */
double get_positive_float_from_user_input(char* message) {
    bool isUserInputValid = false;
    double number;
    while (!isUserInputValid) {
        printf("%s", message);
        scanf("%lf", &number);
        while ((getchar()) != '\n');
        if (fabs(number) < FLOATING_POINT_PRECISION || number < 0) {
            printf("Input is not a valid positive floating point number. Retry.\n");
        }
        else {
            isUserInputValid=true;
        }
    }
    return number;
}


/**
 * A function to get user input about the obstacle and mortar's target.
 * @param obstacle represents the obstacle information user specified.
 * @return the distance to the mortar's target.
 */
double get_user_input(ObstacleInfo* obstacle) {
    double distance;
    char isTerrainExistChar;
    bool isTerrainExistBool, isUserInputValid=false;
    distance = get_positive_float_from_user_input("Enter target distance from mortar: ");
    while (!isUserInputValid) {
        printf("Is there any obstacles (y/n)? ");
        scanf("%c", &isTerrainExistChar);
        while ((getchar()) != '\n');
        switch (tolower(isTerrainExistChar)) {
            case 'y':
                isTerrainExistBool = true;
                isUserInputValid = true;
                break;
            case 'n':
                isTerrainExistBool = false;
                isUserInputValid = true;
                break;
            default:
                printf("Input is invalid. Please only enter (y/n). Retry.\n");
        }
    }
    if (isTerrainExistBool) {
        obstacle->height = get_positive_float_from_user_input("Enter obstacle's height: ");
        obstacle->distanceFromMortar = get_positive_float_from_user_input("Enter obstacle's distance from mortar: ");
    }
    return distance;
}
