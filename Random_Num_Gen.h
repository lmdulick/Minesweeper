// RANDOM_NUM_GEN.H

#pragma once
#include <random>

class Random_Num_Gen {
	static std::mt19937 randomNum;
public:
	static int IntegerNum(int intMin, int intMax);
	static float FloatNum(float floatMin, float floatMax);
};