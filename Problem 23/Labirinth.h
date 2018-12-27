#pragma once
#include <vector>

class Labirinth {
	friend class Proxy;
	class Node {
	public:
		Node(const std::pair<int, int>& rowAndColl, const std::pair<int, int>& start,
			const std::pair<int, int>& end, bool traversable, Node* parent);
		Node(int row, int coll, const std::pair<int, int>& start, const std::pair<int, int>& end,
			bool traversable, Node* parent);
		Node(int row, int coll, int gCost, int hCost,
			bool traversable, Node* parent);
		Node(const Node& other);
		Node& operator=(const Node& other);

		bool operator==(const Node& other)const;
		bool operator!=(const Node& other)const;

		bool operator<(const Node& other)const;
		bool operator<=(const Node& other)const;
		bool operator>(const Node& other)const;
		bool operator>=(const Node& other)const;

		int FCost() const;

		std::pair<int, int> position() const;

		void updateCosts(const std::pair<int, int>& start, const std::pair<int, int>& end);

		static int distance(const std::pair<int, int>& from, const std::pair<int, int>& to);
		static int distance(int fromRow, int fromColl, int toRow, int toColl);

		void setGCostandHCost(const std::pair<int, int>& start, const std::pair<int, int>& end);

		void copyFrom(const Node& other);

		void setBasicFields(int row, int coll, bool traversable, Node* parent);

		int row;
		int coll;
		// Distance from starting node
		int gCost;
		// Distance from end node
		int hCost;
		bool traversable;
		Node* parent;
	};
	class Proxy {
	public:
		Proxy(int, Labirinth*);
		Node* operator[](int);

		int row;
		Labirinth* parent;
	};
public:
	Labirinth(const std::vector<std::vector<bool>>& matrix, const std::pair<int, int>& start,
		const std::pair<int, int>& end);

	~Labirinth();

	void AstarPathfinding();

	int Rows()const;
	int Colls()const;

	void updateNode(const std::pair<int, int>);
	void updateNode(int row, int coll);

	const std::pair<int, int>& StartPos()const;
	const std::pair<int, int>& EndPos()const;

	int Costs(const Node&) const;

	Proxy operator[](int);
private:
	std::pair<int, int> start;
	std::pair<int, int> end;
	std::vector<std::vector<Node*>> matrix;
};