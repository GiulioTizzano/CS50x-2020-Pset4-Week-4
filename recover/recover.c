#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 512
bool is_jpeg = false;
int pictures = 0;

int main(int argc, char *argv[])
{
    //ensuring user is running program with two words at prompt
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    //recording file name required
    char *o_file = argv[1];
      
    //opening file

    
    FILE *file_input = fopen(o_file, "r");
    FILE *file_output = NULL;
    //read three first bytes of the file "file"
    unsigned char image[BUFFER_SIZE];


    //fread(data, size, number, input)
    //loop until end of card memory
    while (fread(image, BUFFER_SIZE, 1, file_input) == 1)
    {
        //check if the first three array values are 0xff, 0xd8, 0xff
        if (image[0] == 0xff && image[1] == 0xd8 && image[2] == 0xff)
        {
            if (is_jpeg == true)
            {
                fclose(file_output);
            }
            else
            {
                is_jpeg = true;
            }

            char file[8];
            sprintf(file, "%03i.jpg", pictures);
            file_output = fopen(file, "a");
            pictures++;



        }

        if (is_jpeg == true)
        {
            fwrite(&image, BUFFER_SIZE, 1, file_output);
        }


    }
    fclose(file_input);
    fclose(file_output);

    return 0;


}
