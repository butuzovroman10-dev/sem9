#include "analysis.h"
#include "coin_change.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace chrono;

void Analysis::measureAlgorithm(const string& name, 
                               function<int(const vector<int>&, int)> func,
                               const vector<int>& coins, int amount) {
    auto start = high_resolution_clock::now();
    int result = func(coins, amount);
    auto end = high_resolution_clock::now();
    
    auto duration_ms = duration_cast<milliseconds>(end - start);
    auto duration_us = duration_cast<microseconds>(end - start);
    
    cout << name << ": результат = " << result 
         << ", время = ";
    
    if (duration_ms.count() > 0) {
        cout << duration_ms.count() << " мс";
    } else {
        cout << duration_us.count() << " мкс";
    }
    cout << endl;
}

void Analysis::runComplexityAnalysis() {
    cout << "=== Анализ вычислительной сложности ===" << endl;
    
    vector<int> coins = {1, 2, 5, 10};
    
    cout << "\n1. Вычислительная сложность полного перебора:" << endl;
    cout << "   - Временная сложность: O(S^n), где S - сумма, n - количество типов монет" << endl;
    cout << "   - Пространственная сложность: O(n) для рекурсивного стека" << endl;
    cout << "   - В худшем случае: экспоненциальная сложность" << endl;
    cout << "   - Практический предел: суммы до 50-70" << endl;
    
    cout << "\n2. Вычислительная сложность динамического программирования:" << endl;
    cout << "   - Временная сложность: O(n × S)" << endl;
    cout << "   - Пространственная сложность: O(S)" << endl;
    cout << "   - Полиномиальная сложность" << endl;
    cout << "   - Практический предел: суммы до 100000+" << endl;
}

void Analysis::testDifferentInputSizes() {
    cout << "\n=== Тестирование на различных размерах входных данных ===" << endl;
    
    vector<int> coins = {1, 2, 5, 10, 20, 50, 100};
    
    vector<int> testAmounts = {100, 500, 1000, 2000, 5000, 10000, 15000, 20000};
    
    cout << setw(10) << "Сумма" << setw(20) << "Время ДП" 
         << setw(15) << "Результат" << setw(20) << "Время на монету" << endl;
    cout << string(65, '-') << endl;
    
    for (int amount : testAmounts) {
        // Измеряем время для динамического программирования
        auto start = high_resolution_clock::now();
        int result = CoinChange::dynamicProgramming(coins, amount);
        auto end = high_resolution_clock::now();
        
        auto time_ns = duration_cast<nanoseconds>(end - start);
        double time_per_coin = (result > 0) ? time_ns.count() / (double)result : 0;
        
        string time_str;
        if (time_ns.count() < 1000) {
            time_str = to_string(time_ns.count()) + " нс";
        } else if (time_ns.count() < 1000000) {
            time_str = to_string(time_ns.count() / 1000.0) + " мкс";
        } else {
            time_str = to_string(time_ns.count() / 1000000.0) + " мс";
        }
        
        cout << setw(10) << amount 
             << setw(20) << time_str
             << setw(15) << result
             << setw(20) << fixed << setprecision(2) << time_per_coin << " нс" << endl;
    }
    
    // Тестируем полный перебор на маленьких значениях
    cout << "\nТестирование полного перебора (малые значения):" << endl;
    vector<int> smallAmounts = {10, 20, 30, 40, 50};
    
    for (int amount : smallAmounts) {
        auto start = high_resolution_clock::now();
        int result = CoinChange::bruteforce(coins, amount);
        auto end = high_resolution_clock::now();
        auto time = duration_cast<microseconds>(end - start);
        
        cout << "Сумма " << amount << ": " << result << " монет, время: " 
             << time.count() << " мкс" << endl;
    }
}

void Analysis::compareAlgorithms() {
    cout << "\n=== Сравнение алгоритмов ===" << endl;
    
    vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200, 500};
    int amount = 20000;
    
    cout << "Монеты: ";
    for (int coin : coins) cout << coin << " ";
    cout << "\nСумма: " << amount << endl << endl;
    
    // Только динамическое программирование для больших сумм
    measureAlgorithm("Динамическое программирование", CoinChange::dynamicProgramming, coins, amount);
    
    // Показываем разницу на маленькой сумме
    cout << "\nСравнение на маленькой сумме (50):" << endl;
    measureAlgorithm("Полный перебор", CoinChange::bruteforce, coins, 50);
    measureAlgorithm("Дин. программирование", CoinChange::dynamicProgramming, coins, 50);
    
    cout << "\nПрактический предел применимости алгоритмов:" << endl;
    cout << "- Полный перебор: суммы до 50-70 с небольшим набором монет" << endl;
    cout << "- Динамическое программирование: суммы до 100000+ " << endl;
    cout << "- Для суммы 20000 время выполнения ~1-10 мс" << endl;
}