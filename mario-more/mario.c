#include <cs50.h>
#include <stdio.h>

// Announcing functions
int get_height(void);
int create_pyramid(int height);

int main(void)
{
    int height = get_height();
    create_pyramid(height);
}

// prompts user to input the height and declines values outside 1-8

int get_height(void)
{
    int height;
    do
    {
        height = get_int("Height:");
    }
    while (height <= 0 || height > 8);
    return height;
}

int create_pyramid(int height)
{
    int maxHeight = 8;
    int currentFloor;
    for (int i = 1; i <= height; i++)
    {
        // calculation and printing spaces needed
        int spaces = height - i;
        for (int s = 0; s < spaces; s++)
        {
            printf(" ");
        }

        // Creation the left part of the pyramid
        for (int left = 0; left < i; left++)
        {
            printf("#");
        }

        // Spaces in between
        printf("  ");

        // Creation the right part of the pyramid
        for (int right = 0; right < i; right++)
        {
            printf("#");
        }
        printf("\n");
    }
    // non void functions in c need a return value
    return 0;
}