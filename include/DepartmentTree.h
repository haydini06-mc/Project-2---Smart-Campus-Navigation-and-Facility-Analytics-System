// Purpose: general tree for the academic department hierarchy
//          (loading, search, traversals, statistics).
// Author: Member C
#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

#include <string>
#include <vector>
#include "DepartmentNode.h"

struct DepartmentStats {
    int total;
    int leaves;
    int height;   // -1 when the tree is empty (display as N/A)
};

class DepartmentTree {
public:
    DepartmentTree();
    ~DepartmentTree();                                   // frees every node (NFR-11)
    DepartmentTree(const DepartmentTree&) = delete;
    DepartmentTree& operator=(const DepartmentTree&) = delete;

    bool isEmpty() const;
    int size() const;

    // TREE-2: load departments.txt (prints warnings + LOAD-4 summary line).
    void loadFromFile(const std::string& path, const std::string& displayName);

    // TREE-3: add the root (tree must be empty) or a child of an existing parent.
    // On failure returns false and fills 'error'; the tree is left unchanged.
    bool addRoot(const std::string& name, std::string& error);
    bool addChild(const std::string& name, const std::string& parentName, std::string& error);

    // TREE-4: case-insensitive search; nullptr if not found.
    DepartmentNode* find(const std::string& name) const;
    void displaySearchResult(const std::string& name) const;

    // TREE-5: preorder, one per line, 4 spaces of indent per depth.
    void displayHierarchy() const;

    // TREE-6 / TREE-7: traversal sequences (names only, no indentation).
    std::vector<std::string> preorder() const;
    std::vector<std::string> postorder() const;
    std::vector<std::string> levelOrder() const;   // uses std::queue
    void printSequence(const std::string& title, const std::vector<std::string>& seq) const;

    // TREE-8: totals, leaves, height.
    DepartmentStats computeStats() const;
    void displayStats() const;

private:
    DepartmentNode* root;
    int count;

    int depthOf(const DepartmentNode* node) const;
    void printSubtree(const DepartmentNode* node, int depth) const;
    void preorderHelper(const DepartmentNode* node, std::vector<std::string>& out) const;
    void postorderHelper(const DepartmentNode* node, std::vector<std::string>& out) const;
};

#endif
