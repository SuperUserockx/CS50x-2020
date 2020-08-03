#include<stdio.h>
#include<cs50.h>
#include<string.h>

int main(int argc, string argv[])
{
    if (argc != 2)                                  //check for correct number of arguments
    {
        printf("Usage: ./substitution key \n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)                 //check for correct key length
    {
        printf("Key must contain 26 characters. \n");
        return 1;
    }
    
    string key = argv[1];
    
    for (int i = 0; i < strlen(key); i++)
    {
        if (!(key[i] >= 'a' && key[i] <= 'z'))      //check for invalid characters in the key
        {
            if (!(key[i] >= 'A' && key[i] <= 'Z'))
            {
                printf("Invalid characters in key");
                return 1;
            }
        }
        for (int j = i + 1; j < strlen(key) - 1; j++)
        {                                           
            if (key[i] == key[j])
            {
                printf("Key has duplicate characters");
                return 1;
            }
        }
        
    }
    
    string s = get_string("plaintext:  ");              //taking user input
    
    
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            //printf("%c", s[i]);
            char c = s[i];
            c = c - 97;
            if (key[(int) c] >= 'a' && key[(int) c] <= 'z') //coverting the input if the input is in small characters
            {
                s[i] = key[(int) c];
            }
            else
            {
                s[i] = key[(int) c] + 32;
            }
            
        }
        else if (s[i] >= 'A' && s[i] <= 'Z')                //converting the input if the unput is in capital characters
        {
            char c = s[i];
            c = c - 65;
            if (key[(int) c] >= 'A' && key[(int) c] <= 'Z')
            {
                s[i] = key[(int) c];
            }
            else
            {
                s[i] = key[(int) c] - 32;
            }
        }
    }
    printf("ciphertext: %s\n", s);                      //printing the outpur of the program
}