//
// Created by Michael Poliakov on 5/28/21.
//
//
// Created by Michael Poliakov on 5/27/21.
//
/*-------------------------------------------------------------------------
    Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
/*-------------------------------------------------------------------------
    Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11

/*-------------------------------------------------------------------------
    Function declaration
-------------------------------------------------------------------------*/
void print_welcome();
void print_enter_board_size();
void print_board(char board[N][N], int n);
void print_player_turn(int player_index);
void print_error();
void print_winner(int player_index);
void print_tie();
int get_board_size();
int setup_new_board(char boards[][N]);
int doing_move_step(int player_index, char board[][N], int n, int step_num);
int verify_right_step(char board[][N], int n, int i, int j);
bool check_looser(int player_index, char board[][N], int n);
char player_sign(int player_index);
void copy_arr(char in_arr[][N], char out_arr[][N], int n);
int step_to_player_index(int step_num);
bool right_undo(int undo, int step_num);
bool diagonals_check(char board[N][N], int n, char sign);
bool rows_columns_check(char board[N][N], int n, char sign);
int partner_index(int player_idx);
/*-------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/

//main function. Mange move counting and end of game.
//13 lines
int main()
{
    char board[N*N*N][N] = { {0} };
    int n = setup_new_board(board), step_num = 0;
    while (step_num < n * n)
    {
        int players_index = step_to_player_index(step_num);
        print_player_turn(players_index);     //recall that:  1 - 1st player, 2 - 2nd player.
        step_num += doing_move_step(players_index, &board[step_num * N], n, step_num);
        print_board(&board[step_num * N], n);
        if (check_looser(players_index, &board[step_num * N], n)) {
            print_winner(partner_index(players_index));
            return 0;
        }
    }
    if(!check_looser(step_to_player_index(step_num + 1), &board[step_num * N], n))
        print_tie();
    return 0;
}



//getting the size of the board game
// 8 lines
int get_board_size()
{
    int n=0;
    print_welcome();
    print_enter_board_size();
    while (scanf("%d", &n) != 1)
        print_error();
    // assuming board size less or equal to N=11.
    return n;
}



//establish new board. and printing out.
// 6 lines
int setup_new_board(char board[][N])
{
//Any place that used for the game, execute with '_'.
//All other 'free spaces' that left in the matrix set to zero.
    int n = get_board_size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            board[i][j] = '_';
    }
    print_board(board, n);
    return n;
}



// returns: how many turns(steps) back should we go. Meaning, undo value.
// OR +1 - for success.
// 12 lines
int doing_move_step(int player_index, char board[][N], int n, int step_num)
{
    int row_or_undo = -1, col = -1;
    while(col < 0){
        while (scanf("%d", &row_or_undo) < 1 || (row_or_undo < 0 && !right_undo(row_or_undo, step_num)))
            print_error();
        if (row_or_undo < 0 && right_undo(row_or_undo, step_num)) // col is unused, garbage
            return row_or_undo;
        if (scanf("%d", &col) < 1 || verify_right_step(board, n, row_or_undo - 1, col - 1) != 0) {
            print_error();
            row_or_undo = col = -1;
        }
    }
    copy_arr(board, &board[N], n);
    board[N + row_or_undo - 1][col - 1] = player_sign(player_index);
    return 1;
}


//convert player index to player sign.
//1 lines
char player_sign(int player_index){
    return (player_index == 1) ? 'X' : 'O';  // 1 - 1st player, 2 - 2nd player.
}


//duplicate old board.
// 3 lines
void copy_arr(char in_arr[][N], char out_arr[][N], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            out_arr[i][j] = in_arr[i][j];
    }
}



//checking if their are a looser. INPUT: player index and boars. OUTPUT: Does he loose? (true/false)
//2 lines
bool check_looser(int player_index, char board[N][N], int n)
{
    char p_sign = player_sign(player_index);
    return (diagonals_check(board, n, p_sign) || rows_columns_check(board, n, p_sign));
}


//checking if one of diagonals are marked oll with the player`s sign.
//7 lines
bool diagonals_check(char board[N][N], int n, char sign)
{
    int count_major_diagonal = 0, count_minor_diagonal = 0;
    for (int i = 0; i < n ; i++) {
        if (board[i][i] == sign)
            count_major_diagonal++;
        if (board[i][n - 1 - i] == sign)
            count_minor_diagonal++;
    }
    return (count_major_diagonal == n || count_minor_diagonal == n);
}


//Does one of row or columns of the given board full with given sign.
//10 lines
bool rows_columns_check(char board[N][N], int n, char sign)
{
    for (int i = 0; i < n ; i++)
    {
        int counter_for_row = 0, counter_for_col = 0;
        for (int j = 0; j < n; j++) {
            if (board[i][j] == sign)
                counter_for_row++;
            if (board[j][i] == sign)
                counter_for_col++;
        }
        if (counter_for_row == n || counter_for_col == n)
            return true;
    }
    return false;
}


//error type dictionary: 1 - fatal overflow, 2 - game board overflow, 3 - no room for answer.
// 0 - correct input.
//6 lines
int verify_right_step(char board[N][N], int n, int i, int j)
{
    if (i < 0 || j < 0 || i > N || j > N)
        return 1;
    else if (i >= n || j >= n)
        return 2;
    else
        return (board[i][j] == '_') ? 0 : 3;
}


//print welcome message
//1 lines
void print_welcome()
{
    printf("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n");
}


//print message to enter board size
//1 lines
void print_enter_board_size()
{
    printf("Please enter board size (1 to %d):\n", N);
}


//print the board
//7 lines
void print_board(char board[N][N], int n)
{
    printf("\nCurrent board:\n");
    for (int i = 0; i < n; i++)
    {
        printf("|");
        for (int j = 0; j < n; j++)
        {
            printf("%c|", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


//print a request for player with index "player_index" to move
//1 lines
void print_player_turn(int player_index)
{
    printf("\nPlayer ** %d **, enter next move:\n", player_index);
}


//print error message
//1 lines
void print_error()
{
    printf("Illegal move!!!, please try again:\n");
}


//print the winner
//1 lines
void print_winner(int player_index)
{
    printf("Player %d Wins! Hooray!\n", player_index);
}


//print message to announce there is a tie (no one wins)
//1 lines
void print_tie()
{
    printf("It's a tie!\n");
}


//converting step of game number to player index.
//1 lines
int step_to_player_index(int step_num)
{
    return step_num % 2 + 1;
}


//Does undo variable is correct.
//1 lines
bool right_undo(int undo, int step_num)
{
    return ((-undo % 2 == 1) && (-undo <= step_num))  ? true : false;
}


//returns the index of the other player
//1 lines
int partner_index(int player_idx)
{
    return (player_idx == 1) ? 2 : 1;
}
