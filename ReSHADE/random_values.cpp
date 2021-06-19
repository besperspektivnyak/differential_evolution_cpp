#include "random_values.h"

int RandomValues::RandInt(int min, int max) {

	random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	uniform_real_distribution<> dis(min, max);

	return (int)dis(gen);
}

double RandomValues::RandDouble(int min, int max) {
	random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	uniform_real_distribution<> dis(min, max);

	return dis(gen);

}

double RandomValues::Normal(double mu, double sigma) {
	random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	normal_distribution<> dis(mu, sigma);

	return dis(gen);
}

double RandomValues::Cauchy(double mu, double gamma) {
	random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	cauchy_distribution<> dis(mu, gamma);

	return dis(gen);
}
