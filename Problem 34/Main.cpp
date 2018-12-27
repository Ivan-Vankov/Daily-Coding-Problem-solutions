// Daily Coding Problem #34

#include <string>
#include <stdio.h>

std::string to_palindrome(const std::string& str) {
	std::string palindrome;
	palindrome.reserve(str.size() / 2);
	int i = 0, j = (int)str.size() - 1;
	while (i < j) {
		if (str[i] < str[j]) {
			while (str[i] != str[j] && i < j) {
				palindrome.push_back(str[i++]);
			}
		}
		else if (str[i] > str[j]) {
			while (str[i] != str[j] && i < j) {
				palindrome.push_back(str[j--]);
			}
		}
		else {
			palindrome.push_back(str[i++]);
			--j;
		}
	}
	std::string buffer;
	buffer.reserve(2 * palindrome.size() + 1);
	buffer += palindrome;
	if (i == j) {
		buffer.push_back(str[i]);
	}
	for (int m = (int)palindrome.size() - 1; m >= 0; --m) {
		buffer.push_back(palindrome[m]);
	}
	return buffer;
}

int main() {

	std::string str = "google";

	printf("%s is converted to %s\n", str.c_str(), to_palindrome(str).c_str());

	system("pause");
}