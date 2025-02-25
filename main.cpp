#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "StateClimate.h"

// Binary search function
int binarySearch(const std::vector<StateClimate>& data, int year) {
    int left = 0;
    int right = data.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data[mid].getYear() == year) {
            return mid;
        } else if (data[mid].getYear() < year) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; 
}

int main() {
    std::vector<StateClimate> climateData;
    std::ifstream file("climdiv_state_year.csv");
    
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line); // Skip header line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string fipsStr, yearStr, tempStr, tempcStr;

        std::getline(ss, fipsStr, ',');
        std::getline(ss, yearStr, ',');
        std::getline(ss, tempStr, ',');
        std::getline(ss, tempcStr, ',');

        int fips = std::stoi(fipsStr);
        int year = std::stoi(yearStr);
        double temp = std::stod(tempStr);
        double tempc = std::stod(tempcStr);

        climateData.emplace_back(fips, year, temp, tempc);
    }

    file.close();

    // Sort data by year
    std::sort(climateData.begin(), climateData.end());

    // Display data
    for (const auto &entry : climateData) {
        entry.display();
    }

    // Perform binary search for a specific year
    int searchYear = 2020; // Example year to search for
    int index = binarySearch(climateData, searchYear);
    if (index != -1) {
        std::cout << "Record found for year " << searchYear << ":" << std::endl;
        climateData[index].display();
    } else {
        std::cout << "No record found for year " << searchYear << std::endl;
    }

    return 0;
}