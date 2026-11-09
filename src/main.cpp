
#include <iostream>
#include <string>
#include "CampusGraph.h"
#include "DepartmentTree.h"
#include "FacilityDatabase.h"
#include "FileLoader.h"
#include "Menu.h"

int main(int argc, char* argv[]) {
    std::string dataDirectory = "data";
    if (argc > 1) dataDirectory = argv[1];
    if (!dataDirectory.empty() && dataDirectory.back() != '/' && dataDirectory.back() != '\\') {
        dataDirectory += "/";
    }
    CampusGraph graph;
    DepartmentTree tree;
    FacilityDatabase database;
    loadBuildings(dataDirectory + "buildings.txt", graph);
    loadConnections(dataDirectory + "connections.txt", graph);
    // loadFacilities(dataDirectory + "facilities.txt", database, graph);
    loadDepartments(dataDirectory + "departments.txt", tree);
    runMenu(database, graph, tree);
    return 0;
}
