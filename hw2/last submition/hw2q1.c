//
// Created by Michael Poliakov on 5/5/21.
//

#include <stdio.h>
#include <stdlib.h>


#define N1 3
#define N2 10
#define DIGITS 0
#define LETTERS 1
#define SPACES 2

void printGivenParamsToTheOutput(
        char ch,
        int asciiCode,
        int asciiCodePowTwo,
        int difference,
        int unitDigitOfDiff);

void printResults(
        int digitsCounter,
        int lettersCounter,
        int spacesCounter);


char my_scan();


void counting(
        char ch,
        unsigned short count[]);

/*-------------------------------------------------------------------------
Describe every character in given string and pay special attention to
lower letters.
 -------------------------------------------------------------------------*/


int main()
{
    char ch;
    int asciiCode = 0, asciiCodePowTwo, difference, unitDigitOfDiff;
    unsigned short count[N1] = { 0 }; // 0.Digits  1.Letters  2.Spaces Counter
    ch = my_scan(); // Verify scan success.
    while(ch != ';')
    {
        counting(ch, count);
        difference = (int)ch - asciiCode;
        asciiCode = (int)ch;
        asciiCodePowTwo = asciiCode*asciiCode;
        unitDigitOfDiff = difference % N2;
        printGivenParamsToTheOutput(ch, asciiCode, asciiCodePowTwo, difference, unitDigitOfDiff);
        ch = my_scan();
    }
    printResults(count[DIGITS], count[LETTERS], count[SPACES]);


    return 0;
}


// text out.
void printResults(int digitsCounter, int lettersCounter, int spacesCounter)
{
    printf("Number of digits received: %d\n", digitsCounter);
    printf("Number of letters received: %d\n", lettersCounter);
    printf("Number of spaces received: %d\n", spacesCounter);
}


// text out.
void printGivenParamsToTheOutput(char ch, int asciiCode, int asciiCodePowTwo,
                                 int difference, int unitDigitOfDiff) {
    printf(
            "%c%10d%10d%10d%10d\n", ch, asciiCode,
            asciiCodePowTwo, difference, unitDigitOfDiff
    );
}


// count numbers, English letters, spaces.
void counting(char ch, unsigned short count[])
{
    if (('0' <= ch) && (ch <= '9'))
        count[DIGITS]++;
    if ((('A' <= ch) && (ch <= 'Z')) || (('a' <= ch) && (ch <= 'z')))
        count[LETTERS]++;
    if ((int)ch == (int)' ')         // the 'space' char, identically to ch==32.
        count[SPACES]++;
}


// security way to use ScanFormat function.
char my_scan()
{
    char ch1;
    if (scanf("%c", &ch1) < 1)
    {
        printf("\nERROR!\n");
        exit(1);
    }
    return ch1;
}