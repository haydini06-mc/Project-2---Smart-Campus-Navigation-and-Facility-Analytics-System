#include "Utils.h"
#include "FileLoader.h"
"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Opens a data file. If it cannot be opened, prints an error naming the file
// and returns false so the caller can treat the file as empty.
bool openDataFile(const std::string& filename, std::ifstream& fileStream) {
	fileStream.open(filename.c_str());
	if (!fileStream.is_open()) {
		std::cout << "Error: cannot open file " << filename
			<< "; treating it as empty.\n";
		return false;
	}
	return true;
}

// Prints one warning for a rejected record: filename, line number, reason.
void printWarning(const std::string& filename, int lineNumber, const std::string& message) {
	std::cout << "Warning: " << filename << ", line " << lineNumber
		<< ": " << message << " - record rejected.\n";
}

// Prints the one-line load summary shown after each file (LOAD-4).
void printLoadSummary(const std::string& filename, const LoadResult& result) {
	std::cout << "Loaded " << filename << ": " << result.accepted
		<< " accepted, " << result.rejected << " rejected.\n";
}

// Loads buildings.txt: one nonempty, unique (case-insensitive) name per line.
// Prints a warning for each rejected line and the summary line at the end.
LoadResult loadBuildings(const std::string& filename, CampusGraph& graph) {
	LoadResult result = { 0, 0 };

	std::ifstream in;
	if (!openDataFile(filename, in)) {
		printLoadSummary(filename, result);   // missing file = empty file
		return result;
	}

	std::string line;
	int lineNumber = 0;
	while (std::getline(in, line)) {
		lineNumber++;
		if (isCommentOrBlank(line)) continue;

		std::vector<std::string> fields = split(line, '|');
		std::string error;

		if (fields.size() != 1) {
			error = "wrong field count (expected 1, found " +
				std::to_string(fields.size()) + ")";
		}
		else if (graph.addBuilding(fields[0], error)) {
			result.accepted++;
			continue;
		}

		result.rejected++;
		printWarning(filename, lineNumber, error);
	}

	printLoadSummary(filename, result);
	return result;
}

// Loads connections.txt: BuildingA|BuildingB, both already accepted buildings.
// Rejects wrong field counts, empty fields, unknown buildings, self-connections,
// and duplicates (including reversed ones).
LoadResult loadConnections(const std::string& filename, CampusGraph& graph) {
	LoadResult result = { 0, 0 };

	std::ifstream in;
	if (!openDataFile(filename, in)) {
		printLoadSummary(filename, result);   // missing file = empty file
		return result;
	}

	std::string line;
	int lineNumber = 0;
	while (std::getline(in, line)) {
		lineNumber++;
		if (isCommentOrBlank(line)) continue;

		std::vector<std::string> fields = split(line, '|');
		std::string error;

		if (fields.size() != 2) {
			error = "wrong field count (expected 2, found " +
				std::to_string(fields.size()) + ")";
		}
		else if (graph.addConnection(fields[0], fields[1], error)) {
			result.accepted++;
			continue;
		}

		result.rejected++;
		printWarning(filename, lineNumber, error);
	}

	printLoadSummary(filename, result);
	return result;
}

// LoadResult loadFacilities() {
// 	LoadResult result = { 0, 0 };
//}

LoadResult loadDepartments(const std::string& filename, DepartmentTree& tree) {
	LoadResult result = { 0, 0 };

	std::ifstream in;
	if (!openDataFile(filename, in)) {
		printLoadSummary(filename, result);   // missing file = empty file
		return result;
	}

	std::string line;
	int lineNumber = 0;
	while (std::getline(in, line)) {
		lineNumber++;
		if (isCommentOrBlank(line)) continue;

		std::vector<std::string> fields = split(line, '|');
		std::string error;

		if (fields.size() != 2) {
			error = "wrong field count (expected 2, found " +
				std::to_string(fields.size()) + ")";
		}
		else {
			std::string name = trim(fields[0]);
			std::string parent = trim(fields[1]);

			if (name.empty() || parent.empty()) {
				error = "empty required field";
			}
			else if (tree.isEmpty()) {
				// first valid record must be the root with parent NONE
				if (!equalsIgnoreCase(parent, "NONE")) {
					error = "first department must be the root with parent NONE";
				}
				else if (tree.addRoot(name, error)) {
					result.accepted++;
					continue;
				}
			}
			else if (tree.addChild(name, parent, error)) {
				result.accepted++;
				continue;
			}
		}

		result.rejected++;
		printWarning(filename, lineNumber, error);
	}

	printLoadSummary(filename, result);
	return result;
}
