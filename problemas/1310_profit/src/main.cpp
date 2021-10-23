/**
 * @file main.cpp
 * @author Christian Reis Fagundes Gomes (christianrfg@gmail.com)
 * @brief URI Problem - (1310) Profit (https://www.urionlinejudge.com.br/judge/en/problems/view/1310)
 * @version 0.1
 * @date 2019-05-15
 * 
 * @copyright Copyright (c) 2019
 */

/**
 * @solution
 *  For solving this problem, first we transform the original problem into
 *  the Maximum Contiguous Subsequence Sum (MCSS) problem. We can do this by
 *  subtracting the perDayCost of each revenue of the circus. 
 *  
 *  With this the resultant vector from the subtraction, we can see that now our 
 *  problem has been transformed in the MCSS problem. To solve the MCSS problem 
 *  and, consequently, solve the original problem, we use the Kadane's Algorithm [1,2]. 
 *  The Kadane's algorithm is based on the dynamic programming paradigm, which 
 *  solves the problem splitting up the set of possible solutions into mutually 
 *  exclusive (disjoint) sets [2].
 *  
 *  After apply the Kadane's Algorithm, we can obtain the MCSS of one array. Thus,
 *  we have the result of the original problem.
 * 
 * @references
 *  [1] Maximum subarray sum in O(n) using prefix sum. (2018, July 03). 
 *  Retrieved May 22, 2019, from https://www.geeksforgeeks.org/maximum-subarray-sum-using-prefix-sum/.
 *  [2] Maximum subarray problem. (2019, May 14). Retrieved May 22, 2019, 
 *  from https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm.
 */
#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Implementation of Kadane's Algorithm for solving the MCSS problem. 
 *  Solve the MCSS problem and return the MCSS value of the input array.
 * 
 * @complexity 
 *  n - number of elements in the array
 *  T(n) = O(n)
 * 
 * @param array
 * Array represent with the std::vector type.
 * 
 * @return int 
 * Maximum Contiguous Subsequence Sum find in the input array.
 */
inline int kadaneAlgorithm(vector<int> array)
{
    /**
     * max_ending_here - Use to look for all positive contiguous segments in the array.
     * max_so_far - Maximum sum contiguous segmentamong all positive segments.
     */
    int max_so_far, max_ending_here;

    max_so_far = 0;
    max_ending_here = 0;

    for (auto &element : array)
    {
        max_ending_here += element;

        if (max_ending_here < 0) // Initialize a new segment
            max_ending_here = 0;
        else if (max_so_far < max_ending_here) // Update max_so_far if a segment if greater than max_so_far
            max_so_far = max_ending_here;
    }

    return max_so_far;
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

    // Variables for problem results
    int testCaseResult;

    // Variables for problem input
    int numberDays, perDayCost, tmp_revenue;
    vector<int> revenues;

    /**
     * @brief Reading the input and solving the problem of each test case.
     */

    // Reads the numberDays, perDayCost and revenues from the input
    // for each test case
    while (cin >> numberDays)
    {
        cin >> perDayCost;
        for (int i = 0; i < numberDays; i++)
        {
            cin >> tmp_revenue;
            revenues.push_back(tmp_revenue);
        }

        /**
         * @brief Solving one test case. 
         *  For solving this problem, we transform the original problem in the 
         *  Maximum Contiguous Subsequence Sum problem. The transformation of the 
         *  original problem into a MCSS problem is done by subtracting the 
         *  perDayCost of each revenue. With the problem transformed we can apply 
         *  the Kadane's Algoritm for solve the MCSS problem and, consequently,
         *  solve the original problem.
         */

        // Transforming the original problem in MCSS problem
        for (auto &rev : revenues)
            rev -= perDayCost;

        // Solving the MCSS problem with Kodane Algorithm
        testCaseResult = kadaneAlgorithm(revenues);

        // Print the result
        cout << testCaseResult << "\n";

        // Clear revenues vector for next test cases
        revenues.clear();
    }

    return 0;
}
