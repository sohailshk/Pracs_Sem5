#include <iostream>
#include <vector>

using namespace std;

// Define constants for players
const char PLAYER_X = 'X'; // Maximizing player
const char PLAYER_O = 'O'; // Minimizing player
const char EMPTY = '_';    // Empty cell

// Function to print the Tic-Tac-Toe board
void printBoard(const vector<vector<char>> &board)
{
    for (const auto &row : board)
    {
        for (char cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Function to check if there are moves remaining on the board
bool movesLeft(const vector<vector<char>> &board)
{
    for (const auto &row : board)
    {
        for (char cell : row)
        {
            if (cell == EMPTY)
                return true;
        }
    }
    return false;
}

// Function to evaluate the board (return a score for terminal states)
int evaluate(const vector<vector<char>> &board)
{
    // Check rows for a win
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
        {
            if (board[row][0] == PLAYER_X)
                return +10;
            else if (board[row][0] == PLAYER_O)
                return -10;
        }
    }

    // Check columns for a win
    for (int col = 0; col < 3; col++)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
        {
            if (board[0][col] == PLAYER_X)
                return +10;
            else if (board[0][col] == PLAYER_O)
                return -10;
        }
    }

    // Check diagonals for a win
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == PLAYER_X)
            return +10;
        else if (board[0][0] == PLAYER_O)
            return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == PLAYER_X)
            return +10;
        else if (board[0][2] == PLAYER_O)
            return -10;
    }

    // No win
    return 0;
}

// Minimax function to find the best move
int minimax(vector<vector<char>> &board, int depth, bool isMax)
{
    int score = evaluate(board);

    // If the maximizer (PLAYER_X) has won
    if (score == 10)
        return score - depth;

    // If the minimizer (PLAYER_O) has won
    if (score == -10)
        return score + depth;

    // If no moves are left and no winner
    if (!movesLeft(board))
        return 0;

    // Maximizing player's move (PLAYER_X)
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (board[i][j] == EMPTY)
                {
                    // Make the move
                    board[i][j] = PLAYER_X;

                    // Call minimax recursively and choose the maximum value
                    best = max(best, minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
    // Minimizing player's move (PLAYER_O)
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Check if cell is empty
                if (board[i][j] == EMPTY)
                {
                    // Make the move
                    board[i][j] = PLAYER_O;

                    // Call minimax recursively and choose the minimum value
                    best = min(best, minimax(board, depth + 1, !isMax));

                    // Undo the move
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

// Find the best possible move for PLAYER_X (Maximizing player)
pair<int, int> findBestMove(vector<vector<char>> &board)
{
    int bestVal = -1000;
    pair<int, int> bestMove = {-1, -1};

    // Traverse all cells, evaluate minimax for each empty cell
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Check if cell is empty
            if (board[i][j] == EMPTY)
            {
                // Make the move
                board[i][j] = PLAYER_X;

                // Compute evaluation function for this move
                int moveVal = minimax(board, 0, false);

                // Undo the move
                board[i][j] = EMPTY;

                // If the value of the current move is better than the best value, update bestMove
                if (moveVal > bestVal)
                {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    cout << "The value of the best move is: " << bestVal << endl;
    return bestMove;
}

int main()
{
    vector<vector<char>> board = {
        {'X', 'O', 'X'},
        {'_', 'O', '_'},
        {'_', '_', '_'}};

    cout << "Current Board:" << endl;
    printBoard(board);

    pair<int, int> bestMove = findBestMove(board);

    cout << "The best move is row: " << bestMove.first << " and col: " << bestMove.second << endl;

    return 0;
}
