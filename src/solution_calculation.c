#include <stdio.h>
#include <stdlib.h>
#include <math.h> //we need this for calculation
#include <stdbool.h> //we need this library for bool

#define g 9.8
#define pi 3.14 //pre-defined constants

int main()
{
    double distance, terrain_height, terrain_distance_from_mortar; //variables we discussed
    double angle[5][2]; //5 velocities, one velocity have 2 cases (bigger degree and smaller degree)
    bool is_terrain_exist, is_solution_found; //variables we discussed
    printf("Please enter the target distance\n");
    scanf("%lf", &distance);
    printf("Is there any obstacle? (yes put 1, no put 0)\n");
    scanf("%d", &is_terrain_exist);
    if(is_terrain_exist == 1)
    {
        printf("Please enter the terrain height\n");
        scanf("%lf", &terrain_height);
        printf("Please enter the terrain distance from mortar\n");
        scanf("%lf", &terrain_distance_from_mortar);             // aboves are all interface functions for my testing, you could remove them and write your owns.
    }

    get_collision_free_trajectory(angle,is_terrain_exist, terrain_height, terrain_distance_from_mortar, distance, is_solution_found); //call my function


    return(0);

}


//okay, my function is to input everything the user knows (including obstacles information), and then return all possible degrees (and corresponding velocities (argumentation numbers)).
void get_collision_free_trajectory(double angle[5][2], bool is_terrain_exist, double terrain_height, double terrain_distance_from_mortar, double distance, bool is_solution_found)
{
    double time[5][2]; //for each velocity, there are always two cases for the angles and times. (45 degree is also considered two cases)
    double v[5] = {110.0, 115.0, 120.0, 125.0, 130.0};
    double height_till_terrain[5][2]; //for each case, the shell's vertical position when reaching the wall
    int i, j, k = 0; //local counters

    if(is_terrain_exist == 0) //check for if there's no obstacle
    {
        terrain_height = 0;
        terrain_distance_from_mortar = 0;
    }

    for(i=0; i<5; i++)
    {
        angle[i][0] = (asin(g * distance / (v[i] * v[i])) * (180.0 / pi) ) / 2.0 ; //angle a is the smaller angle between the two cases
        angle[i][1] = 90 - angle[i][0]; //angle b is the larger angle between the two cases
        //all angles are in degrees

        time[i][0] = (2 * (v[i]) * sin(angle[i][0])) / g;//time a is related to angle a (actually no need to use, just for reference)
        time[i][1] = (2 * (v[i]) * sin(angle[i][1])) / g;//time b is related to angle b (actually no need to use, just for reference)

        height_till_terrain[i][0] = terrain_distance_from_mortar * tan(angle[i][0] * pi / 180) - (g * terrain_distance_from_mortar * terrain_distance_from_mortar) / (v[i] * v[i] * cos(angle[i][0] * pi / 180) * cos(angle[i][0] * pi / 180) * 2);
        //calculate the shell's vertical position when reaching the wall
        height_till_terrain[i][1] = terrain_distance_from_mortar * tan(angle[i][1] * pi / 180) - (g * terrain_distance_from_mortar * terrain_distance_from_mortar) / (v[i] * v[i] * cos(angle[i][1] * pi / 180) * cos(angle[i][1] * pi / 180) * 2);
        //calculate the shell's vertical position when reaching the wall (higher degree ones)
    }

    for(i=0; i<5; i++) //check for if the shell knocked at the wall
    {
        for(j=0; j<2; j++)
        {
            if(height_till_terrain[i][j] < terrain_height)
            {
                angle[i][j] = 0; //kill all the situations which knocked at the wall
                k++;
            }
        }
    }

    if(k == 10) //if all shells knocked the wall, no solutions
    {
        is_solution_found = 0;
        printf("Sorry, there's no solutions.");
    }

    printf("Here are all the possible situations to shoot the target.\n");//these are for test printing, you could remove this for loop
    for(i=0; i<5; i++)
    {
        for(j=0; j<2; j++)
        {
            if(angle[i][j] != 0)
            {
                printf("velocity: %f\t angle: %f\n", v[i], angle[i][j]);
            }
        }
    }
}
