// Daily Coding Problem #26

#include <cstdlib>
#include <stdio.h>
#include <forward_list>

void print_list(const std::forward_list<int>& list) {
	for (int i : list) {
		printf("%d ", i);
	}
	printf("\n");
}

void remove_kth_last(int k, std::forward_list<int>& list) {
	auto iter = list.begin();
	for (int i = 0; i <= k; ++i, ++iter);
	auto k_iter = list.begin();
	while (iter != list.end()) {
		++iter; 
		++k_iter;
	}
	list.erase_after(k_iter);
}

int main() {

	std::forward_list<int> list = {
		28,	31,	47,	96,	3,
		65,	34,	43,	11,	84,
		16,	92,	39,	34,	72,
		4,	6,	29,	50,	43,
		38,	92,	11,	65,	55,
		32,	59,	64,	93,	96,
		79,	25,	3,	64,	10,
		64,	86,	47,	58,	33,
		84,	80,	99,	65,	37,
		14,	84,	40,	47,	69,
		26,	87,	57,	31,	57,
		69,	98,	36,	83,	22,
		5,	10,	50,	98,	74,
		29,	50,	25,	16,	36,
		57,	83,	66,	71,	75,
		66,	68,	35,	85,	20,
		7,	23,	90,	75,	34,
		52,	60,	74,	60,	35,
		75,	92,	65,	52,	33,
		7,	40,	81,	77,	63
	};

	print_list(list);
	remove_kth_last(2, list);
	print_list(list);

	system("pause");
}