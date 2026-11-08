/* Building list (insertion order), adjacency lists, add building/edge with validation,
 * degree, display, BFS, shortest path (Final), connectivity report (Final). */

#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H
#include <string>
#include <vector>

class CampusGraph {
private:
	std::vector<std::string> buildings;
	std::vector<std::vector<int>> adjacencyList;
	int connectionCount;

public:
	CampusGraph();
	bool addBuilding(const std::string& buildingName, std::string& error);
	int findBuilding(const std::string& buildingName) const;
	const std::string& getBuildingName(int index) const;
	bool addConnection(const std::string& building1, const std::string& building2, std::string& error);
	int getDegree(const std::string& buildingName) const;
	int buildingCount() const;
	int numConnections() const;
	void display() const; // Prints buildings in insertion order with neighbors in neighbor order

	// Prints total buildings, total connections, and every building’s degree
	void displayCountsAndDegrees() const;

	// Prints reachable buildings in visit order with distances, plus “Reachable: X of Y”
	void bfsReachable(const std::string& startBuilding) const;

};

#endif // CAMPUSGRAPH_H