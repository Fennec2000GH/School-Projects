#include <cmath>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

vector<vector<int>> getInput() {
    string line;
    getline(cin, line);

    string token;

    int rowNum=0;
    int colNum=0;
    int size=0;
    int currSize = 0;

    int test;


    //get size
    stringstream lineStream(line);
    while(lineStream >> token)
    {
        size++;
    }

    //initialize 2D vector
    vector<vector<int>> numbers(size, vector<int>(size, 0));

    //read lines

    for (int k = 0; k<size-1; k++)
    {

        stringstream lineStream2(line);
        currSize = 0;
        while(lineStream2 >> token)
        {

            test = stoi(token);
            numbers[rowNum][currSize] = test;
            currSize++;
        }
        rowNum++;
        getline(cin, line);

    }
    //do the last line
    stringstream lineStream2(line);
    currSize = 0;
    while(lineStream2 >> token)
    {

        test = stoi(token);
        numbers[rowNum][currSize] = test;
        currSize++;
    }

    return numbers;
}

void solveMaze(vector<vector<int>> maze, int x, int y) {
    stack <pair<int, int>> coordStack;
    coordStack.push(pair<int, int>(0, 0));
    //current top coordinate, most recent coordinate before top, and potential future coordinate to be pushed to stack
    pair<int, int> nowTop  = coordStack.top(), prevTop, nextTop;

    while (nowTop.first != x || nowTop.second != y) {
        nowTop = coordStack.top();

        //allowed to move RIGHT
        if (nowTop.second <= maze.at(0).size() - 2 && nowTop.second + 1 != prevTop.second) {
            nextTop = pair<int, int>(nowTop.first, nowTop.second + 1);
            if (maze.at(nextTop.first).at(nextTop.second) == 1) {
                maze.at(nowTop.first).at(nowTop.second) = 2;
                prevTop = nowTop;
                coordStack.push(nextTop);
                continue;
            }
        }

        //allowed to move DOWN
        if (nowTop.first <= maze.size() - 2 && nowTop.first + 1 != prevTop.first) {
            nextTop = pair<int, int>(nowTop.first + 1, nowTop.second);
            if (maze.at(nextTop.first).at(nextTop.second) == 1) {
                maze.at(nowTop.first).at(nowTop.second) = 2;
                prevTop = nowTop;
                coordStack.push(nextTop);
                continue;
            }
        }

        //allowed to move LEFT
        if (nowTop.second >= 1 && nowTop.second - 1 != prevTop.second) {
            nextTop = pair<int, int>(nowTop.first, nowTop.second - 1);
            if (maze.at(nextTop.first).at(nextTop.second) == 1) {
                maze.at(nowTop.first).at(nowTop.second) = 2;
                prevTop = nowTop;
                coordStack.push(nextTop);
                continue;
            }
        }

        //allowed to move UP
        if (nowTop.first >= 1 && nowTop.first - 1 != prevTop.first) {
            nextTop = pair<int, int>(nowTop.first - 1, nowTop.second);
            if(maze.at(nextTop.first).at(nextTop.second) == 1){
                maze.at(nowTop.first).at(nowTop.second) = 2;
                prevTop = nowTop;
                coordStack.push(nextTop);
                continue;
            }
        }

        //no directions left - DEAD END! Time to go back to nearest coordinate that offers alternate direction.
        maze.at(nowTop.first).at(nowTop.second) = 6;
        coordStack.pop();
        pair<int, int> tempTop = coordStack.top();
        coordStack.pop();
        prevTop = coordStack.top();
        coordStack.push(tempTop);
    }

    //by this point, the first element in stack is (0, 0), and the top is the intended destination
    string output = "";
    while(!coordStack.empty()){
        nowTop = coordStack.top();
        output = "(" + to_string(nowTop.first) + ", " + to_string(nowTop.second) + ") -> " + output;
        coordStack.pop();
    }
    cout << output;
    cout << "(" + to_string(x) + ", " + to_string(y) + ")";
}

int main(){
    vector<vector<int>> maze;
    maze = getInput();
    int x;
    cin >> x;
    int y;
    cin >> y;

    solveMaze(maze, x, y);

    return 0;
}
