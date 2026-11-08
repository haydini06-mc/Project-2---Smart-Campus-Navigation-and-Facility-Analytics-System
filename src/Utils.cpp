#include "Utils.h"

#include <cctype>

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

std::string toUpperCase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::toupper(c);
    }
    return result;
}

bool equalsIgnoreCase(const std::string& str1, const std::string& str2) {
	return toUpperCase(str1) == toUpperCase(str2);
}

std::vector<std::string> split(const std::string& str, char delimiter) {
	std::vector<std::string> strings;
	size_t start = 0;
	size_t end = str.find(delimiter);
	while (end != std::string::npos) {
		strings.push_back(str.substr(start, end - start));
		start = end + 1;
		end = str.find(delimiter, start);
	}
	strings.push_back(str.substr(start));
	return strings;
}

bool isCommentOrBlank(const std::string& line) {
	std::string trimmedLine = trim(line);
	return trimmedLine.empty() || trimmedLine[0] == '#';
}
std::string normalizeId(const std::string& id) {
    return toUpperCase(trim(id));
}
 

bool isValidFacilityId(const std::string& normalizedId) {
    if (normalizedId.size() != 4 || normalizedId[0] != 'F') {
        return false;
    }
    for (size_t i = 1; i < 4; i++) {
        if (!std::isdigit(static_cast<unsigned char>(normalizedId[i]))) {
            return false;
        }
    }
    return true;
}
