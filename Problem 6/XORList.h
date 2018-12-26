#pragma once
class XORList{
	class Node {
	public:
		Node(int data, Node* prev, Node* right);

		void updateNeighbours(Node* prev, Node* right);

		int data;
		Node* xorptr;
	};
public:
	class ForwardIterator {
		friend class XORList;
	public:
		ForwardIterator(Node* start);
		ForwardIterator(const ForwardIterator& other);

		ForwardIterator& operator++();
		ForwardIterator operator++(int);

		operator bool()const;
	private:
		Node* curr;
		Node* prev;
	};

	class BackwardIterator {
		friend class XORList;
	public:
		BackwardIterator(Node* end);
		BackwardIterator(const  BackwardIterator& other);

		BackwardIterator& operator++();
		BackwardIterator operator++(int);

		operator bool()const;
	private:
		Node* curr;
		Node* prev;
	};
public:
	XORList();
	~XORList();

	void pushBack(int data);
	void popBack();
	bool empty();

	void printList();
private:
	Node* first;
	Node* last;
};