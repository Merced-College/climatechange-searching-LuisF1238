// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>            // for std::sort
#include "StateClimate.h"       // make sure this path matches your project

int main() {
    // 1. Load data
    std::vector<StateClimate> climateData;
    std::ifstream file("climdiv_state_year.csv");
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int fips, year;
        double temp, tempc;
        char comma;
        ss >> fips >> comma 
           >> year >> comma 
           >> temp >> comma 
           >> tempc;
        climateData.emplace_back(fips, year, temp, tempc);
    }
    file.close();

    // 2. Sort by FIPS code
    std::sort(climateData.begin(), climateData.end(),
        [](const StateClimate &a, const StateClimate &b) {
            return a.getFips() < b.getFips();
        });

    // 3. Repeatedly prompt & binary‐search
    std::string input;
    while (true) {
        std::cout << "Enter a FIPS code to search (or 'exit' to quit): ";
        std::getline(std::cin, input);

        if (input == "exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }

        // convert input to integer
        int key;
        try {
            key = std::stoi(input);
        } catch (...) {
            std::cout << "Invalid input. Please enter a numeric FIPS code or 'exit'." 
                      << std::endl;
            continue;
        }

        // binary search [0 .. size-1]
        int left = 0, right = static_cast<int>(climateData.size()) - 1;
        bool found = false;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int midFips = climateData[mid].getFips();
            if (midFips == key) {
                climateData[mid].display();
                found = true;
                break;
            } 
            else if (midFips < key) {
                left = mid + 1;
            } 
            else {
                right = mid - 1;
            }
        }

        if (!found) {
            std::cout << "State not found. Please try again." << std::endl;
        }
    }

    return 0;
}
