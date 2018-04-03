#include <fstream>
#include <iostream>

int main()
{
    // File for input
    std::ifstream csvData;
    csvData.open("G16_1.csv", std::ios::in);
    if (!csvData) {
        std::cerr << "Unable to open csv file";
        exit(1);
    }

    // File for output
    std::ofstream csvAvg;
    csvAvg.open("G16_2.csv", std::ios::out);
    if (!csvAvg) {
        std::cerr << "Unable to create csv file for output";
        exit(1);
    }

    int sumHappy = 0;
    int sumComp  = 0;
    int avgHappy = 0;
    int avgComp  = 0;
    int total    = 0;
    int scenario = 0;
    int current;

    while (csvData >> current) {
        scenario += current;
        // Tracks total items
        total++;
        // Skip next 7 items
        for (int skip = 0; skip < 7; skip++) {
            csvData >> current;
        }
        // read happiness
        csvData >> current;
        sumHappy += current;
        // Skip
        csvData >> current;
        // read competitiveness
        csvData >> current;
        sumComp += current;
    }
    // Calculate and write averages to csv
    avgHappy = sumHappy / total;
    avgComp  = sumComp / total;
    scenario = scenario / total;
    csvAvg << scenario;
    csvAvg << avgHappy;
    csvAvg << avgComp;

    // Clean up files
    csvData.close();
    csvAvg.close();

    return 0;
}
