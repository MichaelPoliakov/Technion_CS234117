#include <stdio.h>
#include <math.h>

#define N 50
#define M 50
#define RECT 4
#define TOP 0
#define LEFT 1
#define BOTTOM 2
#define RIGHT 3
#undef max
#undef min


void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]);
int sum_rect(int integral_image[][M], int rect[RECT]);
void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]);
void print_array(int a[N][M], int n, int m);
int max(int a, int b);
int min(int a, int b);



int main() {
    int n = 0, m = 0;
    printf("Enter image dimensions:\n");
    scanf("%d%d", &n, &m);

    int image[N][M] = {{0}};
    printf("Enter image:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &image[i][j]);
        }
    }

    int h = 0, w = 0;
    printf("Enter sliding window dimensions:\n");
    scanf("%d%d", &h, &w);

    int integral_image[N][M] = {{0}};
    compute_integral_image(image, n, m, integral_image);
    printf("Integral image is:\n");
    print_array(integral_image, n, m);

    int average[N][M];
    sliding_average(integral_image, n, m, h, w, average);
    printf("Smoothed image is:\n");
    print_array(average, n, m);

    return 0;
}

void print_array(int a[N][M], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", a[i][j]);
            if (j != m-1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void compute_integral_image(int image[][M], int n, int m, int integral_image[][M])
{
    integral_image[0][0] = image[0][0];
    for (int i = 1; i < n; i++)
        integral_image[i][0] = integral_image[i - 1][0] + image[i][0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < m; j++)
            integral_image[i][j] = integral_image[i][j - 1] + ((i - 1 >= 0) ? integral_image[i - 1][j] - integral_image[i-1][j-1] : 0) + image[i][j];
    }
}

int sum_rect(int integral_image[][M], int rect[RECT])
{
    return integral_image[rect[BOTTOM]][rect[RIGHT]] - integral_image[rect[TOP] - 1][rect[RIGHT]] - integral_image[rect[BOTTOM]][rect[LEFT] - 1] +
    integral_image[rect[TOP] - 1][rect[LEFT] - 1];
}

void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M])
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            int rect[RECT] = {/*up*/    max(0, i - h / 2),
                            /*left*/    max(0, j - w/2),
                            /*bottom*/  min(n-1, i + h/2),
                            /*right*/   min(m-1, j + w/2)};
            average[i][j] = (int) round(sum_rect(integral_image, rect) / (double) (h*w));
        }
    }

}

int max(int a, int b)
{
    return (a < b) ? b : a;
}

int min(int a, int b)
{
    return (a <= b) ? a : b;
}