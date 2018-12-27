// Daily Coding Problem #22

#include <cstdlib>
#include <unordered_set>
#include <list>
#include <string>

void getOriginalSentence(const std::unordered_set<std::string>& dictionary,
					const std::string& sentence, std::list<std::string>& tempList,
					std::string currWord = "", int i = 0) {
	for (; i < (int)sentence.size(); ++i) {
		currWord.push_back(sentence[i]);
		if (dictionary.find(currWord) != dictionary.end()) {
			tempList.push_back(currWord);
			currWord.clear();
		}
	}

	// Lets say the sentence is bardic
	// and the dictionary is "bard" and "bardic"
	// and whe have identified bard
	// then the cicle will end and currWord will be "ic"
	// which is not what we want
	if (!currWord.empty()) {
		i -= (int)currWord.size();
		currWord = tempList.back();
		tempList.pop_back();
		getOriginalSentence(dictionary, sentence, tempList, currWord, i);
	}
}

std::list<std::string> getOriginalSentence(const std::unordered_set<std::string>& dictionary,
									const std::string& sentence) {
	std::list<std::string> tempList;
	getOriginalSentence(dictionary, sentence, tempList);
	return tempList;
}

int main() {

	std::unordered_set<std::string> dictionary = {
		"bed", "bath", "bedbath", "and", "beyond"
	};

	std::string sentence = "bedbathandbeyond";

	//std::unordered_set<std::string> dictionary = {
	//	"bard", "bardic"
	//};

	//std::string sentence = "bardic";

	std::list<std::string> OriginalSentence = 
		getOriginalSentence(dictionary, sentence);

	for (std::string word : OriginalSentence) {
		printf("%s ", word.c_str());
	}
	printf("\n");

	system("pause");
}