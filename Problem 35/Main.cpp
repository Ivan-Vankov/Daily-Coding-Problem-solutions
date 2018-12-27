// Daily Coding Problem #35

#include <string>
#include <stdio.h>

void rgb_sort_util(std::string& rgb, int& i, int& j, char c) {
	for (j = i; j < (int)rgb.size(); ++j) {
		if (rgb[j] == c) {
			std::swap(rgb[j], rgb[i++]);
		}
	}
}

void rgb_sort(std::string& rgb) {
	int i = 0, j = 0;
	rgb_sort_util(rgb, i, j, 'R');
	rgb_sort_util(rgb, i, j, 'G');
}

int main() {

	std::string rgb = {'G', 'B', 'R', 'R', 'B', 'R', 'G'};

	printf("%s sorted is:", rgb.c_str());
	rgb_sort(rgb);
	printf(" %s\n", rgb.c_str());

	system("pause");
}