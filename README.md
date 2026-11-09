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
## Department Tree (`DepartmentNode.h`, `DepartmentTree.h`, `DepartmentTree.cpp`)

**Purpose:** Stores the academic department hierarchy as a general tree (a node can have any number of children). It supports adding and searching departments, displaying the hierarchy, preorder / postorder / level-order traversals, and department statistics.

**Representation:** Each `DepartmentNode` holds its `name`, a `parent` pointer (`nullptr` for the root), and a `std::vector<DepartmentNode*> children` kept in insertion order. `DepartmentTree` owns the `root` pointer and a node count. The destructor frees every node.

**Why a vector of child pointers:** A department can have any number of sub-departments, the vector grows dynamically (no fixed limits), and sibling order is preserved for traversals.

**Main functions:**

| Function | Description |
|---|---|
| `addRoot(name, error)` | Creates the root when the tree is empty. Returns false and fills `error` on failure. |
| `addChild(name, parent, error)` | Rejects blank names, unknown parents, and duplicate names (case-insensitive). Tree is unchanged on failure. |
| `find(name)` | Case-insensitive, trimmed search. Returns the node or `nullptr`. |
| `displaySearchResult(name)` | Shows name, parent (`None` for the root), direct-child count, and depth. |
| `displayHierarchy()` | Preorder display, one department per line, 4 spaces of indent per depth. |
| `preorder()` / `postorder()` | Return the traversal as a sequence (no indentation). |
| `levelOrder()` | Breadth-first traversal using `std::queue`; siblings in insertion order. |
| `printSequence(title, seq)` | Prints a traversal sequence, or an empty-tree message. |
| `computeStats()` / `displayStats()` | Total departments, leaves, and height (`N/A` when empty; a root-only tree is 1, 1, 0). |

**File loading (`FileLoader.h`, `Fileloader.cpp`):** `loadDepartments(path, tree)` reads `departments.txt` with `getline`, skips blank and comment lines, trims whitespace and `\r`, and enforces the Section 5.5 rules: the first valid record is the root with parent `NONE`, later records need a parent accepted on an earlier line, and names are unique ignoring case. Each rejected record prints a warning with filename, line number, and reason. A missing file prints an error and is treated as empty. A summary line with accepted and rejected counts is printed at the end.

**Menu options:** Add department, Search department, Display department hierarchy, Preorder traversal (Milestone 1); Postorder, Level-order, and Department statistics are added in the Final menu.




g++ -std=c++11 -Wall -Wextra -Iinclude src/*.cpp -o campus
