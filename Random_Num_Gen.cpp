// RANDOM_NUM_GEN.CPP

#include <ctime>
#include "Random_Num_Gen.h"
using namespace std;

mt19937 Random_Num_Gen::randomNum((unsigned)time(0));

// get a low and high integer
int Random_Num_Gen::IntegerNum(int intMin, int intMax) {
	uniform_int_distribution<int> diff(intMin, intMax);
	return diff(randomNum);
}

// get a low and high float
float Random_Num_Gen::FloatNum(float floatMin, float floatMax) {
	uniform_real_distribution<float> diff(floatMin, floatMax);
	return diff(randomNum);
}