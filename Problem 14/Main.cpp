// Daily Coding Problem #14

#include <random>
#include <iostream>
#include <ctime>
#include <cmath>
#include <omp.h>

double piApproximation(long long allPoints) {
	std::mt19937 mt((unsigned int)time(nullptr));
	std::uniform_real_distribution<double> dist(-1.0, 1.0);

	long long insideCircle = 0;

	#pragma omp parallel for
	for (long long i = 0; i < allPoints; ++i) {
		double x = dist(mt);
		double y = dist(mt);
		if ((x * x + y * y) < 1.0) {
			++insideCircle;
		}
	}

	return ((double)insideCircle / (double)allPoints) * 4.0;
}

int main() {

	long long samples = 10'000'000;

	std::cout << piApproximation(samples) << std::endl;

	system("pause");
	return 0;
}