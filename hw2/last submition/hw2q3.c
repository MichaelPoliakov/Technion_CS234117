//
// Created by Michael Poliakov on 5/5/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 25

void printOpenMessageForSudokuSize();
void printOpenMessageForSudokuSolution();
void printValidSolution();
void printBadSolution();
int get_sq_n();  //actually many ver. better to be unsigned int
void get_sudoko(int sudoko[N][N], int max);
bool checkSqr(int sudoko[N][N], int n, int sqrt_n);
bool checkRow(int sudoko[N][N], int n);
bool checkCol(int sudoko[N][N], int n);
//int sqrt(int x);


/*-------------------------------------------------------------------------
Gets sudoko solution and check is that sol` correct.
 sudoko table limited up to 25x25.
 -------------------------------------------------------------------------*/


int main()
{
    int n, sqrt_n, sudoko[N][N];
    printOpenMessageForSudokuSize();
    sqrt_n = get_sq_n(); // saving the sqrt, since receive n again is easy one step. tha next line...
    n = sqrt_n * sqrt_n;
    printOpenMessageForSudokuSolution();
    get_sudoko(sudoko, n); //save in 2 dimensions array the all sudoko solution.
    if (checkSqr(sudoko, n, sqrt_n) && checkRow(sudoko, n) && checkCol(sudoko,n))
        printValidSolution();
    else
        printBadSolution();
    return 0;
}

void printOpenMessageForSudokuSize(){
    printf("Please enter the size of your soduko:\n");
}
void printOpenMessageForSudokuSolution(){
    printf("Please enter your solution:\n");
}
void printValidSolution(){
    printf("Valid solution!\n");
}
void printBadSolution(){
    printf("Bad solution!\n");
}
int get_sq_n() //proper n is Natural quadratic number only.
{
    int a, arg;
    bool ok;
    do
    {
        if (scanf("%d", &a) != 1) //ASSUMPTION: scan <=25.
            continue;
        if (a <= 0) //Dealing in Real numbers only.
            continue;
        arg = 1;
        while (arg * arg < a) arg++;
        ok = (arg * arg == a);
    } while (!ok);
    return arg;
}
/*int sqrt(int x)
{
    int ans = 1;
    while (ans * ans < x) ans++;
    return ans;
}*/
void get_sudoko(int sudoko[N][N], int max)
{
    int  temp;
    for (int i = 0; i < max; i++)
    {
        for (int j = 0; j < max;)
        {
            if (scanf("%d", &temp) != 1) exit(1);
            if (temp == ' ') continue;
            if (temp == '\n') break;
            sudoko[i][j] = temp;
            j++;
        }
    }
}
bool checkRow(int sudoko[N][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        int hist[N] = { 0 };
        for (int j = 0; j < n; j++)
            hist[sudoko[i][j] - 1]++; //for ex. ∃ of 5  ⇒  hist[4] = 1
        for (int t = 0; t < n; t++)
        {
            if (hist[t] != 1)
                return false;
        }
    }
    return true;
}
bool checkCol(int sudoko[N][N], int n)
{
    for (int j = 0; j < n; j++)
    {
        int hist[N] = { 0 };
        for (int i = 0; i < n; i++)
            hist[sudoko[i][j] - 1]++;
        for (int t = 0; t < n; t++)
        {
            if (hist[t] != 1)
                return false;
        }
    }
    return true;
}
bool checkSqr(int sudoko[N][N],int n, int sqrt_n)
{
    for (int box_i = 0; box_i < n; box_i += sqrt_n)
    {
        for (int box_j = 0; box_j < n; box_j += sqrt_n)
        {
            int hist [N] = { 0 };
            for (int i = box_i; i < box_i + sqrt_n; i++)
            {
                for (int j = box_j; j < box_j + sqrt_n; j++)
                    hist[sudoko[i][j] - 1]++;
            }
            for(int t = 0; t < n; t++)
                if (hist[t] != 1) return false;
        }
    }
    return true;
}
