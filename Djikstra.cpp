#include <iostream>
#include <vector>
#include <queue>

#include "API.h"

using namespace std;

const int MAZE_WIDTH = 16;
const int MAZE_HEIGHT = 16;
const int GOAL_X = 7;
const int GOAL_Y = 7;

struct Node {
    int x, y;
    int distance;
    bool visited;
};

// possible movement directions
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

bool isValid(int x, int y) {
    return (x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT);
}

void moveMicromouse(int nextX, int nextY) {
    int currentX = API::mazeWidth();
    int currentY = API::mazeHeight();

    int dx = nextX - currentX;
    int dy = nextY - currentY;

    if (dx == 1) {
        API::turnRight();
        API::moveForward();
    } else if (dx == -1) {
        API::turnLeft();
        API::moveForward();
    } else if (dy == 1) {
        API::moveForward();
    }
}

void dijkstra(int startX, int startY) {
    vector<vector<Node>> graph(MAZE_WIDTH, vector<Node>(MAZE_HEIGHT));
    vector<vector<bool>> visited(MAZE_WIDTH, vector<bool>(MAZE_HEIGHT, false));

    for (int x = 0; x < MAZE_WIDTH; x++) {
        for (int y = 0; y < MAZE_HEIGHT; y++) {
            graph[x][y].x = x;
            graph[x][y].y = y;
            graph[x][y].distance = INT_MAX;
        }
    }

    graph[startX][startY].distance = 0;

    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push({0, {startX, startY}});

    while (!pq.empty()) {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        if (visited[x][y]) continue;

        visited[x][y] = true;

        for (int i = 0; i < 4; i++) {
            int nextX = x + dx[i];
            int nextY = y + dy[i];

            if (isValid(nextX, nextY) && !visited[nextX][nextY]) {
                int newDistance = graph[x][y].distance + 1; // Assuming uniform edge weights
                if (newDistance < graph[nextX][nextY].distance) {
                    graph[nextX][nextY].distance = newDistance;
                    pq.push({-newDistance, {nextX, nextY}});
                }
            }
        }
    }

    // Backtracking
    int currentX = GOAL_X;
    int currentY = GOAL_Y;
    while (currentX != startX || currentY != startY) {
        for (int i = 0; i < 4; i++) {
            int prevX = currentX - dx[i];
            int prevY = currentY - dy[i];
            if (isValid(prevX, prevY) && graph[prevX][prevY].distance + 1 == graph[currentX][currentY].distance) {
                moveMicromouse(prevX, prevY);
                currentX = prevX;
                currentY = prevY;
                break;
            }
        }
    }
}

int main() {
    // Initialize the graph, implement Dijkstra's algorithm, and move the micromouse
    // Continue until the destination is reached

    dijkstra(0, 0); // Start from the bottom-left corner

    // Implement path following and micromouse movement based on the Dijkstra's result
    // You will need to backtrack from the destination to find the path and use the moveMicromouse function to move the micromouse.

    return 0;
}
