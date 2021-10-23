/**
 * @file main.cpp
 * @author Christian Reis Fagundes Gomes (christianrfg@gmail.com)
 * @brief URI Online Judge - (1487) Six Flags (https://www.urionlinejudge.com.br/judge/en/problems/view/1487)
 * @version 0.1
 * @date 2019-05-15
 * 
 * @copyright Copyright (c) 2019
 */

/**
 * @solution
 * 
 * We can see by the problem description (provided in the problem website) that
 * this is a variation of the classifical Knapsack Problem. In this problem, we
 * can have unlimited number of instances of an ride (i.e., items). That type of
 * Knapsack variation is known as Unbounded Knapsack [1].
 * 
 * The Unbounded Knapsack Problem, as well as the classical Knapsack Problem, 
 * can be solved using the Dynamic Programming paradigm. Given a set of 'n' items
 * having weights {W1, .., Wn} e scores {V1, .., Vn} and a Knapsack of weight W,
 * we want to find the maximum value that can be accommodated using 1 or more 
 * instances of given weights [2]. 
 * 
 * For solving this specific problem, we maintain an array V[W + 1] where 'j' 
 * index stores the maximum value that can be fitted in a knapsack of capacity 
 * 'j'. While computing V[j], we need to decide whether to select or reject an 
 * instance of a weight 'i'. Thus, the structure of the optimal solution is 
 * defined recursively as: V[j] = max(V[j - 1], V[j - weights[i]] + scores[i]) for i = 0 .. n - 1.
 * Finally, V[W] gives the required solution [2].
 * 
 * Thus, for solving the Six Flags problem, we use the Unbounded Knapsack Algorithm
 * to find the total score of the collection of rides [2]. 
 * 
 * @references
 * [1] Unbounded Knapsack (Repetition of items allowed). (2018, September 28). 
 * Retrieved May 22, 2019, from https://www.geeksforgeeks.org/unbounded-knapsack-repetition-items-allowed/.
 * [2] Algorithm unbounded knapsack problem. (n.d.). Retrieved May 22, 2019, 
 * from https://csegeek.com/csegeek/view/tutorials/algorithms/dynamic_prog/dp_part7.php.
 */
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Implementation of Unbounded Knapsack solution using the Dynamic Programming
 * approach.
 * 
 * @complexity
 *  capacity - time available for rides.
 *  n_items - number of rides.
 *  T(n) = O(capacity * n_items)
 * 
 * @param n_items 
 *  Number of items in the knapsack.
 * @param capacity 
 *  Capacity of the knapsack.
 * @param scores 
 *  Scores of each item.
 * @param weights 
 *  Weights of each item.
 * 
 * @return int 
 *  Maximum possible score.
 */
inline int unboundedKnapsack(int n_items, int capacity, vector<int> scores, vector<int> weights)
{
    // Array to store the maximum value using all items and i-th capacity of knapsack
    vector<int> V(capacity + 1, 0);
    // Capacity idx
    int i_capacity = 0;

    for (auto &capacity : V) // For each capacity (i.e., i-th capacity) in V
    {
        for (int j = 0; j < n_items; ++j)                                         // For each item in the bag
            if (weights[j] <= i_capacity)                                         // If the j-th weight is less-equal i-th capacity index
                capacity = max(capacity, V[i_capacity - weights[j]] + scores[j]); // Update the i-th capacity

        i_capacity++;
    }

    return V[capacity];
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

    // Variables for problem results
    int H = 1;
    int x;

    // Variables for problem input
    int N, T, D, P;
    vector<int> rideDurations;
    vector<int> scores;

    /**
     * @brief Reading the input and solving the problem of each test case.
     */

    // Reads the N, T, rideDurations and scores from the input
    // for each test case. If N == 0, we reach the end of the input.
    while ((cin >> N >> T) and (N != 0))
    {
        for (int i = 0; i < N; ++i)
        {
            cin >> D >> P;
            rideDurations.push_back(D);
            scores.push_back(P);
        }

        /**
         * @brief Solving one test case. 
         * For solving this problem, we use the implementation of the Dynamic
         * Programming solution of the Unbounded Knapsack Problem [1,2]. In the
         * end of the algorithm execution, we have the total score possible using
         * the problem input.
         */

        x = unboundedKnapsack(N, T, scores, rideDurations);

        // Print the result
        cout << "Instancia " << H << "\n";
        cout << x << "\n\n";

        // Clear vectors for next test cases
        rideDurations.clear();
        scores.clear();

        // Increment H for next test case
        H += 1;
    }

    return 0;
}