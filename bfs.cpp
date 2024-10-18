#include <iostream>
#include<vector>
#include<queue>
using namespace std;

vector<int> codebfs(int startnode,vector<vector<int>> adj,int numnode){
    vector<int>ans;
    queue<int>q;
    int vis[numnode]={0};

    vis[startnode]=1;
    q.push(startnode);

    while(!q.empty()){
        int top=q.front();
        q.pop();
        ans.push_back(top);
        for(int neighbour:adj[top]){
            if(!vis[neighbour]){
                q.push(neighbour);
                vis[neighbour]=1;
            }

        }
    }
    return ans;
}
int main(){
    int numnode=6;
    
    vector<vector<int>> adj(numnode);
    adj[0]={1,2};
    adj[1]={0,3,4};
    adj[2]={0,5};
    adj[3]={1};
    adj[4]={1};
    adj[5]={2};
    vector<int>finalans=codebfs(0,adj,numnode);
    cout << "BFS Traversal starting from node 0: ";
    for (int node : finalans)
    {
        cout << node << " ";
    }
    cout << endl;
    return 0;

}

