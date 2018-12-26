// Daily Coding Problem #1

#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <unordered_set>

bool pairWithTargetSum(const std::vector<int>& list, int sum) {
	std::unordered_set<int> encountered;
	for (int num: list) {
		if (encountered.find(sum - num) != encountered.end()) {
			return true;
		}
		encountered.insert(num);
	}
	return false;
}

int main() {

	printf("%d\n", pairWithTargetSum({10,15,3,7}, 17));

	system("pause");
	return 0;
}