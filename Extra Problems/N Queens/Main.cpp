#include <stdio.h>
#include <cstdlib>
#include <vector>

bool willCollide(const std::vector<int>& queens, int newQueen) {
	int len = (int)queens.size();

	for (int i = 0; i < len; ++i) {
		// If their columns are the same
		if (queens[i] == newQueen) {
			return true;
		}
		//// If they intersect on the diagonals
		// If the 
		else if (queens[i] > newQueen) {
			//	x-n,y+n
			//	  /
			// x,y
			if (queens[i] + i == newQueen + len) {
				return true;
			}
		}
		else {
			// x+n,y+n
			//	  \
			//    x,y
			if (queens[i] - i == newQueen - len) {
				return true;
			}
		}
	}
	return false;
}

void nQueens(int n, std::vector<int>& queens, int& count){
	if ((int)queens.size() == n) { 
		++count;
		return; 
	}

	for (int i = 0; i < n; ++i) {
		if (!willCollide(queens, i)) {
			queens.push_back(i);
			nQueens(n, queens, count);
			queens.pop_back();
		}
	}
}

int nQueens(int n) {
	if (n <= 0) { 
		printf("Please enter a positive integer.\n");
		return -1;
	}
	//// Table is enumerated this way
	//// ^ ^
	////  \|
	//// <-(0,0)
	//// 
	// Array of size n where the i-th member is the i-th queen's collumn
	std::vector<int> queens;
	queens.reserve(n);
	int count = 0;
	nQueens(n, queens, count);
	return count;
}

int main() {

	printf("%d\n", nQueens(10));

	system("pause");
}