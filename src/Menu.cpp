// Reads a full line (spaces allowed) after printing a prompt. Returns trimmed text.
static std::string promptLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return trim(line);
}

void handleAddDepartment(DepartmentTree& tree) {
    std::string error;
    std::string name = promptLine("Enter new department name: ");
    if (name.empty()) { std::cout << "Error: name cannot be blank.\n"; return; }

    if (tree.isEmpty()) {
        if (tree.addRoot(name, error)) std::cout << "Added root department '" << name << "'.\n";
        else std::cout << "Error: " << error << ".\n";
        return;
    }
    std::string parent = promptLine("Enter parent department name: ");
    if (parent.empty()) { std::cout << "Error: name cannot be blank.\n"; return; }

    if (tree.addChild(name, parent, error)) std::cout << "Added department '" << name << "'.\n";
    else std::cout << "Error: " << error << ". Tree unchanged.\n";
}

void handleSearchDepartment(const DepartmentTree& tree) {
    std::string name = promptLine("Enter department name: ");
    if (name.empty()) { std::cout << "Error: name cannot be blank.\n"; return; }
    if (tree.isEmpty()) { std::cout << "The department tree is empty.\n"; return; }
    tree.displaySearchResult(name);
}
