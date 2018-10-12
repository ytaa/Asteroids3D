#pragma once
#include <random>
namespace rng{
	extern std::default_random_engine randomEngine;
	float rand(float, float);
	int rand(int, int);
}
