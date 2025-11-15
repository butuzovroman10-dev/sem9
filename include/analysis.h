#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <vector>
#include <string>
#include <functional>

class Analysis {
public:
    static void runComplexityAnalysis();
    static void testDifferentInputSizes();
    static void compareAlgorithms();
    
private:
    static void measureAlgorithm(const std::string& name, 
                                std::function<int(const std::vector<int>&, int)> func,
                                const std::vector<int>& coins, int amount);
};

#endif