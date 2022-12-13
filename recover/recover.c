#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check for the user input
    if(argc != 2)
    {
        printf("Usage: ./recover /image \n");
        return 1;
    }
    // opeining odf the file
    FILE *file = fopen( argv[1], "r");
    // ensuring the file is not empty
    if(file == NULL)
    {
        printf("Error: cannot open %s\n", argv[1]);
        return 2;
    }
    //We initailize variables to carry out the recovery
    BYTE buffer[512];// stores the byte read from the file
    int count = 0;//counts the nuimber of files read
    FILE *img_address = NULL;// pointer to where the jpg will be stroed
    char Img_stored[8];// variable name used in storing the recovered bytes

    //We loop through the given file to recover the images
    while(fread(&buffer,512,1,file)==1)
    {
        // starts the search for the jpg using(0xff 0xd8 0xff 0xe*)
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if(!(count == 0))
            {
                fclose(img_address);
            }
            sprintf(Img_stored, "%03i.jpg",count);
            img_address = fopen(Img_stored , "w");
            count++;
        }
        //if the jpg is found then we save it to a file
        if(!(count == 0))
        {
            fwrite(&buffer,512,1,img_address);
        }
    }
    fclose(file);
    fclose(img_address);
    return 0;
}