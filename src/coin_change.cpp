#include "coin_change.h"
#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

// Реализация метода полного перебора
int CoinChange::bruteforceRecursive(const vector<int>& coins, int amount, int index) {
    // Базовые случаи
    if (amount == 0) return 0;
    if (amount < 0) return -1;
    if (index >= coins.size()) return -1;
    
    int minCoins = INT_MAX;
    
    // Пробуем использовать текущую монету от 0 до максимально возможного количества
    int maxUse = amount / coins[index];
    
    for (int use = 0; use <= maxUse; use++) {
        int remaining = amount - use * coins[index];
        int result = bruteforceRecursive(coins, remaining, index + 1);
        
        if (result != -1) {
            minCoins = min(minCoins, use + result);
        }
    }
    
    return (minCoins == INT_MAX) ? -1 : minCoins;
}

int CoinChange::bruteforce(const vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    if (coins.empty()) return -1;
    
    // Сортируем монеты по убыванию для более эффективного перебора
    vector<int> sortedCoins = coins;
    sort(sortedCoins.rbegin(), sortedCoins.rend());
    
    return bruteforceRecursive(sortedCoins, amount, 0);
}

// Реализация метода динамического программирования
int CoinChange::dynamicProgramming(const vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    if (coins.empty()) return -1;
    
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    
    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[amount] > amount ? -1 : dp[amount];
}

void CoinChange::printSolution(const vector<int>& coins, int amount, int method) {
    int result;
    string methodName;
    
    if (method == 0) {
        result = bruteforce(coins, amount);
        methodName = "Полный перебор";
    } else {
        result = dynamicProgramming(coins, amount);
        methodName = "Динамическое программирование";
    }
    
    cout << methodName << ": ";
    if (result == -1) {
        cout << "Невозможно разменять сумму " << amount << endl;
    } else {
        cout << "Минимальное количество монет для суммы " << amount 
             << ": " << result << endl;
    }
}