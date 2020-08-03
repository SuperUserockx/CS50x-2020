#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    if (argc < 2)                                                                                    //check for correct arguments
    {
        return 1;
    }
    FILE *file = fopen(argv[1], "r");                                                                   //opening orignal file
    BYTE buffer[512];
    int n = 0;
    int first = 0;
    FILE *img = NULL;
    char filename[] = "000.jpg";
    int temp = fread(buffer, 512, 1, file);
    while (fread(buffer, 512, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)      //check for jpg header
        {
            sprintf(filename, "%03i.jpg", n);
            n++;
            if (first != 0)
            {
                fclose(img);            //check if first image has been created or not
            }
            img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);
            first = 1;
        }
        else if (first != 0)
        {
            fwrite(buffer, 512, 1, img);
        }
        
    }
    fclose(img);                                                                                            //closing all the files
    fclose(file);
    return 0;

}
