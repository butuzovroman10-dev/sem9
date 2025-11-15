#include "coin_change.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

void testBasicCases() {
    cout << "Тестирование базовых случаев..." << endl;
    
    // Тест 1: Обычный случай
    vector<int> coins1 = {1, 2, 5};
    assert(CoinChange::bruteforce(coins1, 11) == 3);
    assert(CoinChange::dynamicProgramming(coins1, 11) == 3);
    
    // Тест 2: Невозможный размен
    vector<int> coins2 = {2};
    assert(CoinChange::bruteforce(coins2, 3) == -1);
    assert(CoinChange::dynamicProgramming(coins2, 3) == -1);
    
    // Тест 3: Сумма равна 0
    vector<int> coins3 = {1, 2, 5};
    assert(CoinChange::bruteforce(coins3, 0) == 0);
    assert(CoinChange::dynamicProgramming(coins3, 0) == 0);
    
    // Тест 4: Один тип монет
    vector<int> coins4 = {1};
    assert(CoinChange::bruteforce(coins4, 5) == 5);
    assert(CoinChange::dynamicProgramming(coins4, 5) == 5);
    
    cout << "Все базовые тесты пройдены успешно!" << endl;
}

void testLargeAmount() {
    cout << "\nТестирование большой суммы (20000)..." << endl;
    
    vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200, 500};
    int amount = 20000;
    
    auto start = high_resolution_clock::now();
    int result = CoinChange::dynamicProgramming(coins, amount);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    
    cout << "Сумма: " << amount << endl;
    cout << "Результат: " << result << " монет" << endl;
    cout << "Время выполнения: " << duration.count() << " мс" << endl;
    
    // Проверяем что решение корректное (для суммы 20000 минимальное количество монет = 40)
    assert(result == 40); // 20000 / 500 = 40
    
    cout << "Тест большой суммы пройден!" << endl;
}

void testPerformance() {
    cout << "\nТестирование производительности..." << endl;
    
    vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200, 500};
    vector<int> testAmounts = {100, 500, 1000, 5000, 10000, 15000, 20000};
    
    cout << "Размер суммы | Время (мс) | Результат" << endl;
    cout << "------------------------------------" << endl;
    
    for (int amount : testAmounts) {
        auto start = high_resolution_clock::now();
        int result = CoinChange::dynamicProgramming(coins, amount);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        
        cout << amount << "         | " 
             << duration.count() << "         | " 
             << result << endl;
    }
}

void testEdgeCases() {
    cout << "\nТестирование граничных случаев..." << endl;
    
    // Тест с максимальной суммой для демонстрации
    vector<int> coins = {1, 2, 5};
    int amount = 20000;
    
    auto start = high_resolution_clock::now();
    int result = CoinChange::dynamicProgramming(coins, amount);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    
    cout << "Граничный случай - сумма 20000 с мелкими монетами:" << endl;
    cout << "Результат: " << result << " монет" << endl;
    cout << "Время: " << duration.count() << " мс" << endl;
    
    // Для монет {1, 2, 5} сумма 20000 должна размениваться
    assert(result > 0);
    cout << "Граничные случаи пройдены!" << endl;
}

int main() {
    testBasicCases();
    testLargeAmount();
    testPerformance();
    testEdgeCases();
    
    cout << "\n✅ Все тесты успешно пройдены!" << endl;
    return 0;
}