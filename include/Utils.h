/* Trim(spaces, tabs, \r), uppercase conversion, case-insensitive compare, 
 * split on | , comment / blank line check. */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

std::string trim(const std::string& str);
std::string toUpperCase(const std::string& str);
bool equalsIgnoreCase(const std::string& str1, const std::string& str2);
std::vector<std::string> split(const std::string& str, char delimiter);
bool isCommentOrBlank(const std::string& line);

std::string normalizeId(const std::string& id);
bool isValidFacilityId(const std::string& normalizedId);

#endif // UTILS_H
