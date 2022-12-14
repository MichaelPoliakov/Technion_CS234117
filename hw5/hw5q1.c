#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#undef max

int evaluate_the_second_most_big(int arr[], int n, int a, int big);
int max(int a, int b);

int main() {
    int n;
    printf("Please enter length:\n");
    if (scanf("%d", &n) != 1) exit(1);
    int * arr = (int*) malloc(sizeof(int) * n);
    if(arr == NULL) exit(1);
    printf("Please enter array:\n");
    for (int a = 0; a < n; a++)
        if (scanf(" %d", &arr[a]) != 1) exit(1);
    printf("The second-greatest is:\n%d", evaluate_the_second_most_big(arr, n, n - 1, INT_MIN));
    return 0;
}

int evaluate_the_second_most_big(int arr[], int n, int a, int big)
{
    if(a == 1) {
        if (max(arr[0], arr[1]) <= big)
            return (max(arr[0], arr[1]));
        else
        {
            if((arr[0] <= big && big <= arr[1]) || (arr[1] <= big && big <= arr[0]))
                return big;
            else
                return -max(-arr[0], -arr[1]);
        }
    }
    return evaluate_the_second_most_big(arr, n, a - 1, max(arr[a], big));
}

int max(int a, int b)
{
    return (a <= b) ? b : a;
}