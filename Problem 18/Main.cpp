// Daily Coding Problem #18

#include <vector>
#include <deque>
#include <stdio.h>

void maxK_SubarrayValues(const std::vector<int>& arr, int k) {
	if (k <= 0) {
		printf("Please enter a positive k.\n");
		return;
	}
	if (k > (int)arr.size()) {
		printf("Please enter a k that is of lower value than the array size.\n");
		return;
	}

	// We maintain a deque that represents a decreasing sequence of
	// the largest elements in the current subarray
	// subarray [10, 2, 5] -> decreasing sequence [10, 5]
	std::deque<int> decreasingSeq;

	// Fill the deque with the first subarray
	int i = 0;
	for (; i < k; ++i) {
		while ((!decreasingSeq.empty()) && decreasingSeq.back() < arr[i]) {
			decreasingSeq.pop_back();
		}
		decreasingSeq.push_back(arr[i]);
	}
	printf("%d ", decreasingSeq.front());

	for (; i < (int)arr.size(); i++) {
		while ((!decreasingSeq.empty()) && decreasingSeq.back() < arr[i]) {
			decreasingSeq.pop_back();
		}
		if ((!decreasingSeq.empty()) && arr[i - k] == decreasingSeq.front()) {
			decreasingSeq.pop_front();
		}
		decreasingSeq.push_back(arr[i]);
		printf("%d ", decreasingSeq.front());
	}
	printf("\n");
}

int main() {

	maxK_SubarrayValues({ 12, 1, 78, 90, 57, 89, 56 }, 3);

	system("pause");
}