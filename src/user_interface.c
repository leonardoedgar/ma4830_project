#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "user_interface.h"
#include "trajectory.h"

/**
 * A function to get a positive floating point number from the user.
 * @param message to prompt for user input.
 * @return the floating point number user inputted.
 */
double get_positive_float_from_user_input(char* message) {
    bool isUserInputValid = false;
    double number;
    char userInput[ERROR_MESSAGE_SIZE];
    char* leftoverBuffer;
    while (!isUserInputValid) {
        printf("%s", message);
        scanf("%s", userInput);
        getchar();
        number = strtod(userInput, &leftoverBuffer);
        if (fabs(number) < FLOATING_POINT_PRECISION || *leftoverBuffer) {
            printf("Input is not a number. Retry.\n");
        }
        else if (number < 0) {
            printf("Input is not a positive number. Retry.\n");
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

/**
 * A function to print a table that contains the maximum range and height given an array of velocities of the trajectory.
 * @param launchVelocityArr contains launch velocities of the trajectory.
 * @param arraySize indicates the launch velocity array size.
 * @param startAngle indicates the projectile launch start angle.
 * @param stepAngle indicates the projectile launch step angle.
 * @param endAngle indicates the projectile launch end angle.
 */
void print_launch_velocities_table(const int* launchVelocityArr, int arraySize, double startAngle, double stepAngle,
        double endAngle) {
    double angle, maxRange, maxHeight;
    int index, augmentationNumber;
    char tableTitle[] = "Augmentation Table";
    int numSpaceBetweenTitle = (29*arraySize-(int)strlen(tableTitle)+10)/2;
    LaunchConfig launch;
    FunctionStatus status;
    printf("The table of the maximum range and height for different muzzle velocities are listed as below.\n");
    printf("\f");
    printf("%*c", numSpaceBetweenTitle, ' ');
    printf("Augmentation Table");
    printf("%*c\n", numSpaceBetweenTitle, ' ');
    printf("==========");
    for (index=0; index<arraySize; index++) {
        printf("=============================");
    }
    printf("\n|        |");
    for (index=0; index<arraySize; index++) {
        launch.velocity = launchVelocityArr[index];
        augmentationNumber = get_augmentation_number(&launch, &status);
        if (!status.success) {
            printf("       Augmentation ?       |");
        }
        else {
            printf("       Augmentation %d       |", augmentationNumber);
        }
    }
    printf("\n| Degree |");
    for (index=0; index<arraySize; index++) {
        printf("----------------------------|");
    }
    printf("\n|        |");
    for (index=0; index<arraySize; index++) {
        printf(" range (m) | max height (m) |");
    }
    printf("\n|--------|");
    for (index=0; index<arraySize; index++) {
        printf("----------------------------|");
    }
    printf("\n");
    for (angle = startAngle; angle < endAngle; angle += stepAngle)
    {
        printf("|%7.2f |", angle);
        for (index=0; index<arraySize; index++)
        {
            launch.velocity = launchVelocityArr[index];
            launch.angle = angle;
            maxRange = get_trajectory_distance(&launch);
            maxHeight = get_trajectory_height_by_distance(&launch, maxRange/2);
            printf("%9.2f  |  %9.2f     |", maxRange, maxHeight);
        }

        printf("\n");
    }
    printf("==========");
    for (index=0; index<arraySize; index++) {
        printf("=============================");
    }
    printf("\n");
}