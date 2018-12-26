#include "AutocompleteTrie.h"
using std::make_pair;


bool AutocompleteTrie::Node::hasChildren() const{
	return !children.empty();
}

bool AutocompleteTrie::Node::hasChild(char newLetter) const {
	return children.find(newLetter) != children.end();
}

void AutocompleteTrie::Node::addChild(char newLetter) {
	children.insert(make_pair(newLetter, new Node));
}

AutocompleteTrie::Node* AutocompleteTrie::Node::getChild(char newLetter) {
	return children.find(newLetter)->second;
}

bool AutocompleteTrie::Node::isLeaf()const {
	return children.find('#') != children.end();
}

void AutocompleteTrie::Node::makeLeaf() {
	if (isLeaf()) { return; }
	children.insert(make_pair('#', new Node));
}

AutocompleteTrie::AutocompleteTrie(){
	root = new Node;
}

AutocompleteTrie::~AutocompleteTrie(){
	clear(root);
}

void AutocompleteTrie::insert(const std::string& key) {
	int i = 0;
	Node* currNode = root;
	while (i < (int)key.length()) {
		if (!currNode->hasChild(key[i])) {
			currNode->addChild(key[i]);
		}
		currNode = currNode->getChild(key[i++]);
	}
	currNode->makeLeaf();
}

bool AutocompleteTrie::isIn(const std::string& key) const {
	int i = 0;
	Node* currNode = root;
	while (i < (int)key.length()) {
		if (!currNode->hasChild(key[i])) {
			return false;
		}
		currNode = currNode->getChild(key[i++]);
	}
	if (!currNode->isLeaf()) {
		return false;
	}
	else {
		return true;
	}
}

void AutocompleteTrie::autocomplete(const std::string& prefix) const {
	std::vector<std::string> words;
	std::string currWord(prefix);

	// Go through the trie using the prefix
	int i = 0;
	Node* currNode(root);
	while (i < (int)prefix.length()) {
		if (!currNode->hasChild(prefix[i])) {
			return;
		}
		currNode = currNode->getChild(prefix[i++]);
	}

	fillWords(words, currWord, currNode);
	
	for (std::string word : words) {
		printf("%s\n", word.c_str());
	}
}

void AutocompleteTrie::fillWords(std::vector<std::string>& words, std::string& currWord, 
								Node* currNode) const {
	if (currNode->isLeaf()) {
		words.push_back(currWord);
	}

	for (auto i : currNode->children) {
		if (i.first == '#') { continue; }
		// Add next letter to currWord
		currWord.push_back(i.first);
		// Recursively call fillWords
		fillWords(words, currWord, i.second);
		// Remove the letter from currWord
		currWord.pop_back();
	}
}

void AutocompleteTrie::clear(Node* curr) {
	for (auto child = curr->children.begin(); child != curr->children.end(); ++child) {
		clear(child->second);
	}
	delete curr;
}
