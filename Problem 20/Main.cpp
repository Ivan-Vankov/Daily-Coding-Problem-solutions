// Daily Coding Problem #20

#include <cstdlib>
#include <stdio.h>

class Node {
public:
	int val;
	Node* next;
	Node(int newVal, Node* newNext = nullptr) : val(newVal), next(newNext) {}
};

int listLength(const Node* list) {
	if (!list) { return 0; }
	const Node* iter = list;
	int cnt = 1;
	while (iter->next) {
		++cnt;
		iter = iter->next;
	}
	return cnt;
}

// the function iterates the list until its size is equal to newSize
void shortenList(const Node*& list, int oldSize, int newSize) {
	while (oldSize != newSize) {
		list = list->next;
		--oldSize;
	}
}

int listsIntersection(const Node*& list1, const Node*& list2) {
	if (!list1 || !list2) { return -1; }
	int list1Size = listLength(list1);
	int list2Size = listLength(list2);

	const Node* list1Iter = list1;
	const Node* list2Iter = list2;

	if (list1Size < list2Size) {
		shortenList(list2Iter, list2Size, list1Size);
	} else {
		shortenList(list1Iter, list1Size, list2Size);
	}

	while (list1Iter) {
		if (list1Iter == list2Iter) {
			return list1Iter->val;
		}
		list1Iter = list1Iter->next;
		list2Iter = list2Iter->next;
	}
	return -1;
}

int main() {

	Node* intersection = new Node(8, new Node(10));
	const Node* list1 = new Node( 3, new Node(7, intersection));
	const Node* list2 = new Node(99, new Node(1, intersection));

	int intersectionValue = listsIntersection(list1, list2);
	if (intersectionValue == -1) {
		printf("No intersection found\n");
	}
	else {
		printf("Intersection at: %d\n", intersectionValue);
	}

	system("pause");
}