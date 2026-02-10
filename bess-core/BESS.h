#ifndef BESS_H
#define BESS_H 

#include <vector> 

class BESS {
private:
    std::vector<double> originalCurve;
    std::vector<double> resultCurve;

    int startHour;
    int endHour;

    bool dispatchIntervalSet;
    bool dispatchComputed;

    void isCurveSet() const;
    bool isWithinDispatchInterval(int hour, int start, int end) const;


public: 

    BESS();

    void setOriginalCurve(const std::vector<double>&curve);

    double getDailyStoredEnergy() const;
    double getMonthlyStoredEnergy() const;

    void setDispatchInterval(int start, int end);

    void batteryDischarge();

    std::vector<double> getResultCurve() const;
    double getResultAt(int t) const;

};

#endif