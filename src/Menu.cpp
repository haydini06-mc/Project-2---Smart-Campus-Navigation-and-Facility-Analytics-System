// Purpose: menu display, safe input, and dispatch to the data-structure modules.
#include "Menu.h"
#include "Utils.h"

#include <iostream>
#include <string>

// Reads a full line (spaces allowed). Returns trimmed text.
static std::string promptLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return trim(line);
}

// Safe integer input: reads the whole line, so letters or blanks can never
// leave the stream in a bad state (UI-4). Returns false if not a valid integer.
static bool readInt(const std::string& prompt, int& value) {
    std::string line = promptLine(prompt);
    if (line.empty()) return false;
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
              << " 3. Search facility by name\n"
              << " 4. Search facility by category\n"
              << " 5. View campus graph\n"
              << " 6. Display graph counts and degrees\n"
              << " 7. Find reachable buildings (BFS)\n"
              << " 8. Find shortest path (BFS)\n"
              << " 9. Add department\n"
              << "10. Search department\n"
              << "11. Display department hierarchy\n"
              << "12. Preorder traversal\n"
              << "13. Postorder traversal\n"
              << "14. Level-order traversal\n"
              << "15. Department statistics\n"
              << "16. Facility category report\n"
              << "17. Graph connectivity report\n"
              << "18. Exit\n";
}

// ---- Department handlers (Member C) ----
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

// ---- Graph handlers (Member B) ----
// Prompts for a start building and prints reachable buildings (BFS).
// A blank name is rejected here; an unknown name is reported by bfsReachable.
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
void runMenu(FacilityDatabase& db, CampusGraph& graph, DepartmentTree& tree) {
    while (true) {
        printMenu();
        int choice = 0;
        if (!readInt("Enter choice: ", choice)) {
            if (std::cin.eof()) return;          // end of scripted input: stop cleanly
            std::cout << "Error: please enter a number from 1 to 18.\n";
            continue;
        }

        switch (choice) {
            case 1:  /* teammate: db.displayAll(); */ break;
            case 2:  /* teammate: ID search */ break;
            case 3:  /* teammate: name search */ break; // Member A, final project
            case 4:  /* teammate: category search */ break; // Member A, final project
            case 5:  graph.display(); break;
            case 6:  graph.displayCountsAndDegrees(); break;
            case 7:  handleBfsReachable(graph); break;
			case 8:  /* teammate: shortest path */ break; // Member B, final project

            case 9:  handleAddDepartment(tree); break;
            case 10: handleSearchDepartment(tree); break;
            case 11: tree.displayHierarchy(); break;
            case 12: tree.printSequence("Preorder traversal", tree.preorder()); break;
            case 13: tree.printSequence("Postorder traversal", tree.postorder()); break; // Member C, final project
            case 14: tree.printSequence("Level-order traversal", tree.levelOrder()); break; // Member C, final project
            case 15: tree.displayStats(); break; // Member C, final project

            case 16: /* teammate: category report */ break; // Member A, final project
            case 17: /* teammate: connectivity report */ break; // Member B, final project
            case 18: std::cout << "Goodbye.\n"; return;
            default: std::cout << "Error: please enter a number from 1 to 18.\n";
        }
    }
}
