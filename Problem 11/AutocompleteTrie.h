#pragma once

#include <unordered_map>
#include <string>
#include <vector>

//		$(root)
//	   /|\
//	  a b z
//   /| |  \
//	# l u	a
//	 /  |\   \
//   l  z c   r
//	 |  | |   |
//	 #  z k   r
//		| |   |
//		# #   #(leaf | end of key)

class AutocompleteTrie {
	class Node {
	public:
		bool hasChildren()const;
		bool hasChild(char newLetter) const;
		void addChild(char newLetter);
		Node* getChild(char newLetter);
		bool isLeaf()const;
		void makeLeaf();

		std::unordered_map<char, Node*> children;
	};
public:
	AutocompleteTrie();
	~AutocompleteTrie();

	void insert(const std::string& key);

	bool isIn(const std::string& key) const;

	void autocomplete(const std::string& prefix) const;
private:
	void fillWords(std::vector<std::string>& words, std::string& currWord, Node* currNode)const;

	void clear(Node*);

	Node * root;
};
