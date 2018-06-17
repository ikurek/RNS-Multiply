#include <iostream>
#include <array>
#include "Conversions.h"
#include "MRNMultiply.h"

// Formating << operator to support int128 type
static ostream &operator<<(ostream &dest, __int128_t value) {
    ostream::sentry s(dest);
    if (s) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = std::end(buffer);
        do {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);
        if (value < 0) {
            --d;
            *d = '-';
        }
        int len = std::end(buffer) - d;
        if (dest.rdbuf()->sputn(d, len) != len) {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

// Works
vector<int128> Conversions::machineValueToRNS(int128 machineValue, vector<long> modules) {
    vector<int128> result;

    for (auto module: modules) {
        result.push_back(machineValue % module);
    }

    reverse(result.begin(), result.end());

    return result;
}

int128 Conversions::decimalToMachineValue(float number, long fractionalPartLength, vector<long> modules) {
    int128 moduleProduct = 1;

    for (int i = 0; i < fractionalPartLength; ++i) {
        moduleProduct = moduleProduct * modules[i];
    }

    int128 result = number * moduleProduct;

    return result;
}

int128 Conversions::truncatedMRN(int128 mrnNumber, long fractionalPartLength, vector<long> modules) {
    int128 moduleProduct = 1;
	for (int i = 0; i < fractionalPartLength; ++i) {
		moduleProduct = moduleProduct * modules[i];
	}
    int128 result = mrnNumber / moduleProduct;
	return result;
}

double Conversions::RNStoDec(vector<int128> rnsNum, int fractionalPartLength, vector<long> modules) {
    int128 allModProduct = MRNMultiply::findModulesProduct(modules, modules.size());
	cout << "\n Big M: " << allModProduct << endl;
    vector<int128> paramM;
    vector<int128> paramB;
    int128 param;
	for (int i = 0; i < modules.size(); ++i) {
		paramM.push_back(allModProduct / modules[i]);
		param = MRNMultiply::findXParameterForMRNConversion(paramM[i], modules[i]);
		paramB.push_back(param);
	}

    int128 sum;
	for (int i = 0; i < modules.size(); ++i) {
		sum += rnsNum[i] * paramB[i] * paramM[i];
	}
	sum %=allModProduct;

	//find Rf - float modulo range
    int128 moduleProduct = 1;
	for (int i = 0; i < fractionalPartLength; ++i) {
		moduleProduct *= modules[i];
	}

    double result = (double) sum / moduleProduct;
	return result;

}
