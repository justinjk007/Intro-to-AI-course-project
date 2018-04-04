#include <fstream>
#include <iostream>
#include <string>

using namespace std;

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

    double sumHappy[3] = {0.0};
    double sumComp[3]  = {0.0};
    int scenario       = 0;
    string cell;

    while (csvData.good()) {
        getline(csvData, cell, ',');
        try {
            scenario = std::stoi(cell);
        } catch (const exception& e) {
            cout << "stuuf is messed up " << cell << "\n";
            cout << e.what() << "\n";
            exit(1);
        }
        for (int skip = 0; skip < 8; skip++) {
            getline(csvData, cell, ',');  // Skip next 7 columns
        }
        getline(csvData, cell, ',');
        sumHappy[scenario - 1] += stod(cell);
        getline(csvData, cell, ',');
        getline(csvData, cell, '\n');
        sumComp[scenario - 1] += stod(cell);
    }
    csvAvg << 1 << "," << sumHappy[0] / 25 << "," << sumComp[0] / 25 << "\n";
    csvAvg << 2 << "," << sumHappy[1] / 25 << "," << sumComp[1] / 25 << "\n";
    csvAvg << 3 << "," << sumHappy[2] / 25 << "," << sumComp[2] / 25 << "\n";

    // Clean up files
    csvData.close();
    csvAvg.close();

    return 0;
}
