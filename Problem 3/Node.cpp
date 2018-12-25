#include "Node.h"

Node::Node(int val, Node* left, Node* right) {
	this->val = val;
	this->left = left;
	this->right = right;
}

Node::Node(const Node& other) {
	copyFrom(&other);
}

void Node::copyFrom(const Node* fromNode) {
	if (!fromNode) { return; }
	val = fromNode->val;
	copyFromUtil(this, fromNode);
}

void Node::copyFromUtil(Node* toNode, const Node* fromNode) {
	if (fromNode->left) {
		toNode->left = new Node(fromNode->left->val);
		copyFromUtil(toNode->left, fromNode->left);
	}
	if (fromNode->right) {
		toNode->right = new Node(fromNode->right->val);
		copyFromUtil(toNode->right, fromNode->right);
	}
}
