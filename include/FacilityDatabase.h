
#ifndef FACILITY_DATABASE_H
#define FACILITY_DATABASE_H

#include "Facility.h"
#include "HashTable.h"
#include <string>
#include <vector>
#include <cstddef>

class FacilityDatabase {
private:
    std::vector<Facility> facilities;
    HashTable idIndex;
    static void printFacility(const Facility& facility);

public:
    bool addFacility(const Facility& facility, std::string& error);
    const Facility* findById(const std::string& id) const;
    std::vector<const Facility*> findByName(const std::string& name) const;
    std::vector<const Facility*> findByCategory(const std::string& category) const;
    void displayAll() const;
    void displayIdSearch(const std::string& id) const;
    void displayNameSearch(const std::string& name) const;
    void displayCategorySearch(const std::string& category) const;
    void displayCategoryReport() const;
    std::size_t size() const;
    std::size_t hashCapacity() const;
    std::size_t hashEntries() const;
    std::size_t hashCollisions() const;
};

#endif

