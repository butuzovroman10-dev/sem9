#ifndef EXPORT_TOOLS_H
#define EXPORT_TOOLS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct TestResult {
    int amount;
    double time;
    int coins;
    double timePerCoin;
};

class ExportTools {
public:
    static void exportToCSV(const std::vector<TestResult>& results, const std::string& filename);
    static void exportToJSON(const std::vector<TestResult>& results, const std::string& filename);
    static void generateReport(const std::vector<TestResult>& results);
    
private:
    static std::string escapeJSON(const std::string& input);
};

#endif