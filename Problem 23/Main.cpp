// Daily Coding Problem #23

#include <cstdlib>
#include "Labirinth.h"

const std::vector<std::vector<bool>> labirinth = {
	{ 1,1,1,1 },
	{ 0,0,1,0 },
	{ 1,1,1,1 },
	{ 1,1,1,1 }
};

int main() {

	Labirinth matrix(labirinth, std::make_pair(3, 0), std::make_pair(0, 0));
	matrix.AstarPathfinding();

	system("pause");
}