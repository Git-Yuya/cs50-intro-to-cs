#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start, end, years, n;

    // TODO: Prompt for start size
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    n = start;
    for (years = 0; n < end; years++)
    {
        n = n + (n / 3) - (n / 4);
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);

    return 0;
}