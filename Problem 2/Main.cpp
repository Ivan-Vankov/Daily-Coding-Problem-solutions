// Daily Coding Problem #2

#include <cstdlib>
#include <stdio.h>
#include <vector>

std::vector<int> productOfAllExceptSelf(const std::vector<int>& list) {
	int size = (int)list.size();
	if (!size) { return std::vector<int>(); }
	if (size == 1) { return { 1 }; } // The empty product is 1
	if (size == 2) { return { list[1], list[0] }; }
	
	// Size - 2 because the a rightProducts with size <size> 
	// will always end with ...,list.back(),1>
	std::vector<int> rightProducts(size - 2);

	rightProducts[size - 3] = list[size - 1] * list[size - 2];

	for (int i = size - 4; i >= 0; --i) {
		rightProducts[i] = list[i + 1] * rightProducts[i + 1];
	}

	std::vector<int> final(size);
	final[0] = rightProducts[0];
	int leftProduct = 1;
	int i = 0;
	for (; i < size - 2; ++i) {
		final[i] = leftProduct * rightProducts[i];
		leftProduct *= list[i];
	}

	final[i++] = leftProduct * list.back();
	final[i] = leftProduct * list[i - 1];

	return final;
}

int main() {

	std::vector<int>&& vector(productOfAllExceptSelf({ 1,2,3,4,5 }));

	for (int i : vector) {
		printf("%d ", i);
	}
	printf("\n");

	system("pause");
	return 0;
}