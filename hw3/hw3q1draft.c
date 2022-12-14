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
char* setup_new_board(int n);
int doing_move_step(int player_index, char board[N][N], char new_step_board[][N], int n);
int verify_right_step(char board[N][N], int n, int i, int j);
bool check_winner(int player_index, char board[N][N], int n);
char player_sign(int player_index);
void copy_arr(char in_arr[][N], char out_arr[][N], int n);
int step_to_player_inx(int step_num);
bool right_undo(int undo);
/*-------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/

int main()
{
    int n = get_board_size();
    char* recorded_boards[N*N*N*N] = { 0 };
    recorded_boards[0] = setup_new_board(n);
    print_board(recorded_boards[0], n);
    int step_num = 0;
    while (step_num <= (n+1)*(n+1))
    {
        int player_index = step_to_player_inx(step_num);
        recorded_boards[step_num + 1] = setup_new_board(n);
        step_num += doing_move_step(player_index, recorded_boards[step_num], recorded_boards[step_num + 1], n);
        print_board(recorded_boards[step_num], n);
        if (check_winner(player_index, recorded_boards[step_num ], n)) {
            print_winner(player_index);
            break;
        }
    }
    if(check_winner(step_to_player_inx(step_num - 1), recorded_boards[step_num], n))
        print_winner(step_to_player_inx(step_num - 1));
    else
        print_tie();
}

//getting the size of the board game
// .. lines
int get_board_size()
{
    int n=0;
    print_welcome();
    print_enter_board_size();
    while (scanf("%d", &n) != 1)
        //exit_error();
        print_error();
    // assuming board size less or equal to N=11.
    return n;
}


/*void exit_error()
{
    printf("\n\n * ERROR! * \n");
    exit(1);
}*/

//establish new board.
// ... lines
char* setup_new_board(int game_board_size)
{
//Any place that used for the game, execute with '_'.
//All other 'free spaces' that left in the matrix set to zero.
    char new_board[N][N] = {{ 0 }};
    for (int i = 0; i < game_board_size; i++) {
        for (int j = 0; j < game_board_size; j++)
            new_board[i][j] = '_';
    }
    return new_board;
}

// returns: how many turns(steps) back should we go. Meaning, undo value.
// OR 0 - for success.
int doing_move_step(int player_index, char board[N][N], char new_step_board[N][N], int n)
{
    print_player_turn(player_index);     //recall that:  1 - 1st player, 2 - 2nd player.
    int row_or_undo = -1, col = -1;
    while (true)
    {
        while (scanf("%d", &row_or_undo) < 1)
            print_error();
        if (row_or_undo < 0) // col is unused, garbage
        {
            if (right_undo(row_or_undo))                       //TODO: right_undo(int undo) function.
                return row_or_undo;
            else
            {
                print_error();
                continue;
            }
        }
        while (scanf("%d", &col) < 1)
            print_error();
        if(verify_right_step(board, n, row_or_undo, col) != 0)
        {
            row_or_undo = col = -1;
            print_error();
        }
        else
            break;
    }
    copy_arr(board, new_step_board, n);
    new_step_board[row_or_undo - 1][col - 1] = player_sign(player_index);
    return 1;
}


char player_sign(int player_index){
    return (player_index == 1) ? 'X' : 'O';  // 0 - 1st player, 1 - 2nd player.
}


void copy_arr(char in_arr[][N], char out_arr[][N], int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            out_arr[i][j] = in_arr[i][j];
    }
}


bool check_winner(int player_index, char board[N][N], int n)
{
    char p_sign= player_sign(player_index);
    int full_line = n + 1, cnt_major_diagonal = 0, cnt_minor_diagonal = 0;
    for (int i = 0; i < n / 2; i++)
    {
        if(board[i][i] == player_sign)
            cnt_major_diagonal++;
        if(board[i][n-i] == player_sign)
            cnt_minor_diagonal++;
        int counter_for_row = 0, counter_for_col = 0;
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == player_sign)
                counter_for_row++;
            if (board[j][i] == player_sign)
                counter_for_col++;
        }
        if (counter_for_row == full_line || counter_for_col == full_line || cnt_minor_diagonal == full_line || cnt_major_diagonal == full_line)
            return true;
    }
    return false;
}

//error type dictionary: 1 - fatal overflow, 2 - game board overflow, 3 - no room for answer.
// 0 - correct input.
//
int verify_right_step(char board[N][N], int n, int i, int j)
{
    if (i < 0 || j < 0 || i > N || j > N)
        return 1;
    else if (i >= n || j >= n)
        return 2;
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


int step_to_player_inx(int step_num)
{
    return step_num % 2 + 1;
}

bool right_undo(int undo)
{
    return (-undo % 2 == 1)  ? true : false;
}