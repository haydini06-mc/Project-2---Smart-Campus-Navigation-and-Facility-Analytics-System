# | Project 2: Smart Campus Navigation System and Facility Analytics System |
# --------------------------------------------------------------------------------------

## | Project Overview |



## | Build and Run |



## | Directory Layout |


# --------------------------------


# | Section A: Abhijeeth Chouti |



# | Section B: Hayden Goff |

## Campus Graph (`CampusGraph.h`, `CampusGraph.cpp`)

**Purpose:** Stores campus buildings and the walkways between them as an
undirected, unweighted graph. It supports display, counts and degrees, and
Breadth-First Search (BFS) reachability.

**Representation:** An adjacency list built from parallel vectors.
- `buildings` (`std::vector<std::string>`) holds building names in insertion order.
  A building's position in this vector is its index.
- `adjacencyList` (`std::vector<std::vector<int>>`) holds, for each building index,
  the indices of its neighbors in the order the connections were accepted.
- `connectionCount` (`int`) holds the number of connections, counted once each.

Both vectors grow together, so they always have the same length. Neighbors are
never sorted, so BFS order follows connection insertion order.

**Why an adjacency list:** It grows dynamically (no fixed limits), keeps insertion
order, and lets BFS work with simple integer indices.

**Main functions:**

| Function | Description |
|---|---|
| `addBuilding(name)` | Trims the name, rejects empty or duplicate names (case-insensitive), keeps the first spelling. Returns "" on success or a rejection reason. |
| `addConnection(a, b)` | Rejects unknown buildings, self-connections, and duplicates (including reversed). Updates both endpoints and counts the connection once. Returns "" on success or a reason. |
| `findBuilding(name)` | Case-insensitive, trimmed lookup. Returns the index, or -1 if not found. |
| `getBuildingName(index)` | Returns the stored spelling of a building. |
| `getDegree(name)` | Returns the number of neighbors, or -1 if the building is unknown. |
| `buildingCount()`, `numConnections()` | Totals. |
| `display()` | Prints each building with its neighbors, or "(no connections)". |
| `displayCountsAndDegrees()` | Prints total buildings, total connections, and every degree. |
| `bfsReachable(start)` | BFS using a queue and a visited structure (marked when enqueued). Prints reachable buildings in visit order with distances, then "Reachable: X of Y". |

**Planned for Final:** shortest path (BFS with parent tracking) and the graph
connectivity report.

##s Utils (`Utils.h`, `Utils.cpp`)

**Purpose:** Shared text helpers used by every module so that trimming and
case handling behave the same everywhere.

| Function | Description |
|---|---|
| `trim(s)` | Removes spaces, tabs, `\r`, and `\n` from both ends. Internal spaces are preserved. |
| `toUpper(s)` | Returns an uppercase copy of the string. |
| `equalsIgnoreCase(a, b)` | Case-insensitive comparison (does not trim). |
| `split(str, delimiter)` | Splits a line on the delimiter and keeps empty fields so loaders can detect bad field counts. |
| `isBlankOrComment(line)` | True if the line is blank or its first non-whitespace character is `#`. |

# | Section C: Derick Ohonbamu |
