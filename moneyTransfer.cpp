/* 
    this program is written for Shopee Code League 2022 qualification round
    P5. Money Transfer, successfully attempted.

    Wanna Wannasin 19/03/2022
*/

#include<iostream>
#include<string>
#include<map>

int main()
{
    int accountNo, orderNo;
    std::map<std::string, long long int> bankBalance;
    
    std::cin >> accountNo >> orderNo;

    while(accountNo--)
    {
        std::string owner;
        long long int netWorth;
        
        std::cin >> owner >> netWorth;
        bankBalance[owner] = netWorth;
    }

    while(orderNo--)
    {
        std::string source, destination;
        long long int amount;

        std::cin >> source >> destination >> amount;

        if(bankBalance[source] < amount)
            continue;
        
        bankBalance[source] -= amount;
        bankBalance[destination] += amount;
    }

    for(auto i : bankBalance)
        std::cout << i.first << ' ' << i.second << std::endl;
}