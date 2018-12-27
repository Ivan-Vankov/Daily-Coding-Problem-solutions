#include "Labirinth.h"
#include <unordered_set>
#include <queue>
#include <stdio.h>

Labirinth::Node::Node(const std::pair<int, int>& rowAndColl, const std::pair<int, int>& start,
	const std::pair<int, int>& end, bool traversable, Node* parent) {
	setBasicFields(rowAndColl.first, rowAndColl.second, traversable, parent);
	setGCostandHCost(start, end);
}

Labirinth::Node::Node(int row, int coll, const std::pair<int, int>& start,
	const std::pair<int, int>& end, bool traversable, Node* parent) {
	setBasicFields(row, coll, traversable, parent);
	setGCostandHCost(start, end);
}

Labirinth::Node::Node(int row, int coll, int gCost, int hCost,
	bool traversable, Node* parent) {
	setBasicFields(row, coll, traversable, parent);
	this->gCost = gCost;
	this->hCost = hCost;
}

Labirinth::Node::Node(const Node& other) {
	copyFrom(other);
}

Labirinth::Node& Labirinth::Node::operator=(const Node& other) {
	if (this != &other) {
		copyFrom(other);
	}
	return *this;
}

bool Labirinth::Node::operator==(const Node& other) const {
	return row == other.row && coll == other.coll;
}

bool Labirinth::Node::operator!=(const Node & other) const {
	return !(*this == other);
}

bool Labirinth::Node::operator<(const Node & other) const {
	return FCost() < other.FCost();
}

bool Labirinth::Node::operator<=(const Node & other) const {
	return !(*this > other);
}

bool Labirinth::Node::operator>(const Node& other) const {
	return FCost() > other.FCost();
}

bool Labirinth::Node::operator>=(const Node & other) const {
	return !(*this < other);
}

int Labirinth::Node::FCost() const { return gCost + hCost; }

std::pair<int, int> Labirinth::Node::position() const {
	return std::make_pair(row, coll);
}

void Labirinth::Node::updateCosts(const std::pair<int, int>& start, const std::pair<int, int>& end) {
	gCost = distance(std::make_pair(row, coll), start);
	hCost = distance(std::make_pair(row, coll), end);
}

int Labirinth::Node::distance(const std::pair<int, int>& from, const std::pair<int, int>& to) {
	return distance(from.first, from.second, to.first, to.second);
}

int Labirinth::Node::distance(int fromRow, int fromColl, int toRow, int toColl) {
	int yDiff = abs(fromRow - toRow);
	int xDiff = abs(fromColl - toColl);
	int lower, higher;
	if (xDiff < yDiff) {
		lower = xDiff;
		higher = yDiff;
	}
	else {
		lower = yDiff;
		higher = xDiff;
	}
	return lower * 14 + (higher - lower) * 10;
}

void Labirinth::Node::setGCostandHCost(const std::pair<int, int>& start, const std::pair<int, int>& end) {
	gCost = distance(row, coll, start.first, start.second);
	hCost = distance(row, coll, end.first, end.second);
}

void Labirinth::Node::copyFrom(const Node& other) {
	row = other.row;
	coll = other.coll;
	gCost = other.gCost;
	hCost = other.hCost;
}

void Labirinth::Node::setBasicFields(int row, int coll, bool traversable, Node* parent) {
	this->row = row;
	this->coll = coll;
	this->traversable = traversable;
	this->parent = parent;
}

Labirinth::Proxy::Proxy(int row, Labirinth* parent){
	this->row = row;
	this->parent = parent;
}

Labirinth::Node* Labirinth::Proxy::operator[](int coll){
	return parent->matrix[row][coll];
}

Labirinth::Labirinth(const std::vector<std::vector<bool>>& matrix, const std::pair<int, int>& start,
					 const std::pair<int, int>& end){
	this->matrix.resize((int)matrix.size());
	for (int i = 0; i < (int)matrix.size(); ++i) {
		this->matrix[i].resize((int)matrix[i].size());
		for (int j = 0; j < (int)matrix[i].size(); ++j) {
			this->matrix[i][j] = new Node(i, j, INT_MAX / 2, INT_MAX / 2, matrix[i][j], nullptr);
		}
	}

	this->start = start;
	this->end = end;
}

Labirinth::~Labirinth(){
	for (int i = 0; i < (int)matrix.size(); ++i) {
		for (int j = 0; j < (int)matrix[i].size(); ++j) {
			delete matrix[i][j];
		}
	}
}

void Labirinth::AstarPathfinding(){
	// Set of nodes to be evaluated
	std::priority_queue<Node*> open;
	std::unordered_set<Node*> open_set;

	// Set of nodes that have been evaluated
	// (map from row and coll to g and h costs)
	std::unordered_set<Node*> closed;

	updateNode(start);
	open.push(matrix[start.first][start.second]);
	open_set.insert(matrix[start.first][start.second]);
	Node* currNode = nullptr, *neighbour = nullptr;
	while (!open.empty()) {
		currNode = open.top();
		open.pop();
		open_set.erase(currNode);
		closed.insert(currNode);

		if (currNode->position() == end) { break; }

		// For each neighbour
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (i == 0 && j == 0) { continue; }
				// Neighbour validity check
				if (currNode->row  + i >= 0 && currNode->row  + i < Rows() &&
					currNode->coll + j >= 0 && currNode->coll + j < Colls()) {
					// If the neighbour is not traversable or is in closed
					neighbour = matrix[currNode->row + i][currNode->coll + j];
					if (!neighbour->traversable ||
						closed.find(neighbour) != closed.end()) {
						continue;
					}

					// If new path to neighbour is shorter or the neighbour is not in open_set
					if (Costs(*neighbour) < neighbour->FCost() ||
						open_set.find(neighbour) == open_set.end()) {
						neighbour->setGCostandHCost(start, end);
						neighbour->parent = currNode;
						if (open_set.find(neighbour) == open_set.end()) {
							open.push(neighbour);
							open_set.insert(neighbour);
						}
					}
				}
			}
		}
	}

	if (currNode->position() == end) {
		std::vector<Node*> path;
		do {
			path.push_back(currNode);
			currNode = currNode->parent;
		} while (currNode);
		int i = (int)path.size() - 1;
		for (; i > 0; --i) {
			printf("<%d, %d>, ", path[i]->row, path[i]->coll);
		}
		if (!i) {
			printf("<%d, %d>\n", path[i]->row, path[i]->coll);
		}
	}
	else {
		printf("No path found.\n");
	}
}

int Labirinth::Rows() const {
	return (int)matrix.size();
}

int Labirinth::Colls() const {
	return matrix.size() ? (int)matrix.back().size() : 0;
}

void Labirinth::updateNode(const std::pair<int, int> rowAndColl){
	updateNode(rowAndColl.first, rowAndColl.second);
}

void Labirinth::updateNode(int row, int coll){
	matrix[row][coll]->updateCosts(start, end);
}

const std::pair<int, int>& Labirinth::StartPos() const {
	return start;
}

const std::pair<int, int>& Labirinth::EndPos() const {
	return end;
}

int Labirinth::Costs(const Node& node) const {
	return Node::distance(start, node.position()) + 
		Node::distance(node.position(), end);
}

Labirinth::Proxy Labirinth::operator[](int row){
	return Proxy(row, this);
}
