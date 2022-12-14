/*-------------------------------------------------------------------------
    Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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
//void exit_error();
void print_scan_failed();
void print_winner(int player_index);
void print_tie();
int get_board_size();
char* setup_new_board(int n);
int doing_move_step(int player_index, char board[N][N], int n);
int verify_right_step(char board[N][N], int n, int i, int j);
bool check_winner(int player_index, char board[N][N], int n);
char player_sign(int player_index);
void copy_arr(char in_arr[][N], char out_arr[][N], int n);
/*-------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/

int main()
{
    print_welcome();
    int n = get_board_size();
    char* recorded_boards[N*N] = { 0 };
    recorded_boards[0] = setup_new_board(n);
    while (1)
    {

        break;
    }
}

//getting the size of the board game
// .. lines
int get_board_size()
{
    int n=0;
    print_welcome();
    while (scanf("%d", &n) != 1)
        //exit_error();
        print_scan_failed();
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
    //char *new_board;
    //new_board = (char *) malloc(sizeof(char) * (N*N)); //TODO: variable with arr size.
// optional build every board in a used size. That better in concept of space keeping, but this would lift up the complexity of the code writing.
    //if (new_board == NULL) print_error();
    //for (char * p = new_board; p < sizeof(char) * (N*N); p++)
      //  (int) *p = 0
    for (int i = 0; i < game_board_size; i++)
        for (int j = 0; j < game_board_size; j++)
            new_board[i][j] = '_';
    return new_board;
}

// returns: how many turns(steps) back should we go. Meaning, undo value.
// OR 0 - for success.
char* doing_move_step(int player_index, char board[N][N], int n)
{
    print_player_turn(player_index);     //recall that:  0 - 1st player, 1 - 2nd player.
    int row_or_undo = -1, col = -1;
    bool keep_try = true;
    while (keep_try)
    {
        while (scanf("%d %d", &row_or_undo, &col) < 1)
            print_scan_failed();
        if (row_or_undo < 0) // col is unused, garbage
        {
            if (right_undo(row_or_undo))                       //TODO: right_undo(int row_or_undo) function.
                return row_or_undo;
            else
                keep_try = true;
        }
        else
        {
            keep_try = (bool) verify_right_step(board, n, row_or_undo, col);
        }
        if(keep_try)
        {
            row_or_undo = col = -1;
            print_error();
        }
    }
    char new_step_board[N][N] = { {0} };
    copy_arr(board, new_step_board, n);
    return copy_arr;
}


char player_sign(int player_index){
    return (player_index == 0) ? 'X' : 'O';  // 0 - 1st player, 1 - 2nd player.
}


void copy_arr(char in_arr[][N], char out_arr[][N], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            out_arr[i][j] = in_arr[i][j];
}


bool check_winner(int player_index, char board[N][N], int n)
{
    char player_sign = player_sign(player_index);
    int full_line = n + 1, counter_for_col;
    for (int i = 0; i <= n; i++)
    {
        int counter_for_row = 0;
        for (int j = 0; j <= n; j++)
        {
            if (board[i][j] == player_sign)
                counter_for_row++;
            if (board[j][i] == player_sign)
                counter_for_col++;
        }
        if (counter_for_row == full_line || counter_for_col == full_line)
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
    else if (i > n || j > n)
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


void print_scan_failed()
{
    printf("\n ERORR! \n please try again.\n");
}