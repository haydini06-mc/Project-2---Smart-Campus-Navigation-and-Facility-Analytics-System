/* One loader function per file. Opens the file, reads with getline,
 * applies the validation rules, prints warnings, and returns accepted/rejected counts. */

#ifndef FILELOADER_H
#define FILELOADER_H

#include "CampusGraph.h"

#include <string>
#include <fstream>

struct LoadResult {
    int accepted;
    int rejected;
};

LoadResult loadBuildings(const std::string& filename, CampusGraph& graph);
LoadResult loadConnections(const std::string& filename, CampusGraph& graph);

LoadResult loadFacilities();

LoadResult loadDepartments();

void printLoadSummary(const std::string& filename, const LoadResult& result);
void printWarning(const std::string& filename, int lineNumber, const std::string& message);
bool openDataFile(const std::string& filename, std::ifstream& fileStream);

#endif // FILELOADER_H