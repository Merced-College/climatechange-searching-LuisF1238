#ifndef STATECLIMATE_H
#define STATECLIMATE_H

#include <iostream>

class StateClimate {
private:
    int fips;
    int year;
    double temp;
    double tempc;
public:
    // Constructor
    StateClimate(int f, int y, double t, double tc);
    // Getters
    int getFips() const;
    int getYear() const;
    double getTemp() const;
    double getTempC() const;
    // Setters
    void setFips(int f);
    void setYear(int y);
    void setTemp(double t);
    void setTempC(double tc);
    // Display function
    void display() const;
    // Comparison operator for sorting
    bool operator<(const StateClimate& other) const;
};

#endif // STATECLIMATE_H