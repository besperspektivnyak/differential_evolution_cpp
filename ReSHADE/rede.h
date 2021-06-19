#pragma once

#include<iostream>
#include <iomanip>
#include <string.h>
#include <vector>
#include <math.h>
#include <cfloat>
#include <limits>
#include <time.h>

using namespace std;

class Individual {
private:
	vector <double> individual;

public:
	Individual operator+(Individual i2) {
		Individual i_new;
		for (int i = 0; i < this->individual.size(); i++) {
			i_new.individual.push_back(this->individual[i] + i2.individual[i]);
		}
		return i_new;
	}

	Individual operator-(Individual i2) {
		Individual i_new;
		for (int i = 0; i < this->individual.size(); i++) {
			i_new.individual.push_back(this->individual[i] - i2.individual[i]);
		}
		return i_new;
	}

	Individual operator*(double num) {
		Individual i_new;
		for (int i = 0; i < this->individual.size(); i++) {
			i_new.individual.push_back(this->individual[i] * num);
		}
		return i_new;
	}

	void push_back(double elem) {
		this->individual.push_back(elem);
	}

	int size() {
		return (int)individual.size();
	}

	double get(int index) {
		return individual[index];
	}

	void set(int index, double num) {
		individual[index] = num;
	}
};

typedef double (*func)(Individual x);

class ReSHADE {
private:
	vector <Individual> population;
	int problemSize;
	int populationSize;
	int max_iterations;
	vector <double> borders;
	func function;

	void CreatePopulation();
	Individual Mutation(int index, double F);
	int FindMin(vector <int> nums);
	int FindMax(vector <int> nums);
	Individual FindV(int bestInd, int worstInd, int t1, int t2, int r0, int F);
	Individual Crossover(Individual x, Individual v, double Cr);
	vector <int> ChooseVectorNums(int index);
	vector <int> FindIndexes(vector <int> inds, int bestInd, int worstInd);
public:
	ReSHADE(func function_, int problemSize_, int populationSize_, int maxnfes_, vector <double> borders_) {
		borders.push_back( borders_[0]);
		borders.push_back(borders_[1]);
		function = function_;
		problemSize = problemSize_;
		populationSize = populationSize_;
		max_iterations = maxnfes_;
	}
	double RunReDE();
	double RunReSHADE();

};