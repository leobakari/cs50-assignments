#include <cs50.h>
#include <stdio.h>

int get_startSize(void);
int get_endSize(int startSize);
int get_years(int startSize, int endSize);

int main(void)
{
    // TODO: Prompt for start size
    int startSize = get_startSize();
    // TODO: Prompt for end size
    int endSize = get_endSize(startSize);
    // TODO: Calculate number of years until we reach threshold
    int years = get_years(startSize, endSize);
    // TODO: Print number of years
    printf("Years: %i\n", years);
}

int get_startSize(void)
{
    int startSize = 0;
    int minSize = 9;
    do
    {
        startSize = get_int("Start size:");
    }
    while (startSize < minSize);
    return startSize;
}

int get_endSize(int startSize)
{
    int endSize;
    do
    {
        endSize = get_int("End size:");
    }
    while (endSize < startSize);
    return endSize;
}

int get_years(int startSize, int endSize)
{
    int currSize = startSize;
    int birthRate;
    int deathRate;
    int populationGrowth;
    int years = 0;
    while (currSize < endSize)
    {
        birthRate = currSize / 3;
        deathRate = currSize / 4;
        populationGrowth = birthRate - deathRate;
        currSize = currSize + populationGrowth;
        years++;
    }
    return years;
}