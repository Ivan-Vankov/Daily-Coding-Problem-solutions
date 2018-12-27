// Daily Coding Problem #74

#include <iostream>

// Special matrix:
// i-th row and j-th column is (i + 1) * (j + 1) (if 0-indexed) 
// or i * j (if 1-indexed)

int solve(int N, int X) {
	int cnt = 0;
	int smaller = N < X ? N : X;
	for (int i = 1; i <= smaller; ++i) {
		cnt += X % i == 0 && X <= i * N;
	}
	return cnt;
}

int main() {
	int N = 6, X = 12;
	std::cout << X << " found <" << solve(N, X) << "> times in special " 
		<< N << "x" << N << " matrix" << std::endl;
	system("pause");
}