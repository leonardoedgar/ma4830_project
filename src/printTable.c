#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define g 9.8
#define PI 3.14

void print_table();

// typedef struct table
// {
//     int *index;  // Augmentation number
//     int *degree; // Degree range
//     int *max_height;
//     int *max_range;
// } table;

int main(void)
{
    // table *mortarTable = malloc(4 * sizeof(table));
    int index[5] = {0, 1, 2, 3, 4};
    int degrees[10] = {40, 45, 50, 55, 60, 65, 70, 75, 80, 85};
    int velocities[5] = {110, 115, 120, 125, 130};
    float rad, time, max_height, max_range;

    print_table();

    for (int degree = 40; degree < 90; degree += 5)
    {
        printf("|   %-5d|", degree);
        for (int speed = 110; speed < 135; speed += 5)
        {
            rad = degree * PI / 180;
            time = 2 * speed * sin(rad) / g;
            max_range = speed * cos(rad) * time;
            max_height = 0.5 * pow(speed, 2) * pow(sin(rad), 2)/ g;

            printf("%9.2f  |%9.2f   |",max_range, max_height);
        }
        
        printf("\n");
    }

    return 0;
}

void print_table()
{
    /************************************************************
     * This function will print out a table of maximum range and 
     * maximum height versus launching angles within 40~80 
     * degrees at different speed (augmentation number)
     * 
     * Param: a list containing:
     *      1. Augmentation number, [0, 1, 2, 3, 4];
     *      2. Launching velocity, [110, 115, 120, 125, 130];
     *      3. Degree ranges 40~85 degrees, with step 5;
     *      4. Max_ranges and max_heights respecttively;
     * 
     * Return: NULL
     ***********************************************************/

    printf("=======================================================================================================================================\n"); 
    printf("|        |     Augmentation 0     |     Augmentation 1     |     Augmentation 2     |     Augmentation 3     |     Augmentation 4     |\n");
    printf("| Degree |------------------------|------------------------|------------------------|------------------------|------------------------|\n"); 
    printf("|        | Max_range | Max_height | Max_range | Max_height | Max_range | Max_height | Max_range | Max_height | Max_range | Max_height |\n");
    printf("|--------|------------------------|------------------------|------------------------|------------------------|------------------------|\n"); 


}
