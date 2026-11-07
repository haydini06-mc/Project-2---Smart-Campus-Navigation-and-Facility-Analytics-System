#include "CampusGraph.h"
#include "Utils.h"

#include <iostream>
#include <queue>

CampusGraph::CampusGraph() : connectionCount(0) {}

// 
std::string CampusGraph::addBuilding(const std::string& buildingName) {
	std::string trimmedName = trim(buildingName);
	if (findBuilding(trimmedName) != -1) {
		return "Error: Building already exists.";
	}
	buildings.push_back(trimmedName);
	adjacencyList.push_back(std::vector<int>());
	return "Building added successfully.";
}

// 
int CampusGraph::findBuilding(const std::string& buildingName) const {
	std::string trimmedName = trim(buildingName);
	for (size_t i = 0; i < buildings.size(); ++i) {
		if (equalsIgnoreCase(trimmedName, buildings[i])) {
			return static_cast<int>(i);
		}
	}
	return -1; // Building not found
}

// 
const std::string& CampusGraph::getBuildingName(int index) const {
	if (index < 0 || index >= static_cast<int>(buildings.size())) {
		throw std::out_of_range("Index out of range");
	}
	return buildings[index];
}

// 
std::string CampusGraph::addConnection(const std::string& building1, const std::string& building2) {
	int index1 = findBuilding(building1);
	int index2 = findBuilding(building2);
	if (index1 == -1 || index2 == -1) {
		return "Error: One or both buildings do not exist.";
	}
	if (index1 == index2) {
		return "Error: Cannot connect a building to itself.";
	}
	// Check if the connection already exists
	for (int neighbor : adjacencyList[index1]) {
		if (neighbor == index2) {
			return "Error: Connection already exists.";
		}
	}
	adjacencyList[index1].push_back(index2);
	adjacencyList[index2].push_back(index1);
	connectionCount++;
	return "Connection added successfully.";
}

// 
int CampusGraph::getDegree(const std::string& buildingName) const {
	int index = findBuilding(buildingName);
	if (index == -1) {
		return -1; // Building not found
	}
	return static_cast<int>(adjacencyList[index].size());
}

// 
int CampusGraph::buildingCount() const {
	return static_cast<int>(buildings.size());
}

int CampusGraph::numConnections() const {
	return connectionCount;
}

// 
void CampusGraph::display() const {
	for (size_t i = 0; i < buildings.size(); ++i) {
		std::cout << buildings[i] << ": ";
		for (int neighbor : adjacencyList[i]) {
			std::cout << buildings[neighbor] << " ";
		}
		std::cout << std::endl;
	}
}

// 
void CampusGraph::displayCountsAndDegrees() const {
	std::cout << "Total buildings: " << buildingCount() << std::endl;
	std::cout << "Total connections: " << numConnections() << std::endl;
	for (const auto& building : buildings) {
		std::cout << building << ": Degree = " << getDegree(building) << std::endl;
	}
}

// 
void CampusGraph::bfsReachable(const std::string& startBuilding) const {
	int startIndex = findBuilding(startBuilding);
	if (startIndex == -1) {
		std::cout << "Error: Starting building does not exist." << std::endl;
		return;
	}
	std::vector<bool> visited(buildings.size(), false);
	std::vector<int> distance(buildings.size(), 0);
	std::queue<int> q;
	q.push(startIndex);
	visited[startIndex] = true;
	int reachableCount = 0;
	int currentIndex = startIndex;
	while (!q.empty()) {
		currentIndex = q.front();
		q.pop();
		std::cout << buildings[currentIndex] << " (Distance: " << reachableCount << ")" << std::endl;
		reachableCount++;
		for (int neighbor : adjacencyList[currentIndex]) {
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				distance[neighbor] = distance[currentIndex] + 1;
				q.push(neighbor);
			}
		}
	}
	std::cout << "Reachable: " << distance[currentIndex] << " of " << buildingCount() << std::endl;
}