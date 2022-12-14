//
// Created by Michael Poliakov on 5/5/21.
//

#include <stdio.h>
#include <stdlib.h>


#undef min
#define UP_RESTRICT 1E9
#define SIZE_OF_HIST (short) ('z' - 'a' + 1)
#define N1 3


void printThreeDigitsOpenMessage();
void printResults(int avg, int rootOfMinNum, int avgPowTwoRootOfMinNum);
void printCharactersOpenMessage();
void printDataPerGivenCharAsInput(char ch, int numberOfTimesAppeared);
void printNumberOfOtherCharsAppeared(int numberOfOtherCharsAppeared);
int average(int a, int b, int c);
int min(int a, int b);
int absolute(int a);
int root(int a);
long long int power(int base, int exponent);
void characterAnalysis();

/*-------------------------------------------------------------------------
PART I: Gets three variables, and print kind of math multilation.
PART II: Counting regular letters from given input.
 -------------------------------------------------------------------------*/

int main()
{
    //PART I
    printThreeDigitsOpenMessage();
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != N1) exit(1);
    int avg = average(a, b, c),
        pos_total_min = absolute(min(a, min(b, c))); // math operation: |min{a,b,c}|
    printResults( avg, root(pos_total_min), (int) power(avg, pos_total_min));

    //PART II
    characterAnalysis();
    return 0;
}


// arithmetical mean value of {a,b,c}
int average(int a, int b, int c)
{
    return (a + b + c) / N1;
}

// math operation: min{a,b}
int min(int a, int b)
{
    return (a < b) ? a : b;
}

// math operation: |a|
int absolute(int a)
{
    return (a < 0) ? -a : a;
}

// math operation: √(a) iff ∈ℕ, -1 if not.
int root(int a)
{
    if (a < 0)
        return -1;
    else
        if (a == 0)
            return 0;
        else
        {
            int arg = 1;
            while (arg * arg < a) arg++;
            return (arg * arg == a) ? arg : -1;
        }
}

// math operation: a^b
long long int power(int base, int exponent)
{
    if (base < 0 || exponent < 0)
        return -1;
    if (exponent == 0) // Take advantaged of the assumption that zero in
        // power of zero in ours HW is 1, even though mathematical is not true.
        return 1;
    if (base == 0)
        return 0;
    long long int res = base;
    while (exponent > 1)
    {
        if ((long double) res > UP_RESTRICT / base) // 'base' strictly
            // positive.
        {
         res = -1;
         break;
        }
        res *= base;
        exponent--;
    }
    return res;
}

// counting lower case letters on input string.
void characterAnalysis()
{
    printCharactersOpenMessage();
    int cnt[SIZE_OF_HIST] = { 0 }, cnt_out =  0;
    char ch;
    while (scanf("%c", &ch) != EOF)
    {
        if (ch == '\n' || ch == '\r')  //ignore newline
            continue;
        if ('a' <= ch && ch <= 'z')
            cnt[(int)(ch - 'a')]++;
        else
            cnt_out++;
    }
    for (short i = 0; i < SIZE_OF_HIST; i++) //reading histogram of small
    // letters & printing it out. 0 represents a, 1 rep` b and so on..
         printDataPerGivenCharAsInput((char)(i + 'a'), cnt[i]);
    printNumberOfOtherCharsAppeared(cnt_out);
}

// text
void printThreeDigitsOpenMessage()
{
    printf("Please enter three integers:\n");
}

// print out: three numbers as their name.
void printResults(int avg, int rootOfMinNum, int avgPowTwoRootOfMinNum){
    printf("%d %d %d\n", avg, rootOfMinNum,avgPowTwoRootOfMinNum);
}

// text
void printCharactersOpenMessage()
{
    printf("Please enter your character set:\n");
}

// text. used in part II.
void printDataPerGivenCharAsInput(char ch, int numberOfTimesAppeared){
    printf(
            "letter %c appeared %d time in the given set of characters\n",
            ch, numberOfTimesAppeared
    );
}

// text
void printNumberOfOtherCharsAppeared(int numberOfOtherCharsAppeared){
    printf(
            "number of other characters in the given set was: %d\n",
            numberOfOtherCharsAppeared
    );
}

