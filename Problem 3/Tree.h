#pragma once

#include <string>
#include <fstream>
#include "Node.h"

class Tree {
public:
	Tree(Node* root);

	void serialize(const std::string& toFile) const;
	void deserialize(const std::string& fromFile);

	void destroy();

private:
	void serialize(const Node* currNode, std::ofstream& ofile) const;
	void deserialize(std::ifstream& ifile);

	void deserializeUtil(Node*& currNode, std::ifstream& ifile);

	void destroy(Node* currNode);

private:
	Node * root;
};