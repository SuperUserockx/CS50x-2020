#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Height : ");       //to get input from the user
    }
    while (h < 1 || h > 8);
    for (int i = 0; i < h; i++)
    {
        for (int j = h - 1; j > i ; j--)    //print spaces to align the output
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)    //print left side of the '#'
        {
            printf("#");
        }
        printf("  ");
        for (int l = 0; l <= i; l++)    //print right side of the '#'
        {
            printf("#");
        }
        printf("\n");
    }
    
}