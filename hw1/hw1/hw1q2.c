//
// Created by Michael Poliakov on 4/28/21.
//
// input:  letter and string.
//
//output:  times letter appears in.
/*-------------------------------------------------------------------------
  Calculating how many times a given char appears in a given sentence.
 -------------------------------------------------------------------------*/
// Attention: program evaluating chars ASCII value, please ignore the fact that some compilers return warnings
// is such case.


#include <stdio.h>


char ensure_upper_case(char c);


int main()
{
    printf("Enter letter to count:\n");
    char letter = 0;
    if (scanf("%c", &letter) != 1) return 1;
    letter = ensure_upper_case(letter);
    if (letter == 0) return 0;
    printf("Enter the char sequence:\n");
    unsigned char count = 0;
    char i = 0;
    scanf("%c", &i);
    while (i != '$')
    {
        if (ensure_upper_case(i) == letter) count++;
        scanf("%c", &i);
    }
    printf("The letter appeared %d times\n", count);
    return 0;
}


char ensure_upper_case(char c)
{
    if ('a' <= c && c <= 'z')
        return (char)((c-'a')+'A');
    else if ('A' <= c && c <= 'Z')
        return c;
    else
        return 0;
}

