#include <iostream>
#include "Conversions.h"

// Works
vector<long> Conversions::machineValueToRNS(long machineValue, vector<long> modules) {
    vector<long> result;

    for (auto module: modules) {
        result.push_back(machineValue % module);
    }

    reverse(result.begin(), result.end());

    return result;
}

long long Conversions::decimalToMachineValue(float number, long fractionalPartLength, vector<long> modules) {
    long long moduleProduct = 1;

    for (int i = 0; i < fractionalPartLength; ++i) {
        moduleProduct = moduleProduct * modules[i];
    }

    long long result = number * moduleProduct;

    return result;
}
