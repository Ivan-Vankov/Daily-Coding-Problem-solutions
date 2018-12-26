#pragma once

#include <unordered_set>

class Node {
public:
	Node(int data = int(), Node* left = nullptr, Node* right = nullptr);

	bool isUnival() const;

	int numOfUnivalSubtrees() const;

private:
	void numOfUnivalSubtreesUtil(const Node* currNode,
		std::unordered_set<const Node*>& univalTrees) const;

	bool isUnivalCheck(const Node* currNode,
		std::unordered_set<const Node*>& univalTrees) const;

	bool isUnival(const Node* curr) const;

	int data;
	Node* left;
	Node* right;
};