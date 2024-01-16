#include <stdio.h>
#include <stdlib.h>
#include "tictactoe.h"
// #define T_SIZE 3
// #define T_MAX 1000
// #define T_MIN -1000

// char T_board[T_SIZE][T_SIZE];
// char T_humanPlayer = 'X';
// char T_computerPlayer = 'O';

// Function to check if the move is valid
int T_isValidMove(int row, int col)
{
    return (row >= 0 && row < T_SIZE && col >= 0 && col < T_SIZE && T_board[row][col] == ' ');
}

// Function to check if the game is over or not
int T_isGameOver()
{
    for (int i = 0; i < T_SIZE; i++)
    {
        if (T_board[i][0] == T_board[i][1] && T_board[i][1] == T_board[i][2] && T_board[i][0] != ' ')
            return 1; // Row-wise check
        if (T_board[0][i] == T_board[1][i] && T_board[1][i] == T_board[2][i] && T_board[0][i] != ' ')
            return 1; // Column-wise check
    }
    if (T_board[0][0] == T_board[1][1] && T_board[1][1] == T_board[2][2] && T_board[0][0] != ' ')
        return 1; // Diagonal 1 check
    if (T_board[0][2] == T_board[1][1] && T_board[1][1] == T_board[2][0] && T_board[0][2] != ' ')
        return 1; // Diagonal 2 check

    for (int i = 0; i < T_SIZE; i++)
    {
        for (int j = 0; j < T_SIZE; j++)
        {
            if (T_board[i][j] == ' ')
                return 0; // Game is still in progress
        }
    }
    return -1; // Game is a draw
}

// Function to T_evaluate the current game state
int T_evaluate()
{
    for (int row = 0; row < T_SIZE; row++)
    {
        if (T_board[row][0] == T_board[row][1] && T_board[row][1] == T_board[row][2])
        {
            if (T_board[row][0] == T_computerPlayer)
                return +10;
            else if (T_board[row][0] == T_humanPlayer)
                return -10;
        }
    }
    for (int col = 0; col < T_SIZE; col++)
    {
        if (T_board[0][col] == T_board[1][col] && T_board[1][col] == T_board[2][col])
        {
            if (T_board[0][col] == T_computerPlayer)
                return +10;
            else if (T_board[0][col] == T_humanPlayer)
                return -10;
        }
    }
    if (T_board[0][0] == T_board[1][1] && T_board[1][1] == T_board[2][2])
    {
        if (T_board[0][0] == T_computerPlayer)
            return +10;
        else if (T_board[0][0] == T_humanPlayer)
            return -10;
    }
    if (T_board[0][2] == T_board[1][1] && T_board[1][1] == T_board[2][0])
    {
        if (T_board[0][2] == T_computerPlayer)
            return +10;
        else if (T_board[0][2] == T_humanPlayer)
            return -10;
    }
    return 0;
}

