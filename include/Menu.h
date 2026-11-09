
#ifndef MENU_H
#define MENU_H

#include "FacilityDatabase.h"
#include "CampusGraph.h"
#include "DepartmentTree.h"

void runMenu(FacilityDatabase& db, CampusGraph& graph, DepartmentTree& tree);

void handleAddDepartment(DepartmentTree& tree);
void handleSearchDepartment(const DepartmentTree& tree);
void handleBfsReachable(const CampusGraph& graph);

void runMenu(
    FacilityDatabase& db,
    CampusGraph& graph,
    DepartmentTree& tree
);

#endif


