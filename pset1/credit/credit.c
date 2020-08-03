#include<stdio.h>
#include<cs50.h>

int main(void)
{
    long card = get_long("Number : ");
    long card_bac = card;
    int odd = 0;
    int even = 0;
    bool flag = false;
    if (card < 1000000000000)           //check for correct length of inpur number
    {
        printf("INVALID\n");
    }
    else
    {
        while (card != 0)               //Check for a valid card
        {
            if (flag == false)
            {
                odd += card % 10;
                card /= 10;
                flag = true;
            }
            else
            {
                int s = card % 10;
                s *= 2;
                while (s != 0)
                {
                    even += s % 10;
                    s = s / 10;
                }
                card /= 10;
                flag = false;
            }
        }

        int sum = odd + even;
        if (sum % 10 == 0)
        {
            while (card_bac > 100)
            {
                card_bac /= 10;
            }
            if (card_bac == 34 || card_bac == 37)
            {
                printf("AMEX\n");                           //check for AMEX card
            }
            else if (card_bac >= 51 && card_bac <= 55)
            {
                printf("MASTERCARD\n");                     //check for MASTERCARD
            }
            else
            {
                card_bac /= 10;
                if (card_bac == 4)
                {
                    printf("VISA\n");                       //check for VISA card
                }
                else
                {
                    printf("INVALID\n");                    //case for an invalid type number with correct checksum
                }
            }

        }
        else
        {
            printf("INVALID\n");                            //default condition for card being invalid for checksum
        }
    }

}