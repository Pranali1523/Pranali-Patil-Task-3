#include<bits/stdc++.h>
#include <algorithm>
using namespace std;
bool sortcol(const vector<int>& v1, const vector<int>& v2){
    return v1[4] < v2[4];
}
class Solution{
    public:
    vector<vector<int>> dist; 
    
    vector<pair<int,int>> MinimumCostPath(vector<int>& grid,int n,int m){
        int x1=grid[0],y1=grid[1],x2 = grid[2],y2 = grid[3],t = grid[4];
        vector<vector<int>> vist(n,vector<int>(m,0));
        queue<pair<pair<int,int>,int>> q;    /* we store x and y co-ordinate with time*/
        q.push({{x1,y1},t});
        
        vector<pair<int,int>> ans;        /* ans is used to store the shortest path from sorce to destination */
        ans.push_back({x1,y1});
        
        vector<vector<int>> directions = {{0,1},{0,-1},{1,0},{-1,0}};
        while(!q.empty()){
            int x = q.front().first.first,y = q.front().first.second;
            int t = q.front().second;
            q.pop();
            vist[x][y] = 1;
            int cod1=0,cod2=0;
            long long euclidDist=0,curmin=INT_MAX;
            for(int i=0 ;i<4 ;i++){
                int nx = x+directions[i][0],ny = y+directions[i][1];
                if(nx<0 || ny<0 ||ny>=m || nx>=n || vist[nx][ny]) continue;
                if(dist[nx][ny]==t+1) continue;
                int ptx = x2-nx,pty = y2-ny;
                euclidDist = ptx*ptx+pty*pty;
                
                if(curmin>=euclidDist){
                    cod1 = nx,cod2 = ny;
                    curmin = euclidDist;
                }
            }
            if(curmin!=INT_MAX){ 
                dist[cod1][cod2] = max(dist[cod1][cod2],t+1);
                q.push({{cod1,cod2},t+1});
                ans.push_back({cod1,cod2});
                if(cod1==x2 && cod2==y2) break;
            }
        }
        return ans;
    }
    void PrintSortestPath(vector<pair<int,int>>&SortestPath){
        for(auto it:SortestPath){
            cout<<"("<<it.first<<","<<it.second<<")"<<" ";
        }
        cout<<endl;
        return ;
    }

    void PathCalculate(vector<vector<int>> &grid,int n,int m){

        /* we use dist vector to check whether two nodes reach at same co-ordinate simultaniously or at 
        same time */

        dist = vector<vector<int>>(n,vector<int>(m,0));

        /* we sort the given grid on the bases of the time of arrival of drone (when it came) */
        sort(grid.begin(),grid.end(),sortcol);

        int size = grid.size();

        cout<<"<-----------------------Calculate all Sortest Path-------------------------->"<<endl;
        for(int i=0 ;i<size ;i++){
            cout<<"Sortest Path from "<<"("<<grid[i][0]<<","<<grid[i][1]<<") to ("<<grid[i][2]<<","<<grid[i][3]<<") with time at "<<grid[i][4]<<endl;
            vector<pair<int,int>> SortestPath = MinimumCostPath(grid[i],n,m);
            PrintSortestPath(SortestPath);
            cout<<endl;
        }
        return ;
    }
    
};


int main(){
    Solution obj;
    vector<vector<int>> grid={  {0,1,2,4,1},  
                                {0,3,3,0,2},
                                {0,0,2,3,1},
                                {2,1,2,4,1} }; 
    /* here i have n*m 2-D plane grid of let say n= 5 and m=5*/
    obj.PathCalculate(grid,5,5);
}
