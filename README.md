# | Project 2: Smart Campus Navigation System and Facility Analytics System |
# --------------------------------------------------------------------------------------

Requirements: g++ with C++11 support. Run all commands from the project
root (the folder that contains data/, src/, and include/).

Build
    g++ -std=c++11 -Wall -Wextra -Iinclude src/*.cpp -o campus

Run with the default data folder (data/)
    ./campus

Run with a different data folder (optional argument)
    ./campus DATA_DIRECTORY

The data directory must contain buildings.txt, connections.txt,
facilities.txt, and departments.txt. A missing file is reported and treated
as empty.

TEST DATA RUN COMMANDS

---- MEMBER B TESTS: data folders -----------------------------

Run these with no folder argument. The last 0 exits the menu.
    B1   ./campus
    B9   printf "3\n0\n" | ./campus
    B10  printf "4\n0\n" | ./campus
    B11  printf "5\nLibrary\n0\n" | ./campus
    B12  printf "5\nObservatory\n0\n" | ./campus
    B13  printf "5\nNarnia\n0\n" | ./campus
    B14  printf "5\n\n0\n" | ./campus
    B15  printf "5\n  student union  \n0\n" | ./campus
    B17  printf "5\nNarnia\n5\nLibrary\n0\n" | ./campus

---- MEMBER B TESTS: test folders -----------------------------
    B2     ./campus testdata/case1_fields
    B3     ./campus testdata/case2_missing_connections
    B4     ./campus testdata/case3_dup_buildings
    B5-B7  ./campus testdata/case4_bad_connections
    B16    printf "5\nNorth Hall\n5\nSouth Hall\n5\nLonely Shed\n0\n" | ./campus testdata/case5_components
    B8     ./campus testdata/case6_crlf_whitespace

---- SAVING OUTPUT (optional) ---------------------------------
Add > output.txt to any command to save the output to a file:
    printf "5\nLibrary\n0\n" | ./campus > output.txt

# --------------------------------


# | Section A: Abhijeeth Chouti |
Facility Database (Facility.h, FacilityDatabase.h, FacilityDatabase.cpp)

Purpose: Stores campus facility records and supports displaying all facilities, searching facilities by ID, and validating facility information. It maintains the order in which facilities were accepted from the input file.

Representation: A vector of facility records connected to a custom hash table.

* Facility stores four strings: id, name, building, and category.
* facilities (std::vector<Facility>) stores accepted facility records in insertion order.
* idIndex (HashTable) provides fast facility lookup using a normalized facility ID.

Each facility is stored in the vector, while the hash table stores its ID and corresponding vector index. This allows facilities to be displayed in file order without scanning the entire vector during ID searches.

Why a vector: It grows dynamically, preserves the order of accepted records, and allows direct access to a facility using the index returned by the hash table.

Main functions:

Function	Description
addFacility(facility, error)	Trims fields, normalizes the ID, rejects invalid or duplicate IDs and empty fields, and inserts an accepted facility. Returns true on success or false with a rejection reason.
findById(id)	Looks up a facility using the custom hash table. Returns a pointer to the facility or nullptr if not found.
findByName(name)	Performs a case-insensitive, exact-name search and returns all matches in insertion order.
findByCategory(category)	Performs a case-insensitive, exact-category search and returns all matching facilities.
displayAll()	Prints every accepted facility with ID, name, building, and category, followed by the total count.
displayIdSearch(id)	Normalizes and validates the entered ID, then displays the matching facility or an appropriate error message.
size()	Returns the total number of accepted facilities.
hashCapacity()	Returns the hash table capacity.
hashEntries()	Returns the number of facility IDs stored in the hash table.
hashCollisions()	Returns the total number of collisions encountered during accepted insertions.

Planned for Final: Facility name search, category search, and facility category report. These functions are already included in the current FacilityDatabase implementation but are not required through the M1 menu.

⸻

Custom Hash Table (HashTable.h, HashTable.cpp)

Purpose: Provides efficient facility lookup by ID using a custom hash function and separate chaining for collision handling. It also detects duplicate facility IDs and tracks hash table statistics.

Representation: A vector of buckets, where each bucket contains a vector of entries.

* buckets (std::vector<std::vector<Entry>>) stores the hash table buckets.
* Entry holds a normalized facility ID (key) and its corresponding facility vector index (recordIndex).
* entryCount (std::size_t) tracks the number of stored entries.
* collisionCount (std::size_t) tracks collisions during successful insertions.
* DEFAULT_CAPACITY is set to 17.

Facility IDs are trimmed and converted to uppercase before hashing, insertion, or lookup. Each ID must begin with F followed by exactly three digits.

Hash function:

hash = (hash * 31 + ASCII(character)) % capacity

The hash starts at zero and processes each character of the normalized facility ID.

Collision handling: Separate chaining is used. When different IDs map to the same bucket, they are stored as separate entries within that bucket. An insertion into a nonempty bucket counts as one collision, provided the ID is not a duplicate.

Why separate chaining: It handles collisions without overwriting existing facilities, allows buckets to grow dynamically, and avoids an arbitrary maximum facility count.

Main functions:

Function	Description
HashTable(capacity)	Initializes the hash table with the specified capacity, defaulting to 17.
hashKey(key)	Calculates the bucket index using the custom polynomial string hash function.
insert(id, recordIndex)	Normalizes the ID, rejects invalid or duplicate IDs, stores the entry, and updates collision statistics.
find(id, recordIndex)	Searches the calculated bucket for the normalized ID and returns the associated record index when found.
capacity()	Returns the number of hash table buckets.
size()	Returns the number of stored entries.
collisions()	Returns the collision count.

⸻

Facility File Loading (FileLoader.h, FileLoader.cpp)

Purpose: Reads facility records from facilities.txt, validates each record, and stores accepted facilities in the FacilityDatabase. Invalid records are rejected with warnings.

Input format:

FacilityID|FacilityName|BuildingName|Category

Example:

F004|Computer Lab A|Science Building|Computer Lab

Validation:

* Blank lines and comment lines are ignored.
* Every record must contain exactly four fields.
* All required fields must be nonempty after trimming.
* Facility IDs must follow the format F plus exactly three digits.
* Duplicate facility IDs are rejected without replacing the first accepted record.
* Building names must exist in the campus graph.
* Building references are matched case-insensitively, preserving the spelling from buildings.txt.
* Every rejected record produces a warning containing the filename, line number, and reason.

Main functions:

Function	Description
loadFacilities(filename, database, graph)	Reads and validates facility records, inserts accepted records, and prints the loading summary and hash diagnostics.
openDataFile(filename, fileStream)	Opens the requested file and reports an error if it cannot be opened.
printWarning(filename, lineNumber, message)	Displays a warning for an invalid record.
printLoadSummary(filename, result)	Displays the number of accepted and rejected records.

Load summary: After loading facilities.txt, the program reports the accepted and rejected record counts, hash table capacity, stored entries, and collisions.

⸻

Facility Menu Functions (Menu.h, Menu.cpp)

Purpose: Connects the facility database operations to the main interactive menu.

Milestone 1 Menu Options:

* Option 1: View all facilities.
* Option 2: Search facility by ID.

Main functions:

Function	Description
handleViewFacilities(db)	Calls the facility database to display all accepted facilities and the total count.
handleSearchFacilityById(db)	Prompts the user for a facility ID, checks for blank input, and performs an ID search.
runMenu(db, graph, tree)	Displays the repeating M1 menu and dispatches the user’s selection to the appropriate module.

Input handling: Menu selections are read as complete lines. Invalid numeric input is rejected without crashing. Facility IDs are trimmed and normalized before searching.

Planned for Final: Add menu options for facility name search, category search, and the facility category report.

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

