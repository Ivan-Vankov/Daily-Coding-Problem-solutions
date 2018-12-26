// Daily Coding Problem #12

#include <cstdlib>
#include <stdio.h>
#include <vector>

long long int basicFibb(long long int n) {
	if (n <= 2) { return n; }
	long long int buff[3] = { 1,2 };
	long long int i = 3;
	while (i <= n) {
		buff[2] = buff[1] + buff[0];
		buff[0] = buff[1];
		buff[1] = buff[2];
		++i;
	}
	return buff[2];
}

void fastFibb(long long int n, long long int arr[2]) {
	if (n == 0) {
		arr[0] = 0;
		arr[1] = 1;
		return;
	}
	fastFibb(n / 2, arr);
	// arr[0] == fibb(n/2)
	// arr[1] == fibb(n/2 + 1)
	long long int f_n = arr[0] * (arr[1] * 2 - arr[0]);
	long long int f_nplus1 = arr[0] * arr[0] + arr[1] * arr[1];
	if (n % 2 == 0) {
		arr[0] = f_n;
		arr[1] = f_nplus1;
	}
	else {
		arr[0] = f_nplus1;
		arr[1] = f_n + f_nplus1;
	}
}

long long int staircaseClimb(long long int steps) {
	if (steps < 0)   { return -1; }
	if (steps < 150) { return basicFibb(steps); }
	else { 
		long long int arr[2] = { 0 }; 
		fastFibb(steps, arr);
		return arr[1];
	}
}

int staircaseClimb(int n, const std::vector<int>& steps) {
	int max = 0;
	int min = INT_MAX;
	for (int i : steps) {
		if (i > max) {
			max = i;
		}
		if (i < min) {
			min = i;
		}
	}

	if (min > n) { return 0; }

	int lower = max < n ? max + 1 : n;

	std::vector<int> table(lower--, 0);

	for (int i = 0; i < (int)steps.size(); ++i) {
		if (steps[i] - 1 < (int)table.size()) {
			++table[steps[i] - 1];
		}
	}

	for (int i = 0; i < lower; ++i) {
		for (int j = 0; j < (int)steps.size(); ++j) {
			if (steps[j] <= i) {
				table[i] += table[i - steps[j]];
			}
		}
	}

	for (int i = lower; i < n; ++i) {
		for (int j = 0; j < (int)steps.size(); ++j) {
			table[lower] += table[lower - steps[j]];
		}
		for (int k = 0; k < lower; ++k) {
			table[k] = table[k + 1];
		}
		if (i < n - 1) {
			table[lower] = 0;
		}
	}

	return table.back();
}

int main() {

	printf("%d\n",   staircaseClimb(40, { 1,2 }));
	printf("%lld\n", staircaseClimb(40));

	system("pause");
	return 0;
}