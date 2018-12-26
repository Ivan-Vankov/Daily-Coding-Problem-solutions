#include <cstdlib>
#include <unordered_map>
#include <list>
#include <string>
#include <stdio.h>

void getItinerary(std::unordered_map<std::string, std::string>& flights, 
					std::list<std::string>& itinerary) {
	if (!flights.size()) { return; }
	std::string lastStop = itinerary.back();
	for (auto flight : flights) {
		if (flight.first == lastStop) {
			itinerary.push_back(flight.second);
			std::unordered_map<std::string, std::string> buff(flights);
			buff.erase(flight.first);
			getItinerary(buff, itinerary);
			if (itinerary.size() > flights.size()) { return; }
			itinerary.pop_back();
		}
	}
}

std::list<std::string> getItinerary(const std::unordered_map<std::string, std::string>& flights, 
									const std::string& start) {
	std::unordered_map<std::string, std::string> flightsCopy(flights);
	std::list<std::string> itinerary;
	itinerary.push_back(start);
	getItinerary(flightsCopy, itinerary);
	return itinerary;
}

int main() {

	std::string start = "YUL";

	std::unordered_map<std::string, std::string> flights = {
		std::make_pair("HNL", "AKL"),
		std::make_pair("YUL", "ORD"),
		std::make_pair("ORD", "SFO"),
		std::make_pair("SFO", "HNL")
	};

	std::list<std::string> itinerary = getItinerary(flights, start);

	for (std::string stop : itinerary) {
		printf("%s ", stop.c_str());
	}
	printf("\n");

	system("pause");
}