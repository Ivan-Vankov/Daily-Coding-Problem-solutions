// Daily Coding Problem #21

#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>

int minRoomsRequired(const std::vector<std::pair<int, int>>& OGTimeIntervals) {
	std::vector<std::pair<int, int>> timeIntervals = OGTimeIntervals;
	std::sort(timeIntervals.begin(), timeIntervals.end(), 
		[](const std::pair<int, int>& timeInterval1, 
			const std::pair<int, int>& timeInterval2) {
			return timeInterval1.first < timeInterval2.first;
		});

	// With greater so that is becomes a min priority queue
	std::priority_queue<int, std::vector<int>, std::greater<int>> compatibleRooms;
	// So that compatibleRooms.top() returns a valid int
	compatibleRooms.push(timeIntervals[0].second);

	for (int i = 1; i < (int)timeIntervals.size(); ++i) {
		// If the earliest finishing intereval finishes before the current one
		if (compatibleRooms.top() <= timeIntervals[i].first) {
			compatibleRooms.pop();
			compatibleRooms.push(timeIntervals[i].second);
		}
		else {
			compatibleRooms.push(timeIntervals[i].second);
		}
	}
	return (int)compatibleRooms.size();
}

int main() {

	std::vector<std::pair<int, int>> timeIntervals = {
		std::make_pair(30 , 75),
		std::make_pair( 0 , 50),
		std::make_pair(60 , 100),
		std::make_pair(40 , 70)
	};

	printf("%d\n", minRoomsRequired(timeIntervals));

	system("pause");
}