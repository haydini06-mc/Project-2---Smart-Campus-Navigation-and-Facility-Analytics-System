
#ifndef MENU_H
#define MENU_H

#include "FacilityDatabase.h"
#include "CampusGraph.h"
#include "DepartmentTree.h"

void handleViewFacilities(const FacilityDatabase& db);
void handleSearchFacilityById(const FacilityDatabase& db);
void handleAddDepartment(DepartmentTree& tree);
void handleSearchDepartment(const DepartmentTree& tree);
void handleBfsReachable(const CampusGraph& graph);

void runMenu(
    FacilityDatabase& db,
    CampusGraph& graph,
    DepartmentTree& tree
);

#endif


