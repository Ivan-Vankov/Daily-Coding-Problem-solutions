#include "XORList.h"
#include <stdio.h>

XORList::Node::Node(int data, Node* prev, Node* right) {
	this->data = data;
	updateNeighbours(prev, right);
}

void XORList::Node::updateNeighbours(Node* prev, Node* right) {
	xorptr = (Node*)((int)prev ^ (int)right);
}

XORList::ForwardIterator::ForwardIterator(Node* start) {
	prev = nullptr;
	curr = start;
}

XORList::ForwardIterator::ForwardIterator(const ForwardIterator& other) {
	prev = nullptr;
	curr = other.curr;
}

XORList::ForwardIterator& XORList::ForwardIterator::operator++() {
	Node* next = (Node*)((int)curr->xorptr ^ (int)prev);
	prev = curr;
	curr = next;
	return *this;
}

XORList::ForwardIterator XORList::ForwardIterator::operator++(int) {
	ForwardIterator temp(*this);
	++(*this);
	return temp;
}

XORList::ForwardIterator::operator bool() const {
	return curr != nullptr;
}

XORList::BackwardIterator::BackwardIterator(Node* end) {
	prev = nullptr;
	curr = end;
}

XORList::BackwardIterator::BackwardIterator(const BackwardIterator& other) {
	curr = other.curr;
	prev = nullptr;
}

XORList::BackwardIterator& XORList::BackwardIterator::operator++() {
	Node* next = (Node*)((int)curr->xorptr ^ (int)prev);
	prev = curr;
	curr = next;
	return *this;
}

XORList::BackwardIterator XORList::BackwardIterator::operator++(int) {
	BackwardIterator temp(*this);
	++(*this);
	return temp;
}

XORList::BackwardIterator::operator bool() const {
	return curr != nullptr;
}

XORList::XORList():first(nullptr), last(nullptr){}


XORList::~XORList(){
	while (!empty()) {
		popBack();
	}
}

void XORList::pushBack(int data) {
	Node* newNode = new Node(data, last, nullptr);
	if (last) {
		// last->xorptr acts as the last node's prev 
		// because it is an xor of the prev and 0(aka just prev)
		last->updateNeighbours(last->xorptr, newNode);
	}
	if (!first) {
		first = newNode;
	}
	last = newNode;
}

void XORList::popBack() {
	if (!last) { return; }
	// Same logic as with pushBack
	Node* prev = last->xorptr;
	if (prev) {
		Node* prevPrev = (Node*)((int)prev->xorptr ^ (int)last);
		prev->updateNeighbours(prevPrev, nullptr);
	}
	delete last;
	last = prev;
	if (!last) {
		first = nullptr;
	}
}

bool XORList::empty(){
	return first == nullptr;
}

void XORList::printList() {
	ForwardIterator fIterator(first);
	while (fIterator) {
		printf("%i ", fIterator.curr->data);
		++fIterator;
	}
	printf("\n");
}