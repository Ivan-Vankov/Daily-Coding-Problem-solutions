// Daily Coding Problem #19

#include <cstdlib>
#include <stdio.h>
#include <vector>

int kColoredNeighbourhood(const std::vector<std::vector<int>>& priceMatrix) {
	int n = (int)priceMatrix.size();
	if (n <= 0) { return -1; }
	int k = (int)priceMatrix.back().size();
	if (k <= 1) { return -1; }

	// 2 x k buffer matrix
	std::vector<std::vector<int>> buffer(2);
	buffer[0].resize(k);
	buffer[1].resize(k);

	// Act as the minimum and second to minumum element of buffer[flip]
	int mins[2][2] = {
		{ INT_MAX ,INT_MAX },
		{ INT_MAX ,INT_MAX } 
	};

	// Fill the first row of the buffer matrix 
	// and get the min and second to min from it
	for (int i = 0; i < k; ++i) {
		buffer[0][i] = priceMatrix[0][i];
		if (mins[0][0] > buffer[0][i]) {
			mins[0][1] = mins[0][0];
			mins[0][0] = buffer[0][i];
		}
		else if (mins[0][1] > buffer[0][i]) {
			mins[0][1] = buffer[0][i];
		}
	}

	int flip = 1;
	int revFlip = 0;

	for (int i = 1; i < n; ++i, revFlip = flip, flip = (flip + 1) % 2) {
		for (int j = 0; j < k; ++j) {
			buffer[flip][j] = priceMatrix[i][j];
			if (buffer[revFlip][j] != mins[revFlip][0]) {
				buffer[flip][j] += mins[revFlip][0];
			}
			else {
				buffer[flip][j] += mins[revFlip][1];
			}

			if (mins[flip][0] > buffer[flip][j]) {
				mins[flip][1] = mins[flip][0];
				mins[flip][0] = buffer[flip][j];
			}
			else if (mins[flip][1] > buffer[flip][j]) {
				mins[flip][1] = buffer[flip][j];
			}
		}
		// Reset the mins
		mins[revFlip][0] = mins[revFlip][1] = INT_MAX;
	}

	return mins[revFlip][0];
}

int main() {

	std::vector<std::vector<int>> priceMatrix = {
		{10, 11, 9 },
		{15, 13, 12},
		{5 , 6 , 4 },
		{8 , 7 , 9 },
		{9 , 10, 12} 
	};

	printf("%d\n", kColoredNeighbourhood(priceMatrix));

	system("pause");
}