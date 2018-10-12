#include "rng.h"
#include <random>
#include <time.h>
std::default_random_engine rng::randomEngine((unsigned int)time(NULL));

float rng::rand(float min, float max) {
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(randomEngine);
}
int rng::rand(int min, int max) {
	//return rand() % (max - min + 1) + min;
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(randomEngine);
}