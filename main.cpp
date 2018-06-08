#include <iostream>
#include <vector>
#include "Conversions.h"
#include "MRNMultiply.h"

using namespace std;

// Vectors for modules
vector<long> modules = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61};
vector<long> modulesReversed;

// Number of modules for fractional part
long fractionalPartLength = 7;

// Machine values od x and y
long long xMachineValue;
long long yMachineValue;

// RNS values of x and y
vector<long> xRNS;
vector<long> yRNS;

// Intermediate product
vector<long> intermediateProduct;
vector<long> intermediateProductReversed;

// Parameters required for MRN conversion
vector<long> mrnConversionParameters;

// Works
void printVector(vector<long> vectorToPrint) {
    cout << "[ ";
    for (auto element: vectorToPrint)
        cout << element << ' ';
    cout << "]";
}


int main() {
    std::cout << "RNS - Multiply" << std::endl;

    // Reverse modules
    modulesReversed = modules;
    reverse(modulesReversed.begin(), modulesReversed.end());

    // Read x and y as floats
    float x;
    float y;
    cout << endl;
    cout << "X (Decimal): ";
    cin >> x;
    cout << "Y (Decimal): ";
    cin >> y;

    // Print modules at start
    cout << endl;
    cout << "Modules (Decimal): " << endl;
    cout << "    ==> Values: ";
    printVector(modules);
    cout << endl;
    cout << "    ==> Reversed: ";
    printVector(modulesReversed);
    cout << endl;
    cout << "    ==> Elements: " << modules.size() << endl;

    // Convert numbers to machine value
    xMachineValue = Conversions::decimalToMachineValue(x, fractionalPartLength, modules);
    yMachineValue = Conversions::decimalToMachineValue(y, fractionalPartLength, modules);

    // Print machine values
    cout << endl;
    cout << "Numbers (Machine Value):" << endl;
    cout << "    ==> X: " << xMachineValue << endl;
    cout << "    ==> Y: " << yMachineValue << endl;

    // Convert values to RNS
    xRNS = Conversions::machineValueToRNS(xMachineValue, modules);
    yRNS = Conversions::machineValueToRNS(yMachineValue, modules);

    // Print machine value converted to RNS
    cout << endl;
    cout << "Numbers (RNS):" << endl;
    cout << "    ==> X: ";
    printVector(xRNS);
    cout << endl;
    cout << "        ==> X Elements: " << xRNS.size() << endl;
    cout << "    ==> Y: ";
    printVector(yRNS);
    cout << endl;
    cout << "        ==> Y Elements: " << yRNS.size() << endl;

    // Find intermediate product
    intermediateProduct = MRNMultiply::calculateIntermediateProduct(xRNS, yRNS, modulesReversed);

    // Reverse intermediate product
    intermediateProductReversed = intermediateProduct;
    reverse(intermediateProductReversed.begin(), intermediateProductReversed.end());

    // Print intermediate product
    cout << endl;
    cout << "Intermediate product (RNS):" << endl;
    cout << "    ==> Value: ";
    printVector(intermediateProduct);
    cout << endl;
    cout << "    ==> Reversed: ";
    printVector(intermediateProductReversed);
    cout << endl;
    cout << "    ==> Elements: " << intermediateProduct.size() << endl;

    // Break before calculations
    string continueConfirmation;
    cout << endl;
    cout << "Continue? (y/n): ";
    cin >> continueConfirmation;

    if (continueConfirmation != "y")
        return 0;

    // Calculate parameters for MRN conversions
    // Method prints itself
    mrnConversionParameters = MRNMultiply::calculateRNStoMRNConversionParameters(modules, modulesReversed,
                                                                                 intermediateProductReversed);


    return 0;
}



