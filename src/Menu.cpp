
#include "Menu.h"
#include "Utils.h"

#include <iostream>
#include <string>

static std::string promptLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return trim(line);
}

static bool readInt(const std::string& prompt, int& value) {
    std::string line = promptLine(prompt);

    if (line.empty()) {
        return false;
    }

    try {
        size_t pos = 0;
        value = std::stoi(line, &pos);
        return pos == line.size();
    } catch (...) {
        return false;
    }
}

static void printMenu() {
    std::cout << "\n===== Smart Campus Menu =====\n"
              << " 1. View all facilities\n"
              << " 2. Search facility by ID\n"
              << " 3. View campus graph\n"
              << " 4. Display graph counts and degrees\n"
              << " 5. Find reachable buildings (BFS)\n"
              << " 6. Add department\n"
              << " 7. Search department\n"
              << " 8. Display department hierarchy\n"
              << " 9. Run preorder traversal\n"
              << "10. Exit\n";
}

void handleViewFacilities(const FacilityDatabase& db) {
    db.displayAll();
}

void handleSearchFacilityById(const FacilityDatabase& db) {
    std::string id = promptLine("Enter facility ID: ");

    if (id.empty()) {
        std::cout << "Error: ID cannot be blank.\n";
        return;
    }

    db.displayIdSearch(id);
}

void handleAddDepartment(DepartmentTree& tree) {
    std::string error;
    std::string name = promptLine("Enter new department name: ");

    if (name.empty()) {
        std::cout << "Error: name cannot be blank.\n";
        return;
    }

    if (tree.isEmpty()) {
        if (tree.addRoot(name, error)) {
            std::cout << "Added root department '" << name << "'.\n";
        } else {
            std::cout << "Error: " << error << ".\n";
        }
        return;
    }

    std::string parent = promptLine("Enter parent department name: ");

    if (parent.empty()) {
        std::cout << "Error: name cannot be blank.\n";
        return;
    }

    if (tree.addChild(name, parent, error)) {
        std::cout << "Added department '" << name << "'.\n";
    } else {
        std::cout << "Error: " << error << ". Tree unchanged.\n";
    }
}

void handleSearchDepartment(const DepartmentTree& tree) {
    std::string name = promptLine("Enter department name: ");

    if (name.empty()) {
        std::cout << "Error: name cannot be blank.\n";
        return;
    }

    if (tree.isEmpty()) {
        std::cout << "The department tree is empty.\n";
        return;
    }

    tree.displaySearchResult(name);
}

void handleBfsReachable(const CampusGraph& graph) {
    if (graph.buildingCount() == 0) {
        std::cout << "No buildings are loaded.\n";
        return;
    }

    std::string name = promptLine("Enter starting building: ");

    if (name.empty()) {
        std::cout << "Error: name cannot be blank.\n";
        return;
    }

    graph.bfsReachable(name);
}

// ---- Main menu loop ----
void runMenu(/* FacilityDatabase& db, */CampusGraph& graph, DepartmentTree& tree) {
    while (true) {
        printMenu();

        int choice = 0;

        if (!readInt("Enter choice: ", choice)) {
            if (std::cin.eof()) {
                return;
            }

            std::cout << "Error: please enter a number from 1 to 10.\n";
            continue;
        }

        switch (choice) {
            case 1:
                handleViewFacilities(db);
                break;

            case 2:
                handleSearchFacilityById(db);
                break;

            case 3:
                graph.display();
                break;

            case 4:
                graph.displayCountsAndDegrees();
                break;

            case 5:
                handleBfsReachable(graph);
                break;

            case 6:
                handleAddDepartment(tree);
                break;

            case 7:
                handleSearchDepartment(tree);
                break;

            case 8:
                tree.displayHierarchy();
                break;

            case 9:
                tree.printSequence(
                    "Preorder traversal",
                    tree.preorder()
                );
                break;

            case 10:
                std::cout << "Goodbye.\n";
                return;

            default:
                std::cout << "Error: please enter a number from 1 to 10.\n";
                break;
        }
    }
}

