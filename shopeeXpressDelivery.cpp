/* 
    this program is written for Shopee Code League 2022 qualification round
    P1. Shopee Xpress Delivery.

    using of flood-fill approch

    Wanna Wannasin 19/03/2022
*/

#include<iostream>
#include<utility> 
#include<cstring>
#include<vector>
#include<queue>
#include<map>

int main()
{
    int m, n;
    std::vector<std::vector<int> > grid;
    std::map<int, std::vector<std::pair<int, int> > > blackHoles;

    std::cin >> m >> n;
    for(int i = 0; i < m; i++)
    {
        std::vector<int> row;
        for(int j = 0; j < n; j++)
        {
            int number;
            std::cin >> number;
            row.push_back(number);

            if(number != 0)
                blackHoles[number].push_back(std::make_pair(i, j));
        }
        grid.push_back(row);
        
    }

    bool visited[101][101];
    int stepCount[101][101];
    std::queue<std::pair<int, int> > nextSteps;
    std::memset(visited, false, sizeof(visited));

    nextSteps.push(std::make_pair(0, 0));
    visited[0][0] = true;
    stepCount[0][0] = 0;

    while(1)
    {
        std::pair<int, int> currentLocation;
        int curX, curY;

        currentLocation = nextSteps.front();
        nextSteps.pop();
        curX = currentLocation.first;
        curY = currentLocation.second;

        if(curX == m - 1 && curY == n - 1)
            break;

        int positionX[] = {0, 0, 1, -1}, positionY[] = {1, -1, 0, 0};
        for(int i = 0; i < 4; i++)
        {
            int newX = curX + positionX[i], newY = curY + positionY[i];

            if(newX < 0 || newY < 0 || newX >= m || newY >= n)
                continue;

            if(visited[newX][newY])
                continue;
            
            nextSteps.push(std::make_pair(newX, newY));
            stepCount[newX][newY] = stepCount[curX][curY] + 1;
            visited[newX][newY] = true;

            if(grid[curX][curY] != 0)
            {
                std::vector<std::pair<int, int> > blackHole;
                blackHole = blackHoles[grid[curX][curY]];
                for(auto i : blackHole)
                //for(int i = 0; i < blackHole.size(); i++)
                {
                    newX = i.first;
                    newY = i.second;
                    if(newX < 0 || newY < 0 || newX >= m || newY >= n)
                        continue;

                    if(visited[newX][newY])
                        continue;
            
                    nextSteps.push(i);
                    stepCount[newX][newY] = stepCount[curX][curY];
                    visited[newX][newY] = true;
                }
            }
        }
    }

    std::cout << stepCount[m - 1][n - 1];
}