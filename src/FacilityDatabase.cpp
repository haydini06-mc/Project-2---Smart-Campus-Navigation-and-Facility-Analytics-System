
#include "FacilityDatabase.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

bool FacilityDatabase::addFacility(const Facility& facility, std::string& error) {
    Facility clean = facility;
    clean.id = normalizeId(facility.id);
    clean.name = trim(facility.name);
    clean.building = trim(facility.building);
    clean.category = trim(facility.category);

    if (!isValidFacilityId(clean.id)) {
        error = "invalid facility ID (expected F plus three digits)";
        return false;
    }
    if (clean.name.empty() || clean.building.empty() || clean.category.empty()) {
        error = "empty required field";
        return false;
    }
    std::size_t existingIndex = 0;
    if (idIndex.find(clean.id, existingIndex)) {
        error = "duplicate facility ID '" + clean.id + "'";
        return false;
    }
    std::size_t newIndex = facilities.size();
    facilities.push_back(clean);
    if (!idIndex.insert(clean.id, newIndex)) {
        facilities.pop_back();
        error = "could not insert facility ID";
        return false;
    }
    return true;
}

const Facility* FacilityDatabase::findById(const std::string& id) const {
    std::size_t index = 0;
    if (!idIndex.find(id, index)) return nullptr;
    return &facilities[index];
}

std::vector<const Facility*> FacilityDatabase::findByName(const std::string& name) const {
    std::vector<const Facility*> matches;
    std::string target = trim(name);
    for (const Facility& facility : facilities) {
        if (equalsIgnoreCase(facility.name, target)) matches.push_back(&facility);
    }
    return matches;
}

std::vector<const Facility*> FacilityDatabase::findByCategory(const std::string& category) const {
    std::vector<const Facility*> matches;
    std::string target = trim(category);
    for (const Facility& facility : facilities) {
        if (equalsIgnoreCase(facility.category, target)) matches.push_back(&facility);
    }
    return matches;
}

void FacilityDatabase::printFacility(const Facility& facility) {
    std::cout << facility.id << " | " << facility.name << " | "
              << facility.building << " | " << facility.category << "\n";
}

void FacilityDatabase::displayAll() const {
    if (facilities.empty()) {
        std::cout << "No facilities are loaded.\n";
    } else {
        for (const Facility& facility : facilities) printFacility(facility);
    }
    std::cout << "Total facilities: " << facilities.size() << "\n";
}

void FacilityDatabase::displayIdSearch(const std::string& id) const {
    std::string key = normalizeId(id);
    if (!isValidFacilityId(key)) {
        std::cout << "Invalid facility ID format. Use F followed by exactly three digits.\n";
        return;
    }
    const Facility* facility = findById(key);
    if (!facility) {
        std::cout << "Facility " << key << " not found.\n";
        return;
    }
    std::cout << "Facility found:\n";
    printFacility(*facility);
}

void FacilityDatabase::displayNameSearch(const std::string& name) const {
    if (trim(name).empty()) {
        std::cout << "Error: name cannot be blank.\n";
        return;
    }
    auto matches = findByName(name);
    if (matches.empty()) std::cout << "No facilities found with that name.\n";
    for (const Facility* facility : matches) printFacility(*facility);
    std::cout << "Matches: " << matches.size() << "\n";
}

void FacilityDatabase::displayCategorySearch(const std::string& category) const {
    if (trim(category).empty()) {
        std::cout << "Error: category cannot be blank.\n";
        return;
    }
    auto matches = findByCategory(category);
    if (matches.empty()) std::cout << "No facilities found in that category.\n";
    for (const Facility* facility : matches) printFacility(*facility);
    std::cout << "Matches: " << matches.size() << "\n";
}

void FacilityDatabase::displayCategoryReport() const {
    if (facilities.empty()) {
        std::cout << "No facilities are available.\nTotal: 0\n";
        return;
    }
    struct CategoryCount {
        std::string name;
        std::size_t count;
    };
    std::vector<CategoryCount> categories;
    for (const Facility& facility : facilities) {
        bool found = false;
        for (CategoryCount& category : categories) {
            if (equalsIgnoreCase(category.name, facility.category)) {
                ++category.count;
                found = true;
                break;
            }
        }
        if (!found) categories.push_back({facility.category, 1});
    }
    std::cout << "\n===== Facility Category Report =====\n";
    std::cout << std::left << std::setw(28) << "Category"
              << std::right << std::setw(10) << "Count"
              << std::setw(14) << "Percentage" << "\n";
    std::cout << std::fixed << std::setprecision(1);
    for (const CategoryCount& category : categories) {
        double percentage = 100.0 * static_cast<double>(category.count) /
                            static_cast<double>(facilities.size());
        std::cout << std::left << std::setw(28) << category.name
                  << std::right << std::setw(10) << category.count
                  << std::setw(13) << percentage << "%\n";
    }
    std::cout << "Total facilities: " << facilities.size() << "\n";
}

std::size_t FacilityDatabase::size() const { return facilities.size(); }
std::size_t FacilityDatabase::hashCapacity() const { return idIndex.capacity(); }
std::size_t FacilityDatabase::hashEntries() const { return idIndex.size(); }
std::size_t FacilityDatabase::hashCollisions() const { return idIndex.collisions(); }
