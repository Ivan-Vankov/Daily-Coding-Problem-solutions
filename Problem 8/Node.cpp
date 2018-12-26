#include "Node.h"

Node::Node(int data, Node* left, Node* right) {
	this->data = data;
	this->left = left;
	this->right = right;
}

bool Node::isUnival() const {
	return isUnival(this);
}

int Node::numOfUnivalSubtrees() const {
	std::unordered_set<const Node*> univalTrees;
	numOfUnivalSubtreesUtil(this, univalTrees);
	return (int)univalTrees.size();
}

void Node::numOfUnivalSubtreesUtil(const Node* currNode,
	std::unordered_set<const Node*>& univalTrees) const {
	if (!currNode) { return; }
	numOfUnivalSubtreesUtil(currNode->left, univalTrees);
	numOfUnivalSubtreesUtil(currNode->right, univalTrees);
	if (isUnivalCheck(currNode, univalTrees)) {
		univalTrees.insert(currNode);
	}
}

bool Node::isUnivalCheck(const Node* currNode,
	std::unordered_set<const Node*>& univalTrees) const {
	return  (!currNode->left ||
		(currNode->left->data == currNode->data &&
			univalTrees.find(currNode->left) != univalTrees.end())) &&
			(!currNode->right ||
		(currNode->right->data == currNode->data &&
			univalTrees.find(currNode->right) != univalTrees.end()));
}

bool Node::isUnival(const Node* curr) const {
	if (!curr) {
		return false;
	}
	if ((!curr->left ||
		(curr->left->data == curr->data && isUnival(curr->left))) &&
		(!curr->right ||
		(curr->right->data == curr->data && isUnival(curr->right)))) {
		return true;
	}
	else {
		return false;
	}
}