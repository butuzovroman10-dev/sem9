#ifndef COIN_CHANGE_H
#define COIN_CHANGE_H

#include <vector>

class CoinChange {
public:
    // Метод полного перебора (рекурсивный)
    static int bruteforce(const std::vector<int>& coins, int amount);
    
    // Оптимизированный метод (динамическое программирование)
    static int dynamicProgramming(const std::vector<int>& coins, int amount);
    
    // Вспомогательные функции
    static void printSolution(const std::vector<int>& coins, int amount, int method);
    
private:
    // Рекурсивная функция для полного перебора
    static int bruteforceRecursive(const std::vector<int>& coins, int amount, int index);
};

#endif