//
// Created by Michael Poliakov on 7/6/21.
//
#include <stdio.h>
#include <stdlib.h>


#define N 4
#define MAT {{0, 5, 2, 2},{1, 0, 1, 1},{1, 2, 0, 1},{1, 1, 2, 0}}
#define SOURCE 3
#define DESTINATION 2
#define INF 0xFFFFFFF


int best_path(int [][N], int*, int, int*, /*int*,*/ int, int*, int*, int, int, int);
void copy_arr(int [], const int [], int);
int get_num(const char *);
void get_mat(int [][N]);
void print_shortest_path(int*, int);

int main()
{
    int road[N][N] = /*MAT*/ {{ 0 }}; get_mat(road);
    int sol[N] = { 0 },
            best_sol[N] = { 0 },
            len_best_sol = 0,
            best_sol_cost = INF,
            visited[N] = { 0 },
            departure = /*SOURCE*/get_num("Please enter source city:\n"),
            destination = /*DESTINATION*/get_num("Please enter destination city:\n");
    visited[departure] = 1;
    best_path(road, sol, 0, best_sol, /*&len_best_sol,*/ 0, &best_sol_cost, visited,
              departure, departure, destination);
    while(best_sol[len_best_sol] != destination) len_best_sol++;
    len_best_sol += 1;
    print_shortest_path(best_sol, len_best_sol);
    return 0;
}

int best_path (int   road[][N],
               int   sol[N],
               int   len_sol,
               int   best_sol[N],
               /*int * len_best_sol,*/
               int   path_cost,
               int * best_sol_cost,
               int   visited[N],
               int   source,
               int   my_location,
               int   final_destination)
{
    //step
    sol[len_sol] = my_location;
    path_cost += road[source][my_location];

    //stop condition
    if((path_cost >= *best_sol_cost) || (my_location == final_destination)) return path_cost;

    //recursive program
    int j = N - 1, tmp_path_cost;
    while (j >= 0)
    {
        //backtracking
        if(visited[j]) {j--; continue;}

        //recursive move
        visited[j] = 1;
        tmp_path_cost = best_path(road, sol, len_sol + 1, best_sol, /*len_best_sol,*/ path_cost,
                                           best_sol_cost, visited, my_location, j,
                                           final_destination);
        visited[j] = 0;
        if(tmp_path_cost == -1) break;
        if(tmp_path_cost < *best_sol_cost)
        {
            *best_sol_cost = tmp_path_cost;
            copy_arr(best_sol, sol, N);
            if(*best_sol_cost == 1) return -1;  //anyway its the cheapest path as can be.
        }

        //return sol vector to  initial situation (pre-loop)
        j--;
    }
    return tmp_path_cost;
}
void copy_arr(int a[], const int b[], int len_b) {
    int i = (int) len_b;
    while (--i >= 0) a[i] = b[i];
}
int get_num(const char * msg)
{
    int ans;
    printf("%s", msg);
    if(scanf("%d", &ans) < 1) exit(1);
    return ans;
}
void get_mat(int matrix[N][N])
{
    printf("Please enter roads matrix:\n");
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if(scanf(" %d", &matrix[i][j]) < 1) exit(1);
}
void print_shortest_path(int * sol, int n)
{
    printf("The shortest path is:\n");
    for (int i = 0; i <= n - 2; i++)
        printf("%d ", sol[i]);
    printf("%d", sol[n - 1]);
}
