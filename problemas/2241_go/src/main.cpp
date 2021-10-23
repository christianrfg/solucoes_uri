/**
 * @file main.cpp
 * @author Christian Reis Fagundes Gomes (christianrfg@gmail.com)
 * @brief URI Online Judge - (2241) GO-- (https://www.urionlinejudge.com.br/judge/en/problems/view/2241)
 * @version 0.1
 * @date 2019-05-15
 * 
 * @copyright Copyright (c) 2019
 */
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Struct to store the types of each cell in the board 
 */
enum CellID
{
    EMPTY,
    BLACK,
    WHITE,
    CONF
};

/**
 * @brief Evaluate a 2 dimension rectangle
 *  We evaluate a 2 dimension rectangle to determine the feasible sub-areas. If the
 *  square has only black stones, then we return that square is BLACK. The same is
 *  done if the square has only white stones (WHITE). If the square has some black
 *  stone and some white stone, we determined that this square doesn't belong to
 *  any player (CONF).  Finally, if the square has no stones, we return that this
 *  square is a empty space (EMPTY).
 * 
 * @complexity
 *  T(n) = O((r_j - r_i) * (c_j - c_i))
 * 
 * @param board 
 *  Board of the game.
 * @param r_i 
 *  Initial row of the square.
 * @param r_j 
 *  Final row of the square.
 * @param c_i 
 *  Initial column of the square.
 * @param c_j 
 *  Final column of the square.
 * 
 * @return CellID 
 *  The type of the 2 dimension rectangle analysed.
 */
inline CellID eval_rect(vector<vector<int>> &board, int r_i, int r_j, int c_i, int c_j)
{
    int num_black = 0;
    int num_white = 0;

    for (int i = r_i; i <= r_j; ++i)
    {
        for (int j = c_i; j <= c_j; ++j)
        {
            if (board[i][j] == BLACK)
            {
                num_black += 1;
            }
            else if (board[i][j] == WHITE)
            {
                num_white += 1;
            }
            else if (board[i][j] == CONF) // When has black and white stones (conflict)
            {
                return CONF;
            }
        }
    }

    // Check the type of the square
    if ((num_black > 0) && (num_white == 0))
    {
        return BLACK;
    }
    else if ((num_white > 0) && (num_black == 0))
    {
        return WHITE;
    }
    else if ((num_black > 0) && (num_white > 0))
    {
        return CONF;
    }

    // Return empty if isn't the other types
    return EMPTY;
}

/**
 * @brief Solve the GO-- Problem
 *  The problem is solved iteratively by applying a series of squared reduction
 *  of dimension 2 to solve the squares of larger dimensions. In the end, we will
 *  have calculated how many possible sub-areas for each player.
 * 
 * @complexity:
 *  T(n) = O(N² * (log N) * (aval_result))
 * 
 * @param results 
 *  Store the total of sub-areas of each player.
 * @param board 
 *  The final board with the stones placed.
 * @param N 
 *  Size of the board.
 * @param P 
 *  Number of stones that each player places.
 */
inline void solution(map<CellID, int> &results, vector<vector<int>> &board, int N, int P)
{
    CellID aval_result;

    results[BLACK] = P;
    results[WHITE] = P;

    for (int dim = N; dim > 1; --dim)
    {
        for (int i = 0; i < dim - 1; ++i)
        {
            for (int j = 0; j < dim - 1; ++j)
            {
                aval_result = eval_rect(board, i, i + 1, j, j + 1);

                if (aval_result == BLACK || aval_result == WHITE)
                {
                    results[aval_result] += 1;
                }
                board[i][j] = aval_result;
            }
        }
    }
}

/**
 * @brief Main Program
 * Reads the problem input, solve the problem and prints the result.
 * 
 * @return int 
 * Indicate how the program exited (normal = 0 and abnormal = 1)
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char const *argv[])
{
    /**
     * @brief Configuration for fast I/O with cin/cout
     */

    ios_base::sync_with_stdio(false); // Toggle off synchronization of all the C++ standard streams
    cin.tie(NULL);                    // Disable the flushing of std::cout before std::cin accepts an input

    /**
     * @brief Variables 
     */

    // Variables for problem input
    int N;                     // Size of board
    int P;                     // Number of stones that each player places
    int L, C;                  // (row, column) of stones
    vector<vector<int>> board; // Matrix to store board

    // Variables for problem output
    map<CellID, int> results;

    /**
     * @brief Reading the input 
     */
    cin >> N >> P;

    // Init board with empty spaces (id = 0)
    board.resize(N, vector<int>(N, EMPTY));

    // Place black stones (id = BLACK)
    for (int i = 0; i < P; ++i)
    {
        cin >> L >> C;
        board[L - 1][C - 1] = BLACK;
    }

    // Place white stones (id = WHITE)
    for (int i = 0; i < P; ++i)
    {
        cin >> L >> C;
        board[L - 1][C - 1] = WHITE;
    }

    /**
     * @brief Problem Solution
     */
    solution(results, board, N, P);

    cout << results[BLACK] << " " << results[WHITE] << "\n";

    return 0;
}