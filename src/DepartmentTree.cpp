// Purpose: implementation of the department general tree.
// Author: Member C
#include "DepartmentTree.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <queue>

DepartmentTree::DepartmentTree() : root(nullptr), count(0) {}

// Frees all nodes iteratively (no deep recursion on long chains).
DepartmentTree::~DepartmentTree() {
    std::vector<DepartmentNode*> stack;
    if (root) stack.push_back(root);
    while (!stack.empty()) {
        DepartmentNode* n = stack.back();
        stack.pop_back();
        for (DepartmentNode* c : n->children) stack.push_back(c);
        delete n;
    }
    root = nullptr;
    count = 0;
}

bool DepartmentTree::isEmpty() const { return root == nullptr; }
int DepartmentTree::size() const { return count; }

// Case-insensitive lookup using an iterative scan of the tree.
DepartmentNode* DepartmentTree::find(const std::string& name) const {
    std::string target = trim(name);
    if (!root || target.empty()) return nullptr;
    std::vector<DepartmentNode*> stack;
    stack.push_back(root);
    while (!stack.empty()) {
        DepartmentNode* n = stack.back();
        stack.pop_back();
        if (equalsIgnoreCase(n->name, target)) return n;
        for (DepartmentNode* c : n->children) stack.push_back(c);
    }
    return nullptr;
}

bool DepartmentTree::addRoot(const std::string& name, std::string& error) {
    std::string clean = trim(name);
    if (clean.empty()) { error = "department name is empty"; return false; }
    if (root != nullptr) { error = "tree already has a root"; return false; }
    root = new DepartmentNode(clean);
    count = 1;
    return true;
}

bool DepartmentTree::addChild(const std::string& name, const std::string& parentName,
                              std::string& error) {
    std::string clean = trim(name);
    std::string parentClean = trim(parentName);
    if (clean.empty()) { error = "department name is empty"; return false; }
    if (parentClean.empty()) { error = "parent name is empty"; return false; }
    if (root == nullptr) { error = "tree is empty; add the root first"; return false; }

    DepartmentNode* parent = find(parentClean);
    if (!parent) { error = "unknown parent '" + parentClean + "'"; return false; }
    if (find(clean)) { error = "duplicate department name '" + clean + "'"; return false; }

    parent->children.push_back(new DepartmentNode(clean, parent));
    count++;
    return true;
}

// TREE-2: validation order = field count, empty fields, parent reference, duplicate.
void DepartmentTree::loadFromFile(const std::string& path, const std::string& displayName) {
    int accepted = 0, rejected = 0;
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cout << "Error: cannot open file " << displayName << " (" << path
                  << "); treating it as empty.\n";
    } else {
        std::string line;
        int lineNo = 0;
        while (std::getline(in, line)) {
            lineNo++;
            if (isCommentOrBlank(line)) continue;

            std::vector<std::string> f = split(line, '|');
            std::string error;
            bool ok = false;

            if (f.size() != 2) {
                error = "wrong field count (expected 2, found " + std::to_string(f.size()) + ")";
            } else {
                std::string name = trim(f[0]);
                std::string parent = trim(f[1]);
                if (name.empty() || parent.empty()) {
                    error = "empty required field";
                } else if (root == nullptr) {
                    // First valid record must be the root with parent NONE.
                    if (!equalsIgnoreCase(parent, "NONE")) {
                        error = "first department must be the root with parent NONE";
                    } else {
                        ok = addRoot(name, error);
                    }
                } else {
                    ok = addChild(name, parent, error);
                }
            }

            if (ok) {
                accepted++;
            } else {
                rejected++;
                std::cout << "Warning: " << displayName << ", line " << lineNo
                          << ": " << error << " - record rejected.\n";
            }
        }
    }
    std::cout << "Loaded " << displayName << ": " << accepted << " accepted, "
              << rejected << " rejected.\n";
}

int DepartmentTree::depthOf(const DepartmentNode* node) const {
    int d = 0;
    while (node && node->parent) { d++; node = node->parent; }
    return d;
}

// TREE-4
void DepartmentTree::displaySearchResult(const std::string& name) const {
    DepartmentNode* n = find(name);
    if (!n) {
        std::cout << "Department '" << trim(name) << "' not found.\n";
        return;
    }
    std::cout << "Department: " << n->name << "\n"
              << "Parent: " << (n->parent ? n->parent->name : "None") << "\n"
              << "Direct children: " << n->children.size() << "\n"
              << "Depth: " << depthOf(n) << "\n";
}

// TREE-5
void DepartmentTree::printSubtree(const DepartmentNode* node, int depth) const {
    std::cout << std::string(depth * 4, ' ') << node->name << "\n";
    for (const DepartmentNode* c : node->children) printSubtree(c, depth + 1);
}

void DepartmentTree::displayHierarchy() const {
    if (!root) { std::cout << "The department tree is empty.\n"; return; }
    printSubtree(root, 0);
}

// Traversals
void DepartmentTree::preorderHelper(const DepartmentNode* node,
                                    std::vector<std::string>& out) const {
    out.push_back(node->name);
    for (const DepartmentNode* c : node->children) preorderHelper(c, out);
}

void DepartmentTree::postorderHelper(const DepartmentNode* node,
                                     std::vector<std::string>& out) const {
    for (const DepartmentNode* c : node->children) postorderHelper(c, out);
    out.push_back(node->name);
}

std::vector<std::string> DepartmentTree::preorder() const {
    std::vector<std::string> out;
    if (root) preorderHelper(root, out);
    return out;
}

std::vector<std::string> DepartmentTree::postorder() const {
    std::vector<std::string> out;
    if (root) postorderHelper(root, out);
    return out;
}

// Level-order (BFS) with a queue; siblings visited in insertion order.
std::vector<std::string> DepartmentTree::levelOrder() const {
    std::vector<std::string> out;
    if (!root) return out;
    std::queue<const DepartmentNode*> q;
    q.push(root);
    while (!q.empty()) {
        const DepartmentNode* n = q.front();
        q.pop();
        out.push_back(n->name);
        for (const DepartmentNode* c : n->children) q.push(c);
    }
    return out;
}

void DepartmentTree::printSequence(const std::string& title,
                                   const std::vector<std::string>& seq) const {
    if (seq.empty()) { std::cout << "The department tree is empty.\n"; return; }
    std::cout << title << ":\n";
    for (size_t i = 0; i < seq.size(); i++) {
        if (i > 0) std::cout << " -> ";
        std::cout << seq[i];
    }
    std::cout << "\n";
}

// TREE-8: height = max depth (root-only = 0); empty tree reports -1 (N/A).
DepartmentStats DepartmentTree::computeStats() const {
    DepartmentStats s = {0, 0, -1};
    if (!root) return s;
    std::queue<std::pair<const DepartmentNode*, int>> q;
    q.push({root, 0});
    s.height = 0;
    while (!q.empty()) {
        std::pair<const DepartmentNode*, int> cur = q.front();
        q.pop();
        const DepartmentNode* n = cur.first;
        int d = cur.second;
        s.total++;
        if (n->children.empty()) s.leaves++;
        if (d > s.height) s.height = d;
        for (const DepartmentNode* c : n->children) q.push({c, d + 1});
    }
    return s;
}

void DepartmentTree::displayStats() const {
    DepartmentStats s = computeStats();
    if (s.total == 0) {
        std::cout << "The department tree is empty.\n";
    }
    std::cout << "Total departments: " << s.total << "\n"
              << "Leaf departments: " << s.leaves << "\n"
              << "Tree height: " << (s.height < 0 ? "N/A" : std::to_string(s.height)) << "\n";
}
