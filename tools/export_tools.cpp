#include "export_tools.h"
#include <iomanip>
#include <sstream>

using namespace std;

void ExportTools::exportToCSV(const vector<TestResult>& results, const string& filename) {
    ofstream file(filename);
    
    // Заголовок CSV
    file << "Amount,TimeMicroseconds,Coins,TimePerCoinNanoseconds" << endl;
    
    // Данные
    for (const auto& result : results) {
        file << result.amount << ","
             << fixed << setprecision(2) << result.time << ","
             << result.coins << ","
             << fixed << setprecision(2) << result.timePerCoin << endl;
    }
    
    file.close();
    cout << "✅ Данные экспортированы в " << filename << endl;
}

void ExportTools::exportToJSON(const vector<TestResult>& results, const string& filename) {
    ofstream file(filename);
    
    file << "{\n";
    file << "  \"testResults\": [\n";
    
    for (size_t i = 0; i < results.size(); ++i) {
        const auto& result = results[i];
        file << "    {\n";
        file << "      \"amount\": " << result.amount << ",\n";
        file << "      \"timeMicroseconds\": " << fixed << setprecision(2) << result.time << ",\n";
        file << "      \"coins\": " << result.coins << ",\n";
        file << "      \"timePerCoinNanoseconds\": " << fixed << setprecision(2) << result.timePerCoin << "\n";
        file << "    }";
        
        if (i < results.size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    
    file << "  ]\n";
    file << "}\n";
    
    file.close();
    cout << "✅ Данные экспортированы в " << filename << endl;
}

string ExportTools::escapeJSON(const string& input) {
    string output;
    for (char c : input) {
        switch (c) {
            case '"': output += "\\\""; break;
            case '\\': output += "\\\\"; break;
            case '\b': output += "\\b"; break;
            case '\f': output += "\\f"; break;
            case '\n': output += "\\n"; break;
            case '\r': output += "\\r"; break;
            case '\t': output += "\\t"; break;
            default: output += c; break;
        }
    }
    return output;
}

void ExportTools::generateReport(const vector<TestResult>& results) {
    // Генерируем оба формата
    exportToCSV(results, "coin_change_results.csv");
    exportToJSON(results, "coin_change_results.json");
    
    cout << "\n📊 Отчеты созданы:\n";
    cout << "   - coin_change_results.csv\n";
    cout << "   - coin_change_results.json\n";
    cout << "   - report.html (обновлен с графиками)\n";
}