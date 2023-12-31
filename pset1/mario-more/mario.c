#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // left side
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (j + 1 < height - i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        // 2 spaces
        printf("  ");

        // right side
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}