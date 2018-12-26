// Daily Coding Problem #9

#include <vector>
#include <algorithm>
#include <stdio.h>

int largestNonadjacentIntegerSum(const std::vector<int>& arr) {
	// Prev is the best sum up to i-1
	// PrevPrev is the best sum up to i-2
	int sum = 0, i = 0, prev = 0, prevPrev = 0;
	while (i < (int)arr.size()) {
		sum = std::max(prevPrev + arr[i++], prev);

		prevPrev = prev;
		prev = sum;
	}
	return sum;
}

int main() {
	std::vector<int> test = { 2,4,6,2,5 };
	printf("%i\n", largestNonadjacentIntegerSum(test));

	system("pause");
	return 0;
}