// Function for the T_miniT_max algorithm
int T_miniT_max(int depth, int isT_Max)
{
    int score = T_evaluate();
    if (score == 10)
        return score - depth; // Computer wins
    if (score == -10)
        return score + depth; // Human wins
    if (T_isGameOver())
        return 0; // Game is a draw

    if (isT_Max)
    {
        int best = T_MIN;
        for (int i = 0; i < T_SIZE; i++)
        {
            for (int j = 0; j < T_SIZE; j++)
            {
                if (T_board[i][j] == ' ')
                {
                    T_board[i][j] = T_computerPlayer;
                    best = (best > T_miniT_max(depth + 1, !isT_Max)) ? best : T_miniT_max(depth + 1, !isT_Max);
                    T_board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else
    {
        int best = T_MAX;
        for (int i = 0; i < T_SIZE; i++)
        {
            for (int j = 0; j < T_SIZE; j++)
            {
                if (T_board[i][j] == ' ')
                {
                    T_board[i][j] = T_humanPlayer;
                    best = (best < T_miniT_max(depth + 1, !isT_Max)) ? best : T_miniT_max(depth + 1, !isT_Max);
                    T_board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

// Function to make the computer move
void T_computerMove()
{
    int bestVal = T_MIN;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < T_SIZE; i++)
    {
        for (int j = 0; j < T_SIZE; j++)
        {
            if (T_board[i][j] == ' ')
            {
                T_board[i][j] = T_computerPlayer;
                int moveVal = T_miniT_max(0, 0);
                T_board[i][j] = ' ';
                if (moveVal > bestVal)
                {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    T_board[bestRow][bestCol] = T_computerPlayer;
}

// Function to display the T_board
void printT_Board()
{
    printf("\n");
    for (int i = 0; i < T_SIZE; i++)
    {
        for (int j = 0; j < T_SIZE; j++)
        {
            if (T_board[i][j] == 'X')
            {
                printf("\033[1;31m X \033[0m"); // Red color for X
            }
            else if (T_board[i][j] == 'O')
            {
                printf("\033[1;33m O \033[0m"); // Yellow color for O
            }
            else
            {
                printf("   ");
            }
            if (j < T_SIZE - 1)
                printf("|");
        }
        printf("\n");
        if (i < T_SIZE - 1)
        {
            printf("---|---|---\n");
        }
    }
}

/*
int main()
{
    for (int i = 0; i < T_SIZE; i++)
    {
        for (int j = 0; j < T_SIZE; j++)
        {
            T_board[i][j] = ' ';
        }
    }
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("You are playing as 'X'.\n");
    printf("Enter the row and column (1-3) to make your move.\n");

    while (!T_isGameOver())
    {
        printT_Board();
        int row, col;
        printf("Enter your move (row column): ");
        scanf("%d %d", &row, &col);
        row--;
        col--;

        while (!T_isValidMove(row, col))
        {
            printf("Invalid move. Try again: ");
            scanf("%d %d", &row, &col);
            row--;
            col--;
        }

        T_board[row][col] = T_humanPlayer;

        if (T_isGameOver())
            break;

        T_computerMove();
    }

    printT_Board();
    int result = T_evaluate();
    if (result > 0)
    {
        printf("Computer ('O') wins!\n");
    }
    else if (result < 0)
    {
        printf("Player ('X') wins!\n");
    }
    else
    {
        printf("It's a draw!\n");
    }
    return 0;
}



The Minimax algorithm is a decision-making algorithm used in two-player games with perfect information, like Tic-Tac-Toe or Chess. Its goal is to choose the optimal move for a player, assuming that the opponent also plays optimally.

Key Concepts:
Search Tree: Minimax operates on a game tree, where nodes represent game states, and edges denote possible moves.

Maximizing and Minimizing Players: In a turn-based game, one player aims to maximize their score (Maximizer), while the opponent tries to minimize it (Minimizer).

Algorithm Workflow:
Recursive Tree Traversal:

Starting from the current game state, the algorithm explores the entire game tree by recursively examining all possible moves.
The tree depth usually represents the number of moves ahead to consider.
Assigning Scores:

At terminal states (win, lose, or draw), scores are assigned:
If the Maximizer wins, assign a positive score.
If the Minimizer wins, assign a negative score.
For a draw, assign a neutral score (usually 0).
Backtracking:

Scores are propagated back up the tree:
Maximizer nodes choose the maximum score from their children.
Minimizer nodes choose the minimum score from their children.
Best Move Selection:

At the root node (starting state), the algorithm chooses the move that leads to the highest score for the Maximizer.
This move represents the optimal strategy under the assumption of optimal play by both players.
In Tic-Tac-Toe:
Depth of the Search Tree: For Tic-Tac-Toe, where the board is small, the algorithm can typically explore the entire game tree.

For Tic-Tac-Toe:

Branching Factor: At each turn, there are typically 9 possible moves initially, reducing by one with each subsequent move.
Depth of the Tree: The depth of the game tree is at most 9 moves (assuming no game-ending conditions occur earlier).
Completeness of Search: With modern computing power, it's possible to traverse the entire game tree, allowing the algorithm to analyze all possible moves to determine the optimal strategy.
For this reason, the entire game tree for Tic-Tac-Toe can be exhaustively explored and stored in memory, allowing for:

Perfect Play: Given enough computational resources, the Minimax algorithm can find the optimal move in any situation.
Game Analysis: It allows for analysis of different strategies, patterns, and outcomes to determine the best moves under any circumstance.

The code provided for a Tic-Tac-Toe game uses the Minimax algorithm but does not explicitly create a tree data structure. Instead, the game states are explored and evaluated through recursive function calls, representing the game tree implicitly.

The T_miniT_max function recursively explores possible moves by simulating both the computer and human player's turns. It evaluates each move's score based on the current state of the board and chooses the best move for the computer player.

The functions T_isGameOver and T_evaluate determine if the game is over and evaluate the current board state, assigning scores based on the outcome for the computer player.

The T_computerMove function calculates the best move for the computer using the Minimax algorithm and places the computer's symbol ('O') on the board.

The printT_Board function is responsible for displaying the Tic-Tac-Toe board.

While the code implements the logic of the Minimax algorithm for a Tic-Tac-Toe game, it does not explicitly create or manipulate a tree data structure. Instead, the game tree's nodes and branches are traversed implicitly through the recursive nature of the algorithm.
*/