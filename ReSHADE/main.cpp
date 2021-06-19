#include <stdlib.h>
#include<iostream>
#include <vector>
#include <time.h>
#include "rede.h"

using namespace std;

double Spherical(Individual x) {
	double res = 0;
	for (int i = 0; i < x.size(); i++) {
		res += pow(x.get(i), 2);
	}
	return res;
}

double Func2(Individual x) {
	double sum = 0, p = 0, res = 0;
	for (int i = 0; i < x.size(); i++) {
		sum += fabs(x.get(i));
		p *= fabs(x.get(i));
	}
	res = sum + p;
	return res;
}



int main() {
	srand(time(0));
	vector <double> borders = { -10, 10 };
	ReSHADE test = ReSHADE(Func2, 30, 100, 100000, borders);
	double res = test.RunReSHADE();
	cout << res;
	return 0;
}