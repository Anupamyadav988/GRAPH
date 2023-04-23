
// The algorithm is not much intuitive as the other ones’. It is more of a brute force, where all combinations of paths have been tried to get the shortest paths. Nothing to panic much with the intuition, it is a simple brute force approach on all paths. Focus on the three ‘for’ loops.

// Formula:

// matrix[i][j] =min(matrix[i][j], matrix[i ][k]+matrix[k][j]), where i = source node,
//                   j = destination node and k = the node via which we are reaching from i to j.

// The algorithm steps are as follows:

// Initial Configuration:

// Adjacency Matrix: The adjacency matrix should store the edge weights for the given edges and the rest of the cells must be initialized with infinity().

// After having set the adjacency matrix accordingly, we will run a loop from 0 to V-1(V = no. of vertices). In the kth iteration, this loop will help us to check the path via node k for every possible pair of nodes. Basically, this loop will change the value of k in the formula.
// Inside the loop, there will be two nested loops for generating every possible pair of nodes(Nothing but to visit each cell of a 2D matrix using the nested loop). Among these two loops, the first loop will change the value of i and the second one will change the value of j in the formula.
// Inside these nested loops, we will apply the above formula to calculate the shortest distance between the pair of nodes.
// Finally, the adjacency matrix will store all the shortest paths. For example, matrix[i][j] will store the shortest path from node i to node j.
// If we want to check for a negative cycle:
// After completing the steps(outside those three loops), we will run a loop and check if any cell having the row and column the same(i = j) contains a value less than 0.

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void shortest_distance(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][j] == -1)
                {
                    matrix[i][j] = 1e9;
                }
                if (i == j)
                    matrix[i][j] = 0;
            }
        }

        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    matrix[i][j] = min(matrix[i][j],
                                       matrix[i][k] + matrix[k][j]);
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][j] == 1e9)
                {
                    matrix[i][j] = -1;
                }
            }
        }
    }
};

int main()
{

    int V = 4;
    vector<vector<int>> matrix(V, vector<int>(V, -1));
    matrix[0][1] = 2;
    matrix[1][0] = 1;
    matrix[1][2] = 3;
    matrix[3][0] = 3;
    matrix[3][1] = 5;
    matrix[3][2] = 4;

    Solution obj;
    obj.shortest_distance(matrix);

    for (auto row : matrix)
    {
        for (auto cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }

    return 0;
}
// Output:

// 0 2 5 -1
// 1 0 3 -1
// -1 -1 0 -1
// 3 5 4 0

// Time Complexity: O(V3), as we have three nested loops each running for V times, where V = no. of vertices.

// Space Complexity: O(V2), where V = no. of vertices. This space complexity is due to storing the adjacency matrix of the given graph.