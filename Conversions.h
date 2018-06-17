#ifndef RNS_MULTIPLY_CONVERSIONS_H
#define RNS_MULTIPLY_CONVERSIONS_H

#include <vector>

using namespace std;
typedef __int128 int128;


static class Conversions {
public:
    static vector<int128> machineValueToRNS(int128 machineValue, vector<long> modules);

    static int128 decimalToMachineValue(float number, long fractionalPartLength, vector<long> modules);

    static int128 truncatedMRN(int128 MRNnumber, long fractionalPartLength, vector<long> modules);


	//static vector<long> findDecimalParameters(vector<long> modules);
    static double RNStoDec(vector<int128> rnsNum, int fractionalPartLength, vector<long> modules);
};


#endif //RNS_MULTIPLY_CONVERSIONS_H
