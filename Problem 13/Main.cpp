// Daily Coding Problem #13

#include <string>
#include <unordered_set>

int kSubstring(const std::string& str, int k) {
	int start = 0;
	int end = 0;
	std::unordered_set<char> activeChars;
	int len = (int)str.length();
	int lower = k < len ? k : len;
	for (; end < lower; ++end) {
		if (activeChars.find(str[end]) == activeChars.end()) {
			activeChars.insert(str[end]);
		}
	}

	while (end < len) {
		if (activeChars.find(str[end]) != activeChars.end()) {
			++end;
		}
		else if ((int)activeChars.size() < k) {
			activeChars.insert(str[end++]);
		}
		else {
			activeChars.erase(str[start++]);
		}
	}

	return end - start;
}

int main() {
	
	printf("%i\n", kSubstring("abcbd", 2));

	system("pause");
	return 0;
}