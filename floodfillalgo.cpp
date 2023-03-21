// Approach:
// To perform a “flood fill”, consider the starting pixel, plus any pixels connected 4-directionally to the starting pixel of the same colour as the starting pixel, 
// plus any pixels connected 4-directionally to those pixels (also with the same colour as the starting pixel), and so on.


// We know about both the traversals, Breadth First Search (BFS) and Depth First Search (DFS). We can follow BFS also, where we start at a given point and colour level wise, i.e., we go simultaneously to all its neighbours. We can use any of the traversals to solve this problem, in our case we will be using DFS just to explore multiple approaches. 

// The algorithm steps are as follows:

// Initial DFS call will start with the starting pixel (sr, sc) and make sure to store the initial colour. 
// Now, either we can use the same matrix to replace the colour of all of the aforementioned pixels with the newColor or create a replica of the given matrix.
//  It is advised to use another matrix because we work on the data and not tamper with it.
//  So we will create a copy of the input matrix. 
// Check for the neighbours of the respective pixel that has the same initial colour and has not been visited or coloured. DFS call goes first in the depth on either of the neighbours.
// We go to all 4 directions and check for unvisited neighbours with the same initial colour.
//  To travel 4 directions we will use nested loops, you can find the implementation details in the code. 
// DFS function call will make sure that it starts the DFS call from that unvisited neighbour, and colours all the pixels that have the same initial colour, and at the same time it will also mark them as visited. 

#include<bits/stdc++.h>
using namespace std;

class Solution {
private:
    void dfs(int row, int col, vector<vector<int>>&ans,
     vector<vector<int>>& image, int newColor, int delRow[], int delCol[],
     int iniColor) {
        // color with new color
        ans[row][col] = newColor; 
        int n = image.size();
        int m = image[0].size(); 
        // there are exactly 4 neighbours
        for(int i = 0;i<4;i++) {
            int nrow = row + delRow[i]; 
            int ncol = col + delCol[i]; 
            // check for valid coordinate 
            // then check for same initial color and unvisited pixel
            if(nrow>=0 && nrow<n && ncol>=0 && ncol < m && 
            image[nrow][ncol] == iniColor && ans[nrow][ncol] != newColor) {
                dfs(nrow, ncol, ans, image, newColor, delRow, delCol, iniColor); 
            }
        }
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, 
    int sr, int sc, int newColor) {
        // get initial color
        int iniColor = image[sr][sc]; 
        vector<vector<int>> ans = image; 
        // delta row and delta column for neighbours
        int delRow[] = {-1, 0, +1, 0};
        int delCol[] = {0, +1, 0, -1}; 
        dfs(sr, sc, ans, image, newColor, delRow, delCol, iniColor); 
        return ans; 
    }
};

int main(){
		
	vector<vector<int>>image{
	    {1,1,1},
	    {1,1,0},
	    {1,0,1}
	};
	
// sr = 1, sc = 1, newColor = 2  	
	Solution obj;
	vector<vector<int>> ans = obj.floodFill(image, 1, 1, 2);
	for(auto i: ans){
		for(auto j: i)
			cout << j << " ";
		cout << "\n";
	}
	
	return 0;
}

// Time Complexity: O(NxM + NxMx4) ~ O(N x M)

// For the worst case, all of the pixels will have the same colour, so DFS function will be called for (N x M) nodes and for every node we are traversing for 4 neighbours, so it will take O(N x M x 4) time.

// Space Complexity: O(N x M) + O(N x M)

// O(N x M) for copied input array and recursive stack space takes up N x M locations at max. 