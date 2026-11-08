/* Trim(spaces, tabs, \r), uppercase conversion, case-insensitive compare, 
 * split on | , comment / blank line check. */

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

static std::string trim(const std::string& str);
static std::string toUpperCase(const std::string& str);
static bool equalsIgnoreCase(const std::string& str1, const std::string& str2);
static std::vector<std::string> split(const std::string& str, char delimiter);
static bool isCommentOrBlank(const std::string& line);

std::string normalizeId(const std::string& id);
bool isValidFacilityId(const std::string& normalizedId);

#endif // UTILS_H
