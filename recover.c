#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    //if argc > 1
    if (argc < 2)
    {
        printf("Usage: ./recover Name.\n");
        return 1;
    }

    //if file doesn't open
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    // buffer
    BYTE *buffer = malloc(sizeof(uint8_t) * BLOCK_SIZE);
    if (buffer == NULL)
    {
        printf("Not enough memory to store the block.\n");
        return 1;
    }

    // N. of jpg
    int v = 0;

    FILE *tmpimg;
    char NAME_FILE[8];
    int check = 0;

    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // when a new jpg found
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (v > 0)  
            {
                fclose(tmpimg);
            }
            sprintf(NAME_FILE, "%03i.jpg", v);

            FILE *img = fopen(NAME_FILE, "w");
            if (img == NULL)
            {
                printf("Could not be created %s.\n", NAME_FILE);
                fclose(file);
                return 5;
            }

            tmpimg = img;
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, tmpimg);
            v++;
            check = 1;
        }
        // if no jpg found
        else if (check == 1)
        {
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, tmpimg);
        }
    }

    fclose(file);
    free(buffer);
    fclose(tmpimg);
    return 0;

}