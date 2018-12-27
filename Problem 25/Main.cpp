// Daily Coding Problem #25

#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>

bool specialStrcmp(const std::string& regex, const std::string& str,
	int regexidx1, int regexidx2, int stridx) {
	if (regexidx2 < regexidx1) {
		return true;
	}
	for (int i = stridx, j = regexidx1; j <= regexidx2; ++i, ++j) {
		if (regex[j] != str[i]) {
			return false;
		}
	}
	return true;
}

// '.' recognises all characters
// '*' recognises an arbitrary amount of chars (zero included)
bool regexMatch(const std::string& regex, const std::string& str) {
	// A vector of the indexes of all the stars in the regex
	std::vector<int> stars;
	for (int i = 0; i < (int)regex.size(); ++i) {
		if (regex[i] == '*') {
			stars.push_back(i);
		}
	}
	if (stars.empty()) {
		if (regex.size() != str.size()) {
			return false;
		}
		for (int i = 0; i < (int)regex.size(); ++i) {
			if (regex[i] == '.') { continue; }
			if (regex[i] != str[i]) {
				return false;
			}
		}
	}
	else {
		if (regex.size() > str.size()) {
			return false;
		}
		// Cycle for the regex before the first *
		int k = 0;
		for (; k < stars[0]; ++k) {
			if (regex[k] == '.') { continue; }
			if (regex[k] != str[k]) {
				return false;
			}
		}
		// ".*at*cake"
		// "chatandcake"
		for (int i = 1; i < (int)stars.size(); ++i) {
			for (; k < (int)str.size(); ++k) {
				// If there is a match on index k
				if (specialStrcmp(regex, str, (int)stars[i - 1] + 1, (int)stars[i] - 1, k)) {
					break;
				}
			}
			// If there wasn't a match
			if (k == (int)str.size()) {
				return false;
			}
			else {
				k += (int)stars[i] - (int)stars[i - 1] - 1;
			}
		}
		// Cycle for the regex after the last *
		k = (int)str.size() - ((int)regex.size() - (int)stars.back()) + 1;
		for (int i = (int)stars.back() + 1; i < (int)regex.size(); ++i, ++k) {
			if (regex[i] == '.') { continue; }
			if (regex[i] != str[k]) {
				return false;
			}
		}
	}
	return true;
}

int main() {

	std::string regex("ch.*c*ake");
	std::string str("chatandcake");

	printf("%d\n", regexMatch(regex, str));

	system("pause");
}