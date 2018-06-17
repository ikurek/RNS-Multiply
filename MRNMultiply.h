#ifndef RNS_MULTIPLY_MRNMULTIPLY_H
#define RNS_MULTIPLY_MRNMULTIPLY_H

#include <vector>
#include <iostream>

using namespace std;
typedef __int128 int128;

static class MRNMultiply {
public:
    static vector<int128>
    calculateIntermediateProduct(vector<int128> xRNS, vector<int128> yRNS, vector<long> modulesReversed);

    static int128 findModulesProduct(vector<long> modules, long end);

    static int128 findXParameterForMRNConversion(int128 pi, int128 pn);

    static vector<int128>
    calculateRNStoMRNConversionParameters(vector<long> modules, vector<int128> intermediateProductReversed);

    static int128
    calculateMRNnumber(vector<long> modules, vector<int128> intermediateProductReversed, vector<int128> MRNparameters);
};

#endif //RNS_MULTIPLY_MRNMULTIPLY_H
