#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Define a node structure to represent the state
struct Node {
    int x, y; // Coordinates
    int h;    // Heuristic (distance to goal)
    
    // Comparison operator for priority queue (min-heap based on h)
    bool operator>(const Node& other) const {
        return h > other.h;
    }
};

// Heuristic function: Manhattan distance to goal
int heuristic(int x, int y, int goalX, int goalY) {
    return abs(x - goalX) + abs(y - goalY);
}

// Greedy Best-First Search function
bool greedyBestFirstSearch(int startX, int startY, int goalX, int goalY) {
    // Priority queue to store nodes based on their heuristic value
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
    // Start with the initial node
    pq.push({startX, startY, heuristic(startX, startY, goalX, goalY)});
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        
        // Check if the goal is reached
        if (current.x == goalX && current.y == goalY) {
            cout << "Goal reached!" << endl;
            return true;
        }
        
        // Explore neighboring nodes (up, down, left, right)
        vector<pair<int, int>> neighbors = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto [dx, dy] : neighbors) {
            int newX = current.x + dx;
            int newY = current.y + dy;
            
            // For simplicity, we assume grid boundaries are [0, 9] for both x and y
            if (newX >= 0 && newX <= 9 && newY >= 0 && newY <= 9) {
                pq.push({newX, newY, heuristic(newX, newY, goalX, goalY)});
            }
        }
    }
    
    cout << "Goal not reachable." << endl;
    return false;
}

int main() {
    int startX = 0, startY = 0;
    int goalX = 9, goalY = 9;

    // Run Greedy Best-First Search
    greedyBestFirstSearch(startX, startY, goalX, goalY);

    return 0;
}
