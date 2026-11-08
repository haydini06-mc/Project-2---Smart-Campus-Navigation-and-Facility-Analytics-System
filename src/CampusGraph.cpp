#include "CampusGraph.h"
#include "Utils.h"

#include <iostream>
#include <queue>
#include <stdexcept>

CampusGraph::CampusGraph() : connectionCount(0) {}

// Adds a building if its trimmed name is nonempty and not already present (case-insensitive).
// Keeps the spelling from the first accepted record. On failure, fills 'error'.
bool CampusGraph::addBuilding(const std::string& buildingName, std::string& error) {
	std::string name = trim(buildingName);
	if (name.empty()) {
		error = "building name is empty";
		return false;
	}
	if (findBuilding(name) != -1) {
		error = "duplicate building '" + name + "'";
		return false;
	}
	buildings.push_back(name);
	adjacencyList.push_back(std::vector<int>());
	return true;
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
// Adds an undirected connection between two existing buildings.
// Rejects empty names, unknown buildings, self-connections, and duplicates
// (including reversed ones). Counts the connection once. On failure, fills 'error'.
bool CampusGraph::addConnection(const std::string& building1, const std::string& building2, std::string& error) {
	std::string name1 = trim(building1);
	std::string name2 = trim(building2);
	if (name1.empty() || name2.empty()) {
		error = "empty required field";
		return false;
	}

	int index1 = findBuilding(name1);
	int index2 = findBuilding(name2);
	if (index1 == -1) {
		error = "unknown building '" + name1 + "'";
		return false;
	}
	if (index2 == -1) {
		error = "unknown building '" + name2 + "'";
		return false;
	}
	if (index1 == index2) {
		error = "cannot connect a building to itself";
		return false;
	}
	for (int neighbor : adjacencyList[index1]) {
		if (neighbor == index2) {
			error = "duplicate connection '" + name1 + "|" + name2 + "'";
			return false;
		}
	}

	adjacencyList[index1].push_back(index2);
	adjacencyList[index2].push_back(index1);
	connectionCount++;
	return true;
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
	if (buildings.empty()) {
		std::cout << "No buildings are loaded." << std::endl;
		return;
	}
	for (size_t i = 0; i < buildings.size(); ++i) {
		std::cout << buildings[i] << ": ";
		if (adjacencyList[i].empty()) {
			std::cout << "(no connections)";
		}
		else {
			for (size_t j = 0; j < adjacencyList[i].size(); ++j) {
				if (j > 0) std::cout << ", ";
				std::cout << buildings[adjacencyList[i][j]];
			}
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
		std::cout << buildings[currentIndex] << " (Distance: " << distance[currentIndex] << ")" << std::endl;
		reachableCount++;
		for (int neighbor : adjacencyList[currentIndex]) {
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				distance[neighbor] = distance[currentIndex] + 1;
				q.push(neighbor);
			}
		}
	}
	std::cout << "Reachable: " << reachableCount << " of " << buildingCount() << std::endl;
}