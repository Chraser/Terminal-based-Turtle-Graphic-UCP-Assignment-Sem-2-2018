#include "utility.h"
#include <string.h>
/*
Purpose: To change every character in the string to upper case
         if it isn't already in upper case. This allows for 
         commands to be in either lower cases or upper cases
         or both while only checking if string is a valid commands
         in upper cases
How it works: It checks the ASCII code of the letter being in the
              range of 97 to 122 inclusive which are ASCII code 
              for upper case letters
*/
void changeToUpperCase(char* string)
{
    int ii;
    for (ii = 0; ii < strlen(string); ii++)
    {
        if(string[ii] >= 97 && string[ii] <= 122)
        {
            string[ii] = string[ii] - 32;
        }
    }
}

/*
Purpose: To round a real number to the nearest integer so that
         the line() function can use that number
How it works: It checks the difference between the real number and
              the integer representation of the real number. If 
              the difference is less than 0.5, truncate the real number
              else truncate the real number and add 1
*/
int round(double realNum)
{
    int intNum;
    if((realNum - (double)((int)realNum)) < 0.5)
    {
        intNum = (int)realNum;
    }
    else
    {
        intNum = (int)realNum + 1;
    }
    return intNum;
}