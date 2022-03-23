/* 
    this program is written for Shopee Code League 2022 qualification round
    P3. Firework Festival problem

    using of dynamic programming approch

    Wanna Wannasin 19/03/2022
*/

#include<iostream>
#include<stdlib.h>
#include<vector>
#include<map>
using namespace std;
int numberRoad, numberFirework, walkRange;
map<int, vector<pair<int, int> > > fireworkOrder;

int startingCoin = 0;

map<int, vector<int> > dpMaxCoin;
int maxTime = 0, maxRoad = 0, minTime = 2000000000, minRoad = 2000000000;

int maxCoin(int time, int tile)
{
    cout << "peek " << time << ' ' << tile << endl;
    if(time < minTime)
        return 0;
    if(time == minTime)
        return startingCoin;
    if(dpMaxCoin.find(time) != dpMaxCoin.end() && dpMaxCoin[time][tile])
        return dpMaxCoin[time][tile];
    
    cout << "not base case or calculated, calculate maxCoin time:" << time << " road:" << tile << endl;
    dpMaxCoin[time].resize(numberRoad + 1);

    int currentCoin = 0;
    for(int i = 0; i < fireworkOrder[time].size(); i++)
        currentCoin += max(0, fireworkOrder[time][i].second - abs(fireworkOrder[time][i].first - tile));

    map<int, vector<pair<int, int> > >::iterator itrLower;
    itrLower = fireworkOrder.lower_bound(time);
    itrLower--;
    int lastTime = (*itrLower).first;

    //cout << "last time is " << lastTime << endl;
    int answer = 0;
    for(int i = - (walkRange * (time - lastTime)); i <= (walkRange * (time - lastTime)); i++)
    {
        //cout << "walk from tile " << tile + i << endl;
        if(tile + i > 0 && tile + i < numberRoad)
            answer = max(answer, maxCoin(lastTime, tile + i) + currentCoin);
    }

    cout << ">>" << answer << endl;

    return dpMaxCoin[time][tile] = answer;
}

int main()
{
    cin >> numberRoad >> numberFirework >> walkRange;

    while(numberFirework--)
    {
        int fireworkRoad, fireworkCoin, fireworkTime;
        cin >> fireworkRoad >> fireworkCoin >> fireworkTime;
        fireworkOrder[fireworkTime].push_back(make_pair(fireworkRoad, fireworkCoin));

        if(fireworkTime > maxTime)
            maxTime = fireworkTime;
        if(fireworkTime < minTime)
            minTime = fireworkTime;
    }

    vector<pair<int, int> > startingFirework = fireworkOrder[minTime];
    int startingPos = startingFirework[0].first;

    for(int i = 0; i < startingFirework.size(); i ++)
    {
        startingCoin += startingFirework[i].second - abs((startingFirework[i].first - startingPos));

        if(startingFirework[i].first > maxRoad)
            maxRoad = startingFirework[i].first;
        if(startingFirework[i].first < minRoad)
            minRoad = startingFirework[i].first;
    }

    for(int i = 1; i <= numberRoad; i++)
    {
        if(i >= minRoad && i <= maxRoad)
            dpMaxCoin[minTime].push_back(startingCoin);
        else
            dpMaxCoin[minTime].push_back(0);
    }
    
    int answer = 0;
    for(int i = 1; i <= numberRoad; i++)
    {
        answer = max(answer, maxCoin(maxTime, i));
    }

    cout << answer;
}
/*
10 3 1
1 500 5
9 500 5
5 500 6
*/

/*
10 2 1
1 500 5
9 500 5
*/


/*
20 5 1
1 10 1
5 10 4
10 10 1
15 10 4
18 10 7
*/

/*
20 6 1
1 10 1
10 10 1
5 10 4
15 10 4
18 10 20
18 10 21
*/
