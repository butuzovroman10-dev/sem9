#include "coin_change.h"
#include "analysis.h"
#include "export_tools.h"
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

vector<TestResult> performAutomatedTesting() {
    cout << "🤖 Запуск автоматизированного тестирования..." << endl;
    
    vector<int> coins = {1, 2, 5, 10, 20, 50, 100};
    vector<int> testAmounts = {100, 500, 1000, 2000, 5000, 10000, 15000, 20000};
    
    vector<TestResult> results;
    
    for (int amount : testAmounts) {
        auto start = high_resolution_clock::now();
        int coinsCount = CoinChange::dynamicProgramming(coins, amount);
        auto end = high_resolution_clock::now();
        
        auto time_ns = duration_cast<nanoseconds>(end - start);
        double time_us = time_ns.count() / 1000.0;
        double timePerCoin = (coinsCount > 0) ? time_ns.count() / (double)coinsCount : 0;
        
        results.push_back({amount, time_us, coinsCount, timePerCoin});
        
        cout << "   Сумма: " << amount 
             << " | Монет: " << coinsCount 
             << " | Время: " << time_us << " мкс" << endl;
    }
    
    return results;
}

void demonstrateBasicUsage() {
    cout << "=== Демонстрация решения задачи размена монет ===" << endl;
    
    vector<int> coins1 = {1, 2, 5};
    int amount1 = 11;
    
    cout << "\nПример 1:" << endl;
    cout << "Монеты: 1, 2, 5" << endl;
    cout << "Сумма: " << amount1 << endl;
    
    CoinChange::printSolution(coins1, amount1, 0);
    CoinChange::printSolution(coins1, amount1, 1);
}

int main() {
    demonstrateBasicUsage();
    
    // Запуск анализа
    Analysis::runComplexityAnalysis();
    Analysis::testDifferentInputSizes();
    Analysis::compareAlgorithms();
    
    // Автоматизированное тестирование и экспорт
    auto results = performAutomatedTesting();
    ExportTools::generateReport(results);
    
    cout << "\n🎉 Все задачи выполнены!" << endl;
    cout << "📁 Проверьте созданные файлы:" << endl;
    cout << "   - report.html (графики и визуализация)" << endl;
    cout << "   - coin_change_results.csv" << endl;
    cout << "   - coin_change_results.json" << endl;
    
    return 0;
}