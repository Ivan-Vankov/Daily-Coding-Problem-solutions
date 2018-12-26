#include "NumberOfEncodings.h"
#include <string>

// If the message is 263 and the index is 2
// function checks if 63 is less than 26(encodable)
bool NumberOfEncodings::isPairAtIndexEncodable(const std::string& message, int index) {
	// Index edge cases
	if (index < 0) { return false; }
	if (index == 0 && message.length()) { return true; }
	if (index >(int)message.length()) { return false; }

	if (message[index - 1] <= '1' ||
		(message[index - 1] == '2' && message[index] <= '6')) {
		return true;
	}
	else {
		return false;
	}
}

int NumberOfEncodings::numOfEncodings(const std::string& message) {
	int len = message.length();
	// Message length edge cases
	if (!len) { return 0; }
	if (len == 1) { return 1; }
	if (len == 2) {
		if (isPairAtIndexEncodable(message, 1)) {
			return 2;
		}
		else {
			return 1;
		}
	}

	// Result table
	int table[3] = { 1,1,0 };
	// If 11 is the message then it can be encoded in 2 ways (aa,k)
	// If 63 is the message then it can be encoded in only 1 way (fc)
	if (isPairAtIndexEncodable(message, 1)) {
		++table[1];
	}

	// Main loop
	int index = 2;
	while (index < len) {
		// Fill table[2]
		table[2] = table[1];
		if (isPairAtIndexEncodable(message, index++)) {
			table[2] += table[0];
		}

		// Shift the table to the left once for the next iteration
		table[0] = table[1];
		table[1] = table[2];
	}

	return table[2];
}