#include <stdio.h>
#include <stdlib.h>


#define g 9.8

int target_dist;
int velocity;
int obstacle_dist;
int obstacle_height;


int main()
{
    print_table();

    get_user_input();

    do_caltulation();

    provide_recommendation();


    exit(1);

}

void print_table()
{




}

void get_user_input()
{
    printf("Please enter the target distance/n");
    scanf("%d", dist);
    printf("Is there any obstacles? y or n /n");



}

void do_caltulation()
{
    get_maxheight();




}

void provide_recommendation()
{


}


