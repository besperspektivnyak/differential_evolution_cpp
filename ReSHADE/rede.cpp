#include "rede.h"
#include "random_values.h"

void ReSHADE::CreatePopulation() {
	for (int i = 0; i < populationSize; i++) {
		Individual tmp;
		for (int j = 0; j < problemSize; j++) {
			tmp.push_back(RandomValues::RandDouble(borders[0], borders[1]));
		}
		population.push_back(tmp);
	}
}


vector <int> ReSHADE::ChooseVectorNums(int index) {
	srand(time(0));
	vector <int> r(4);
	int counter = 0;
	int number = RandomValues::RandInt(0, populationSize - 1);
	while (counter != 4) {
		if (number != r[0] && number != r[1] && number != r[2] && number != r[3] && number != index) {
			r[counter] = number;
			counter++;
		}
		else {
			number = RandomValues::RandInt(0, populationSize - 1);
		}
	}
	return r;
}

int ReSHADE::FindMin(vector <int> nums) {
	double min = (double)INT_MAX;
	int minInd = 0;
	for (int i = 0; i < nums.size(); i++) {
		double funcRes = function(population[nums[i]]);
		if (funcRes < min) {
			minInd = nums[i];
			min = funcRes;
		}
	}
	return minInd;
}

int ReSHADE::FindMax(vector <int> nums) {
	double max = (double)INT_MIN;
	int maxInd = 0;
	for (int i = 0; i < nums.size(); i++) {
		double funcRes = function(population[nums[i]]);
		if (funcRes > max) {
			maxInd = nums[i];
			max = funcRes;
		}
	}
	return maxInd;
}
vector <int> ReSHADE::FindIndexes(vector <int> inds, int bestInd, int worstInd) {
	vector <int> indexes;
	for (int i = 0; i < inds.size(); i++) {
		if (inds[i] != bestInd && inds[i] != worstInd)
			indexes.push_back(inds[i]);
	}
	return indexes;
}

Individual ReSHADE::FindV(int bestInd, int worstInd, int t1, int t2, int r0, int F) {
	double beta = RandomValues::RandDouble(0, 1);

	Individual xc = population[t1] * beta + population[t1] * (1 - beta);
	if (function(population[r0]) <= function(population[worstInd])) {
		Individual vi = xc + (population[bestInd] - xc) * F + (population[r0] - population[worstInd]);
		return vi;
	}
	else {
		Individual vi = xc + (population[bestInd] - xc) * F + (population[worstInd] - population[r0]);
		return vi;
	}

}

Individual ReSHADE::Mutation(int index, double F) {
	vector <int> r = ChooseVectorNums(index);
	int bestInd = FindMin(r);
	int worstInd = FindMax(r);
	vector <int> tIndexes = FindIndexes(r, bestInd, worstInd);
	int r0 = -1;
	while (r0 == -1) {
		int num = RandomValues::RandInt(0, population.size() - 1);
		if (num != bestInd && num != worstInd && num != tIndexes[0] && num != tIndexes[1])
			r0 = num;
	}

	return FindV(bestInd, worstInd, tIndexes[0], tIndexes[1], r0, F);
}

Individual ReSHADE::Crossover(Individual x, Individual v, double Cr) {
	Individual u;
	for (int i = 0; i < x.size(); i++) {
		double num = RandomValues::RandDouble(0, 1);
		int jRand = RandomValues::RandInt(0, x.size() - 1);
		if (num <= Cr || i == jRand)
			u.push_back(v.get(i));
		else
			u.push_back(x.get(i));
	}
	return u;
}


double ReSHADE::RunReDE() {
	double f = 0.8;
	double cr = 0.7;
	CreatePopulation();
	vector <Individual> u;

	int nfes = 0;
	while (nfes < max_iterations) {
		for (int i = 0; i < populationSize; i++) {
			
			Individual vi = Mutation(i, f);
			
			u.push_back(Crossover(population[i], vi, cr));
		}
		for (int i = 0; i < populationSize; i++) {
			if (function(u[i]) <= function(population[i])) {
				for (int j = 0; j < problemSize; j++) {
					population[i].set(j, u[i].get(j));
				}
			}
			
		}

		nfes++;
		u.clear();
		std::cout << "Iteration " << nfes << "\n";
	//	int bestInd = -1;
	//	double bestSol = (double)INT_MAX;
	//	for (int i = 0; i < populationSize; i++) {
	//		double sol = function(population[i]);
	//		if (sol < bestSol) {
	//			bestSol = sol;
	//			bestInd = i;
	//		}
	//	}
	//	cout << "Best solution " << bestSol << "\n";
	//	for (int i = 0; i < problemSize; i++) {
	//		cout << population[bestInd].get(i) << " ";
	//	}
	}
	int bestInd = -1;
	double bestSol = (double)INT_MAX;
	for (int i = 0; i < populationSize; i++) {
		double sol = function(population[i]);
		if (sol < bestSol) {
			bestSol = sol;
			bestInd = i;
		}
	}
	cout << "Best solution " << bestSol << "\n";
	for (int i = 0; i < problemSize; i++) {
		cout << population[bestInd].get(i) << " ";
	}
	return function(population[bestInd]);
}


double ReSHADE::RunReSHADE() {
	vector <double> m_f(populationSize, 0.5);
	vector <double> m_cr(populationSize, 0.5);

	CreatePopulation();

	vector <Individual> u;

	int nfes = 0;
	while (nfes < max_iterations) {
		vector <double> s_f(populationSize, 0);
		vector <double> s_cr(populationSize, 0);

		vector <double> f(populationSize, 0);
		vector <double> cr(populationSize, 0);
		for (int i = 0; i < populationSize; i++) {

			int rand_num = RandomValues::RandInt(0, populationSize);
			cr[i] = RandomValues::Normal(m_cr[rand_num], 0.1);
			f[i] = RandomValues::Cauchy(m_f[rand_num], 0.1);


			// Mutation
			
			Individual vi = Mutation(i, f[i]);

			// Crossover
			
			u.push_back(Crossover(population[i], vi, cr[i]));
			nfes++;
		}
		for (int i = 0; i < populationSize; i++) {
			if (function(u[i]) <= function(population[i])) {
				for (int j = 0; j < problemSize; j++) {
					population[i].set(j, u[i].get(j));
				}
			}

			if (function(u[i]) < function(population[i])) {
				s_cr[i] = cr[i];
				s_f[i] = f[i];
			}
		}
		if (s_cr.size() != 0 && s_f.size() != 0) {
			for (int i = 0; i < populationSize; i++) {
				m_cr[i] = s_cr[i];
				m_f[i] = s_f[i];
			}
		}
		u.clear();
		std::cout << "Iteration " << nfes << "\n";
		/*int bestInd = -1;
		double bestSol = (double)INT_MAX;
		for (int i = 0; i < populationSize; i++) {
			double sol = function(population[i]);
			if (sol < bestSol) {
				bestSol = sol;
				bestInd = i;
			}
		}*/
		//cout << "Best solution " << bestSol << "\n";
		//for (int i = 0; i < problemSize; i++) {
		//	cout << population[bestInd].get(i) << " ";
		//}
	}
	int bestInd = -1;
	double bestSol = (double)INT_MAX;
	for (int i = 0; i < populationSize; i++) {
		double sol = function(population[i]);
		if (sol < bestSol) {
			bestSol = sol;
			bestInd = i;
		}
	}
	cout << "Best solution " << bestSol << "\n";
	for (int i = 0; i < problemSize; i++) {
		cout << population[bestInd].get(i) << " ";
	}
	return function(population[bestInd]);
}
