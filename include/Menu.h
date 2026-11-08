/* Menu display, safe integer input(clear stream, discard line),
 * name prompts using getline, dispatch to modules. */
#ifndef MENU_H
#define MENU_H

#include "DepartmentTree.h"
// #include "FacilityDatabase.h"   // teammates' types
// #include "CampusGraph.h"

void runMenu(/* FacilityDatabase& db, CampusGraph& graph, */ DepartmentTree& tree);

void handleAddDepartment(DepartmentTree& tree);
void handleSearchDepartment(const DepartmentTree& tree);

#endif
