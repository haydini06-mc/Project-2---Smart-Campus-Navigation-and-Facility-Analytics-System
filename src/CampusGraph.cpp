#include "CampusGraph.h"
#include "Utils.h"

#include <iostream>
#include <queue>

CampusGraph::CampusGraph() : connectionCount(0) {}

std::string CampusGraph::addBuilding(const std::string& buildingName) {
	if (findBuilding(buildingName) != -1) {
		return "Error: Building already exists.";
	}
	buildings.push_back(buildingName);
	adjacencyList.push_back(std::vector<int>());
	return "Building added successfully.";
}

int CampusGraph::findBuilding(const std::string& buildingName) const {
	for (size_t i = 0; i < buildings.size(); ++i) {
		if (buildings[i] == buildingName) {
			return static_cast<int>(i);
		}
	}
	return -1; // Building not found
}