#include <iostream>
#include <vector>
#include "Conversions.h"
#include "MRNMultiply.h"
#include <array>

using namespace std;

typedef __int128 int128;

// Vectors for modules
vector<long> modules = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
vector<long> modulesReversed;

// Number of modules for fractional part
long fractionalPartLength = 7;

// Machine values od x and y
int128 xMachineValue;
int128 yMachineValue;

// RNS values of x and y
vector<int128> xRNS;
vector<int128> yRNS;

// Intermediate product
vector<int128> intermediateProduct;
vector<int128> intermediateProductReversed;

// Parameters required for MRN conversion
vector<int128> mrnConversionParameters;
int128 MRNnumber;
vector<int128> MRNtoRNS;
int128 truncatedMRN;
vector<int128> MRNtoRNStrunc;


double check;


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

void printVector(vector<long> vectorToPrint) {
    cout << "[ ";
    for (auto element: vectorToPrint)
        cout << element << ' ';
    cout << "]";
}

void printVector(vector<int128> vectorToPrint) {
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
    mrnConversionParameters = MRNMultiply::calculateRNStoMRNConversionParameters(modules, intermediateProductReversed);

    // Performing MRN conversion
	MRNnumber = MRNMultiply::calculateMRNnumber(modules, intermediateProductReversed, mrnConversionParameters);
    cout << "    == > MRN Number: " << MRNnumber << endl;
	MRNtoRNS = Conversions::machineValueToRNS(MRNnumber, modulesReversed);
	cout << "Product (MRN) in RNS:" << endl;
	cout << "    ==> : ";
	printVector(MRNtoRNS);
	cout << endl;

    // Truncating MRN number
	truncatedMRN = Conversions::truncatedMRN(MRNnumber, fractionalPartLength, modules);

    // Converting back to RNS
	MRNtoRNStrunc = Conversions::machineValueToRNS(truncatedMRN, modulesReversed);
	cout << "Product (truncated MRN) in RNS:" << endl;
	cout << "    ==> : ";
	printVector(MRNtoRNStrunc);
	cout << endl;

    // Converting from RNS to decimal
    check = Conversions::RNStoDec(MRNtoRNStrunc, fractionalPartLength, modules);
	cout << "Product (RNS) in Decimal:" << endl;
	cout << "    ==> : "<< check<< endl;

	return 0;
}
