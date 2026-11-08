/* Menu display, safe integer input(clear stream, discard line),
 * name prompts using getline, dispatch to modules. */
#include "DepartmentTree.h"

// Department menu handlers (Member C)
void handleAddDepartment(DepartmentTree& tree);
void handleSearchDepartment(const DepartmentTree& tree);
