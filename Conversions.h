#ifndef RNS_MULTIPLY_CONVERSIONS_H
#define RNS_MULTIPLY_CONVERSIONS_H

#include <vector>

using namespace std;

static class Conversions {
public:
    static vector<long> machineValueToRNS(long machineValue, vector<long> modules);

    static long long decimalToMachineValue(float number, long fractionalPartLength, vector<long> modules);
};


#endif //RNS_MULTIPLY_CONVERSIONS_H
