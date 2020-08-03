#include<stdio.h>
#include<cs50.h>
#include <string.h>
#include<math.h>

int count_letters(string s);                            //function declereations
int count_words(string s);
int count_sentences(string s);

int main(void)
{
    string s = get_string("Text : ");
    int letters = count_letters(s);
    int words = count_words(s);
    int sentences = count_sentences(s);
    float w = (float) 100 / words;
    float L = letters * w;
    float S = (float) sentences / words;
    S *= 100;
    float I = 0.0588 * L - 0.296 * S - 15.8;            //The Coleman-Liau index formula
    int index = round(I);

    //printf ("%i \n %i \n %i \n %i",letters,words,sentences,index);
    if (index < 1)                                      //printing segmet
    {
        printf("Before Grade 1");                       //for grade being less than 1
    }
    else if (index >= 1 && index <= 16)                 //for grade being in between 1 and 16
    {
        printf("Grade %i", index);
    }
    else                                                //for grade over 16
    {
        printf("Grade 16+");
    }
    printf("\n");
}

int count_letters(string s)                             //count the number of letters
{
    int letters = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if ('a' <= s[i] && s[i] <= 'z')
        {
            letters++;
        }
        if ('A' <= s[i] && s[i] <= 'Z')
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string s)                               //count the number of words
{
    int words = 1;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string s)                           //count the number of sentences
{
    int sentences = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}