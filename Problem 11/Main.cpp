// Daily Coding Problem #11

#include "AutocompleteTrie.h"
#include <stdio.h>

int main() {
	AutocompleteTrie trie;

	std::string keys[5] = { "all","a","buzz","buck","zarr" };
	for (std::string i : keys) {
		trie.insert(i);
	}

	trie.autocomplete("bu");

	system("pause");
	return 0;
}