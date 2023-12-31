#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // file name that user input
    char *file_name = argv[1];
    // open memory card
    FILE *file_pointer = fopen(file_name, "r");

    if (file_pointer == NULL)  //  file cannot be open
    {
        printf("Error: cannot open %s\n", file_name);
        return 2;
    }

    FILE *jpeg = NULL;
    char jpeg_name[8];   // ###.jpg\0
    BYTE buffer[512];    // auxiliary array
    int count = 0;       // jpg file number

    // repeat until EOF
    while (fread(buffer, 512, 1, file_pointer) == 1)
    {
        // check first four bytes (= signatures)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // end of JPEG file
            if (count != 0)
            {
                fclose(jpeg);
            }

            // make JPEG file
            sprintf(jpeg_name, "%03i.jpg", count);
            // open JPEG file
            jpeg = fopen(jpeg_name, "w");
            // count file number
            count++;
        }

        // already
        if (count != 0)
        {
            // write JPEG file
            fwrite(buffer, 512, 1, jpeg);
        }
    }

    // close all remaining files
    fclose(file_pointer);
    fclose(jpeg);

    return 0;
}