// Daily Coding Problem #17

#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>

int longestAbsolutePath(const std::string& fileSys) {
	int currDepth = 0;
	int prevDepth = 0;
	int longestPath = 0;
	std::vector<int> currPath;
	int currWordLen = 0;
	int currPathLen = 0;

	for (int i = 0; i < (int)fileSys.size(); ++i) {
		if (fileSys[i] != '\n'){
			++currWordLen;
			++currPathLen;
		}
		else {
			currPath.push_back(currWordLen);
			if (currPathLen > longestPath) {
				longestPath = currPathLen;
			}

			prevDepth = currDepth;
			currDepth = 0;
			while (fileSys[++i] == '\t') {
				++currDepth;
			}
			if (currDepth == prevDepth + 1) {
				currPathLen += 2; //.../c...(we count the / as a symbol)
			}
			else {
				for (int j = 0; j < prevDepth + 1 - currDepth; ++j) {
					currPathLen -= currPath.back() + 1;
					currPath.pop_back();
				}
				currPathLen += 2; // Add the .../c (c for random char)
			}
			currWordLen = 1;
		}
	}

	return currPathLen > longestPath ? currPathLen : longestPath;
}

int main() {

	std::string fileSys("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext");
	// Represents:
	//dir
	//	subdir1
	//		file1.ext
	//		subsubdir1
	//	subdir2
	//		subsubdir2
	//			file2.ext

	printf("%d\n", longestAbsolutePath(fileSys));

	system("pause");
	return 0;
}