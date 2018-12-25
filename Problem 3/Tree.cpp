#include "Tree.h"
#include <iostream>

Tree::Tree(Node* root) {
	this->root = root;
}

void Tree::serialize(const std::string& toFile) const {
	std::ofstream ofile(toFile, std::ios::trunc);
	if (!ofile.is_open()) {
		std::cerr << "Couldn't open file for writing.\n";
		return;
	}
	serialize(root, ofile);
}

void Tree::deserialize(const std::string& fromFile) {
	std::ifstream ifile(fromFile);
	if (!ifile.is_open()) {
		std::cerr << "Couldn't open file for reading.\n";
		return;
	}
	//Node* backup = new Tree(root);
	destroy(root);
	deserialize(ifile);
}

void Tree::destroy() {
	destroy(root);
}

void Tree::serialize(const Node* currNode, std::ofstream& ofile) const {
	ofile << '(' << currNode->val;
	if (currNode->left) {
		serialize(currNode->left, ofile);
	}
	if (currNode->right) {
		serialize(currNode->right, ofile);
	}
	ofile << ')';
}

void Tree::deserialize(std::ifstream& ifile) {
	char firstChar;
	ifile.get(firstChar);
	if (ifile.eof()) {
		return;
	}
	if (firstChar == '(') {
		root = new Node();
		ifile.unget();
		deserializeUtil(root, ifile);
	}
}

void Tree::deserializeUtil(Node*& currNode, std::ifstream& ifile) {
	char bracket;
	// '('
	ifile.get(bracket);
	ifile >> currNode->val;
	// (10')'
	ifile.get(bracket);
	if (bracket == ')') { return; }
	// (10'('...))
	if (bracket == '(') {
		ifile.unget();
		currNode->left = new Node();
		deserializeUtil(currNode->left, ifile);
	}
	ifile.get(bracket);
	// (10(9...)')'
	if (bracket == ')') { return; }
	// (10(9...)'('...))
	if (bracket == '(') {
		ifile.unget();
		currNode->right = new Node();
		deserializeUtil(currNode->right, ifile);
	}
	// (10(9...)(11...)')'
	ifile.get(bracket);
}

void Tree::destroy(Node* currNode) {
	if (currNode) {
		destroy(currNode->left);
		destroy(currNode->right);
		delete currNode;
	}
}