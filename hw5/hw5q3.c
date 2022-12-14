/*****************************************************************************
 *		Recursive  Merge-Sort, using Dynamicly Allocated Arrays	     *
 *                                                                   *
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 2

unsigned int  ReadSize(void);
int* ReadVec(unsigned int*);
int ReadSum (int *);
void sort(int*, unsigned int);
void merge2halfs(int*, unsigned int, unsigned int);
bool search_sum_of_2_x(const int *arr, unsigned int initial, unsigned int len, int x, unsigned int);
bool search_sum_x(const int arr[], unsigned int n, int x);

int main(void)	/* Here, we are not limited to a fix-sized array */
{
    unsigned int n = ReadSize();
    int *arr = ReadVec(&n);
    sort(arr, n);
    int x = ReadSum(arr);
    if(search_sum_x(arr, n, x))
        printf("Such elements do exist.");
    else
        printf("Such elements do not exist.");
    free(arr);
    return 0;
}

unsigned int ReadSize(void)
{
    unsigned int num;
    printf("Please enter length:\n");
    if (scanf("%u", &num) != 1) exit(1);
    return num;
}

int ReadSum (int * arr)
{
    int num;
    printf("Please enter sum:\n");
    if (scanf("%d", &num) != 1)
    {
        free(arr);
        exit(1);
    }
    return num;
}

void sort(int* arr, unsigned int size)
{
    int  *low = arr;            unsigned int lsz = size / 2;
    int  *hi = arr + lsz;       unsigned int hsz = size - lsz;
    if (size < N) return;
    sort(low,lsz); sort(hi,hsz);
    merge2halfs(arr, lsz, hsz);
    return;
}

void merge2halfs (int* arr, unsigned int low_sz, unsigned int hi_sz)
{
    unsigned int i = 0, j = 0, k = 0;
    int *low = arr, *hi = arr + low_sz, *tmp = malloc(low_sz * sizeof(int));
    if (tmp == NULL) exit(1);
    while (i < low_sz)
        tmp[k++] = low[i++];	  /* Copy the lower part */
    for (i = k = 0; i < low_sz && j < hi_sz;) /* Merge */
        arr[k++] = (tmp[i] < hi[j]) ?  tmp[i++] : hi[j++];
    while (i < low_sz)
        arr[k++] = tmp[i++]; /* i == low_sz --> hi[] lmnts o.k. */
    free(tmp);
}


int *ReadVec(unsigned int *size)
{
    int *vec = malloc(*size * sizeof(int)); unsigned int i;
    if (vec == NULL) exit(1);
    printf("Please enter array:\n");
    for (i = 0; i < *size && (scanf("%d", &vec[i]) > 0); ++i);		/* Null body */
    *size = i;	/* The actual size */
    return vec;
}

bool search_sum_of_2_x(const int *arr, unsigned int initial, unsigned int len, int x , unsigned int skip_idx) //O(n)
{
    unsigned int down = initial, up = len - 1;
    while(down < up)
    {
        if(down == skip_idx) down++;
        if(up == skip_idx) up--;
        if ((arr[down] + arr[up]) < x) down++;
        else if ((arr[down] + arr[up]) > x) up--;
        else
            return true;
    }
    return false;
}

bool search_sum_x(const int arr[], unsigned int n, int x) //O(n^2)
{
    for (unsigned int i = 0; i < n; i++)
    {
        int pair = x - arr[i];
        if (search_sum_of_2_x(arr, 0, n, pair, i))
            return true;
    }
    return false;
}