#pragma once

#include <string>

class NumberOfEncodings {
public:
	static int numOfEncodings(const std::string& message);
private:
	static bool isPairAtIndexEncodable(const std::string& message, int index);
};