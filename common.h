//
// Created by tillw on 05/12/2024.
//

#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

template <typename Out>
inline void split(const std::string &s, char delim, Out result) {
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		*result++ = item;
	}
}

inline std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

#endif //COMMON_H
