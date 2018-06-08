#ifndef RNS_MULTIPLY_MRNMULTIPLY_H
#define RNS_MULTIPLY_MRNMULTIPLY_H

#include <vector>
#include <iostream>

using namespace std;

static class MRNMultiply {
public:
    static vector<long>
    calculateIntermediateProduct(vector<long> xRNS, vector<long> yRNS, vector<long> modulesReversed);

    static long long int findModulesProduct(vector<long> modules, long end);

    static long findXParameterForMRNConversion(long pi, long pn);

    static vector<long> calculateRNStoMRNConversionParameters(vector<long> modules, vector<long> modulesReversed,
                                                              vector<long> intermediateProductReversed);

};

#endif //RNS_MULTIPLY_MRNMULTIPLY_H
