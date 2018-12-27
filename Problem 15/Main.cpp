// Daily Coding Problem #15

#include <fstream>
#include <random>
#include <time.h>

int getRandomStreamElem(std::ifstream& ifile) {
	int buff = 0;
	int res = -1;
	if (!ifile >> buff) {
		return -1;
	}
	else {
		res = buff;
	}
	std::mt19937 mt((unsigned)time(nullptr));
	std::uniform_real_distribution<> dist;
	for (int i = 2; ifile >> buff; ++i) {
		if (dist(mt) <= 1.0 / (double)i) {
			res = buff;
		}
	}
	if (!ifile.eof()) {
		return -1;
	}
	ifile.close();
	return res;
}

int main() {

	std::ifstream ifile("1to10000.txt");

	printf("%d\n", getRandomStreamElem(ifile));

	system("pause");
}