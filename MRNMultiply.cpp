#include "MRNMultiply.h"
#include <array>

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
vector<int128>
MRNMultiply::calculateIntermediateProduct(vector<int128> xRNS, vector<int128> yRNS, vector<long> modulesReversed) {
    vector<int128> result;

    // iterate over all reversed modules
    for (long i = 0; i < modulesReversed.size(); ++i) {
        // Calculate value of current position in intermediate product
        int128 value = (xRNS[i] * yRNS[i]) % modulesReversed[i];
        result.push_back(value);
    }
    return result;
}

int128 MRNMultiply::findModulesProduct(vector<long> modules, long end) {
    int128 result = modules[0];
    //do 4
    for (long i = 1; i < end; ++i) {
        result = result * modules[i];
    }
    return result;
}

int128 MRNMultiply::findXParameterForMRNConversion(int128 pi, int128 pn) {
    int128 x = 0;
    while (((pi * x) % pn) != 1) {
        x++;
    }
    return x;
}

// FIXME: Errors inside
vector<int128> MRNMultiply::calculateRNStoMRNConversionParameters(vector<long> modules,
                                                                  vector<int128> intermediateProductReversed) {
    vector<int128> result;
    cout << endl;
    cout << "MRN Conversion Parameters:" << endl;

    // 1st parameter is the same as last value of intermediate product
    result.push_back(intermediateProductReversed[0]);

    // Print 1st param info
    cout << "    ==> A0: " << result[0] << endl;
    cout << "        ==> Modulus Product: " << 0 << endl;
    cout << "        ==> X Parameter: " << 0 << endl;
    cout << "        ==> Value: " << result[0] << endl;

    // Iterate over all modules, skipping 1st position
    // Searching for parameter for each position of RNS number (intermediate product)
    for (long i = 1; i < modules.size(); ++i) {
        // Variables for single iteration of A
        int128 currentModulusProduct = modules[0];
        int128 currentXParameter = 0;
        int128 formulaFirstPart = 0;
        int128 formulaSecondPart = 0;
        int128 formulaThirdPart = 0;
        int128 formulaFourthPart = 0;

        if (i == 1) {
            currentXParameter = findXParameterForMRNConversion(modules[0], modules[i]);
            formulaFirstPart = findXParameterForMRNConversion(modules[0], modules[i]);
        } else {
            currentModulusProduct = findModulesProduct(modules, i);
            currentXParameter = findXParameterForMRNConversion(currentModulusProduct, modules[i]);
            formulaFirstPart = currentXParameter;
        }

        // Calculating second part of formula
        formulaSecondPart = formulaFirstPart % modules[i];

        // Calculate third part of formula
        formulaThirdPart = 1;
        for (int j = 1; j < i; ++j) {
            formulaThirdPart = formulaThirdPart * (result[j] * modules[j - 1]);
        }
        formulaThirdPart += result[0];

        // Calculate fourth part
        formulaFourthPart = intermediateProductReversed[i] - formulaThirdPart;
        formulaFourthPart = (modules[i] >= 0 ? modules[i] : -modules[i]) - 1 + (formulaFourthPart + 1) % modules[i];
        
        // Calculate final value of current A
        int128 value = formulaSecondPart * formulaFourthPart;

        // Save value
        result.push_back(value);

        // Print information of current A calculations
        cout << "    ==> A" << i << ": " << endl;
        cout << "        ==> Modulus Product: " << currentModulusProduct << endl;
        cout << "        ==> X Parameter: " << currentXParameter << endl;
        cout << "        ==> Value: " << value << endl;
    }
    return result;
}

int128 MRNMultiply::calculateMRNnumber(vector<long> modules, vector<int128> intermediateProduct,
                                       vector<int128> mrnConversionParameters) {

    int128 MRNnumber = mrnConversionParameters[0];
    int128 currentModProduct = modules[0];

    for (size_t i = 1; i < modules.size(); i++) {
        currentModProduct = findModulesProduct(modules, i);
        cout << " curModProduct: " << currentModProduct << "; i= " << i << endl;

        MRNnumber += mrnConversionParameters[i] * currentModProduct;
    }
    cout << endl;
    return MRNnumber;
};
