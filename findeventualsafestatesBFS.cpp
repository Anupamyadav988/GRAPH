
// Solution:
// A terminal node is a node without any outgoing edges(i.e outdegree = 0). Now a node is considered to be a safe node if all possible paths starting from it lead to a terminal node. Here we need to find out all safe nodes and return them sorted in ascending order. If we closely observe, all possible paths starting from a node are going to end at some terminal node unless there exists a cycle and the paths return back to themselves. Let’s understand it considering the below graph:

// In the above graph, there exists a cycle i.e 0->1->3->0, and node 7 is connected to the cycle with an incoming edge towards the cycle.
// Some paths starting from these nodes are definitely going to end somewhere in the cycle and not at any terminal node. So, these nodes are not safe nodes.
// Though node 2 is connected to the cycle, the edge is directed outwards the cycle and all the paths starting from it lead to the terminal node 5. So, it is a safe node and the rest of the nodes (4, 5, 6) are safe nodes as well.
// So, the intuition is to figure out the nodes which are neither a part of a cycle nor connected to the cycle. We have previously solved this problem using the DFS traversal technique. Now, we are going to solve it using the BFS traversal technique especially using the topological sort algorithm. The topological sort algorithm will automatically exclude the nodes which are either forming a cycle or connected to a cycle. Note: Points to remember that any node which is a part of a cycle or leads to the cycle through an incoming edge towards the cycle, cannot be a safe node. Apart from these types of nodes, every node is a safe node.

// Approach:
// The node with outdegree 0 is considered to be a terminal node but the topological sort algorithm deals with the indegrees of the nodes. So, to use the topological sort algorithm, we will reverse every edge of the graph. Now, the nodes with indegree 0 become the terminal nodes. After this step, we will just follow the topological sort algorithm as it is.

// We will apply the BFS(Breadth First Search) traversal technique. Breadth First Search or BFS is a traversal technique where we visit the nodes level-wise, i.e., it visits the same level nodes simultaneously, and then moves to the next level.

// Initial Configuration:
// Indegree Array: Initially all elements are set to 0. Then, We will count the incoming edges for a node and store it in this array. For example, if indegree of node 3 is 2, indegree[3] = 2. If you don’t know how to find indegrees, you can refer to the step 2 in the algorithm.

// Queue: As we will use BFS, a queue is required. Initially, the node with indegree 0 will be pushed into the queue.

// safeNodes array: Initially empty and is used to store the safe nodes.

// The algorithm steps are as follows:

// First, we will reverse all the edges of the graph so that we can apply the topological sort algorithm afterward.
// Then, we will calculate the indegree of each node and store it in the indegree array. We can iterate through the given adj list, and simply for every node u->v, we can increase the indegree of v by 1 in the indegree array.
// Then, we will push the node(s) with indegree 0 into the queue.
// Then, we will pop a node from the queue including the node in our safeNodes array, and for all its adjacent nodes, we will decrease the indegree of that node by one. For example, if node u that has been popped out from the queue has an edge towards node v(u->v), we will decrease indegree[v] by 1.
// After that, if for any node the indegree becomes 0, we will push that node again into the queue.
// We will repeat steps 3 and 4 until the queue is completely empty. Finally, completing the BFS we will get the linear ordering of the nodes in the safeNodes array.
// Finally, the safeNodes array will only consist of the nodes that are neither a part of any cycle nor connected to any cycle. Then we will sort the final safeNodes array as the question requires the answer in sorted order.
// Note: If you wish to see the dry run of the above approach, you can watch the video attached to this article.

// Code:

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> eventualSafeNodes(int V, vector<int> adj[])
    {
        vector<int> adjRev[V];
        int indegree[V] = {0};
        for (int i = 0; i < V; i++)
        {
            // i -> it
            // it -> i
            for (auto it : adj[i])
            {
                adjRev[it].push_back(i);
                indegree[i]++;
            }
        }
        queue<int> q;
        vector<int> safeNodes;
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            safeNodes.push_back(node);
            for (auto it : adjRev[node])
            {
                indegree[it]--;
                if (indegree[it] == 0)
                    q.push(it);
            }
        }

        sort(safeNodes.begin(), safeNodes.end());
        return safeNodes;
    }
};

int main()
{

    vector<int> adj[12] = {{1}, {2}, {3, 4}, {4, 5}, {6}, {6}, {7}, {}, {1, 9}, {10}, {8}, {9}};
    int V = 12;
    Solution obj;
    vector<int> safeNodes = obj.eventualSafeNodes(V, adj);

    for (auto node : safeNodes)
    {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
// Output : 0 1 2 3 4 5 6 7

// Time Complexity: O(V+E)+O(N*logN), where V = no. of nodes and E = no. of edges. This is a simple BFS algorithm. Extra O(N*logN) for sorting the safeNodes array, where N is the number of safe nodes.

// Space Complexity: O(N) + O(N) + O(N) ~ O(3N), O(N) for the indegree array, O(N) for the queue data structure used in BFS(where N = no.of nodes), and extra O(N) for the adjacency list to store the graph in a reversed order.