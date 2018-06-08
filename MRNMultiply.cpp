#include "MRNMultiply.h"

// Works
vector<long>
MRNMultiply::calculateIntermediateProduct(vector<long> xRNS, vector<long> yRNS, vector<long> modulesReversed) {
    vector<long> result;

    // iterate over all reversed modules
    for (long i = 0; i < modulesReversed.size(); ++i) {

        // Calculate value of current position in intermediate product
        long value = (xRNS[i] * yRNS[i]) % modulesReversed[i];

        result.push_back(value);
    }

    return result;
}

// FIXME: Overflow passes 64bit long long value
long long MRNMultiply::findModulesProduct(vector<long> modules, long end) {
    long long result = modules[0];

    for (long i = 1; i < end; ++i) {
        result = result * modules[i];
    }

    return result;
}

// Works
long MRNMultiply::findXParameterForMRNConversion(long pi, long pn) {
    long x = 0;

    while (((pi * x) % pn) != 1) {
        x++;
    }

    return x;
}

// FIXME: Errors inside
vector<long> MRNMultiply::calculateRNStoMRNConversionParameters(vector<long> modules, vector<long> modulesReversed,
                                                                vector<long> intermediateProductReversed) {
    vector<long> result;

    cout << endl;
    cout << "MRN Conversion Parameters:" << endl;

    // 1st parameter is the same as last value of intermediate product
    result.push_back(intermediateProductReversed[0]);

    // Print 1st param info
    cout << "    ==> A0: " << result[0] << endl;
    cout << "        ==> Modulus Product: " << 0 << endl;
    cout << "        ==> X Parameter: " << 0 << endl;
    cout << "        ==> First Formula Part: " << 0 << endl;
    cout << "        ==> Second Formula Part: " << 0 << endl;
    cout << "        ==> Third Formula Part: " << 0 << endl;
    cout << "        ==> Fourth Formula Part: " << 0 << endl;
    cout << "        ==> Value: " << result[0] << endl;

    // Iterate over all modules, skipping 1st position
    // Searching for parameter for each position of RNS number (intermediate product)
    for (long i = 1; i < modulesReversed.size(); ++i) {

        // Variables for single iteration of A
        long long currentModulusProduct = modules[0];
        long currentXParameter = 0;
        long formulaFirstPart = 0;
        long formulaSecondPart = 0;
        long formulaThirdPart = 0;
        long formulaFourthPart = 0;


        // Calculating first part of formula
        if (i == 1) {
            currentXParameter = findXParameterForMRNConversion(modules[0], modules[i]);
            formulaFirstPart = findXParameterForMRNConversion(modules[0], modules[i]);
        } else {
            currentModulusProduct = findModulesProduct(modules, i);
            currentXParameter = findXParameterForMRNConversion(currentModulusProduct, modules[i]);
            formulaFirstPart = findXParameterForMRNConversion(currentModulusProduct, modules[i]);
        }


        // Calculating second part of formula
        formulaSecondPart = formulaFirstPart % modules[i];

        // Calculate third part of formula
        formulaThirdPart = result[0];
        for (int j = 0; j < i; ++j) {

            // Skipping 0
            if (j != 0) {
                formulaThirdPart = formulaThirdPart + (result[j] * modules[j - 1]);
            }

        }

        // Calculate fourth part
        formulaFourthPart = intermediateProductReversed[i] - formulaThirdPart;

        // Calculate final value of current A
        long value = (formulaSecondPart * formulaFourthPart) % modules[i];

        // Save value
        result.push_back(value);


        // Print information of current A calculations
        cout << "    ==> A" << i << ": " << endl;
        cout << "        ==> Modulus Product: " << currentModulusProduct << endl;
        cout << "        ==> X Parameter: " << currentXParameter << endl;
        cout << "        ==> First Formula Part: " << formulaFirstPart << endl;
        cout << "        ==> Second Formula Part: " << formulaSecondPart << endl;
        cout << "        ==> Third Formula Part: " << formulaThirdPart << endl;
        cout << "        ==> Fourth Formula Part: " << formulaFourthPart << endl;
        cout << "        ==> Value: " << value << endl;

    }

    return result;
}