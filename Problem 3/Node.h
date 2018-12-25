#pragma once

class Node {
public:
	Node(int val = int(), Node* left = nullptr, Node* right = nullptr);
	Node(const Node& other);

private:
	void copyFrom(const Node* fromNode);

	void copyFromUtil(Node* toNode, const Node* fromNode);

public:
	int val;
	Node* left;
	Node* right;
};