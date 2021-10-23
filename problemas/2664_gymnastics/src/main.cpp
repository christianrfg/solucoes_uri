/**
 * @file main.cpp
 * @author Christian Reis Fagundes Gomes (christianrfg@gmail.com)
 * @brief URI Online Judge - (2241) Gymnastics (https://www.urionlinejudge.com.br/judge/en/problems/view/2664)
 * @version 0.1
 * @date 2019-05-15
 * 
 * @copyright Copyright (c) 2019
 */

/**
 * @solution
 *  For solving this problem, we use the Dynamic Programming Paradigm [1]. We 
 *  need to calculate the amount of programs we can build for a exercise given
 *  the time T and the min-max difficulty levels M-N. One program is a sequency 
 *  of difficulties levels of a exercise, being that difficulty levels should 
 *  change every minute to a level immediately above or a level immediately below.
 *  
 *  Thus, we use Dynamic Programming to help us solve this problem. We use smaller
 *  time solutions to find larger times solutions. Since we only need the total 
 *  number of programs, we have been able to solve this problem with two vectors. 
 *  We use a vector A and B, where these store the number of programs with each 
 *  level of difficulty level at time i and i + 1, respectively. At each time i,
 *  we update the B vector as follows:
 *  
 *   B[j] = (A[j - 1] + A[j + 1]), for each j = 1, .., M-N+1
 *  
 *  That is, for each difficulty level, we update the amount of programs based
 *  on the amount of programs of the after time. We make the assign A = B and
 *  repeat the processuntil it reaches the time we want (provided by the problem
 *  input). Finally, we add the value of the number of programs in the last time
 *  to obtain the solution of the problem.
 * 
 * @references
 *  [1] Cormen, Thomas H., et al. Introduction to algorithms. MIT press, 2009.
 */
#include <bits/stdc++.h>

using namespace std;

#define RES_MOD (1000000000LL + 7) // Number for module operation
#define ll long long               // Abbreviation for long long

/**
 * @brief Dynamic Programming solution of the Gymnastics URI Problem.
 *  For solving this problem, we use the Dynamic Programming Paradigm. We
 *  start from the calculations of smaller times to solve the grater times.
 *  Thus, in the i-th time, we calculate the number of programs according
 *  to the (i-th - 1) time. In the end, we'll have the total of programs we can
 *  do from each difficulty. Thus, we just need to add the amount of programs
 *  with each difficulty to get the total amount of programs (i.e., solution of
 *  the problem).
 * 
 * @complexity
 *  rows - T (input time)
 *  cols - N - M + 1 (amount of difficulty levels)
 *  T(n) = O(rows * cols)
 * 
 * @param T 
 *  Minutes of the exercise.
 * @param M 
 *  Minimum difficult value.
 * @param N 
 *  Maximum difficult value.
 * 
 * @return int 
 *  Number of different programs module by RES_MOD.
 */
inline int solve_problem(int T, int M, int N)
{
    // Define vector dimensions
    int rows = T;
    int cols = N - M + 1;

    // Set and initialize the vectors that will store the maximum amount of
    // programs in the (i-th - 1) time (oldLine) and in the i-th time (newLine). We
    // add two new columns to handle the minimum and maximum values that will not
    // have a minor difficult and a major difficult, respectively. We instantiate
    // time 1 (i.e., base-case) with all values 1, since with time 1 each gymnastic
    // program will be an individual difficulty.
    vector<ll int> oldLine(cols + 2, 1);
    vector<ll int> newLine(cols + 2, 0);
    oldLine[0] = 0;
    oldLine[cols + 1] = 0;

    ll int solution;
    solution = 0;

    // For each i-th time, compute the number of possible probrams using each
    // difficult. The variable oldLine will store the maximum amount of programs,
    // for each difficult, in the i-th time.
    for (int i = 1; i < rows; ++i)
    {
        // Updates the i-th time with values from the (i-th - 1) time.
        for (int j = 1; j <= cols; ++j)
            newLine[j] = (oldLine[j - 1] + oldLine[j + 1]);

        oldLine = newLine;
    }

    // Get the total of programs module (10⁹ + 7)
    for (int j = 1; j <= cols; ++j)
        solution = (solution + oldLine[j]) % RES_MOD;

    return solution;
}

/**
 * @brief Main Program
 *  Reads the problem input, solve the problem and prints the result.
 * 
 * @return int 
 *  Indicate how the program exited (normal = 0 and abnormal = 1)
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
    int T, M, N;

    // Variables for problem results
    int solution;

    /**
     * @brief Reading the input and solving the problem.
     */
    cin >> T >> M >> N;

    /**
     * @brief Solving the Problem with Dynamic Programming.
     */
    solution = solve_problem(T, M, N);

    // Print the result
    cout << solution << "\n";

    return 0;
}