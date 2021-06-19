#pragma once

#include <random>

using namespace std;

static class RandomValues {
public:
	static int RandInt(int min, int max);
	static double Normal(double mu, double sigma);
	static double Cauchy(double mu, double gamma);
	static double RandDouble(int min, int max);
};