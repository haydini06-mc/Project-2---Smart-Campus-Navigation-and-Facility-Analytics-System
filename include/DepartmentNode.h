// Node with name, parent pointer, vector of children
#ifndef DEPARTMENT_NODE_H
#define DEPARTMENT_NODE_H
 
#include <string>
#include <vector>
 
struct DepartmentNode {
    std::string name;                        // spelling from first accepted record
    DepartmentNode* parent;                  // nullptr for the root
    std::vector<DepartmentNode*> children;   // insertion order preserved
 
    explicit DepartmentNode(const std::string& n, DepartmentNode* p = nullptr)
        : name(n), parent(p) {}
};
 
#endif // DEPARTMENT_NODE_H
