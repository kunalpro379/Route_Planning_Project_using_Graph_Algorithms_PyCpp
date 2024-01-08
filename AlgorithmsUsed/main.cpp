// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <limits>
// #include <queue>
// #include <algorithm> // Include this header for std::reverse

// struct Edge {
//     int destination;
//     int weight;

//     Edge(int destiny, int w) : destination(destiny), weight(w) {}
// };

// struct Graph {
//     std::vector<std::vector<Edge>> adjacencyList;

//     void AddEdge(int src, int dest, int weight) {
//         adjacencyList[src].emplace_back(dest, weight);
//     }
// };

// void BuildGraphFromJSON(Graph& g, const std::string& jsonFileName) {
//     std::ifstream file(jsonFileName);
//     if (!file.is_open()) {
//         std::cerr << "Error opening file: " << jsonFileName << "\n";
//         return;
//     }

//     std::stringstream buffer;
//     buffer << file.rdbuf();
//     file.close();

//     std::string jsonString = buffer.str();

//     size_t pos = jsonString.find("\"edges\":") + 9;
//     size_t endPos = jsonString.find("]", pos) + 1;

//     std::string edgesSubstring = jsonString.substr(pos, endPos - pos);

//     size_t currentPos = edgesSubstring.find("{");
//     while (currentPos != std::string::npos) {
//         size_t endOfEdge = edgesSubstring.find("}", currentPos);
//         std::string edge = edgesSubstring.substr(currentPos, endOfEdge - currentPos + 1);

//         size_t uPos = edge.find("\"u\":") + 5;
//         size_t vPos = edge.find("\"v\":") + 5;

//         try {
//             int u = std::stoi(edge.substr(uPos, edge.find(",", uPos) - uPos));
//             int v = std::stoi(edge.substr(vPos, edge.find("}", vPos) - vPos));

//             // Assuming weight is 0 for now, adjust as needed based on your data
//             g.AddEdge(u, v, 0);
//         } catch (const std::exception& e) {
//             std::cerr << "Error parsing 'u' or 'v': " << e.what() << "\n";
//             std::cerr << "Substring causing the error: " << jsonString.substr(currentPos, 20) << "\n";
//             return;
//         }

//         currentPos = edgesSubstring.find("{", endOfEdge);
//     }
// }

// // Corrected function signature
// std::vector<long long> SHORTEST_PATH(Graph& g, long long start) {
//     // Remaining code remains unchanged
//     // ...

//     // Initialization
//     std::vector<int> dist(g.adjacencyList.size(), std::numeric_limits<int>::max());
//     std::vector<int> prev(g.adjacencyList.size(), -1);
//     dist[start] = 0;

//     // Priority queue to store vertices and their distances
//     std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
//     pq.push({0, start});

//     while (!pq.empty()) {
//         int u = pq.top().second;
//         pq.pop();

//         for (const Edge& edge : g.adjacencyList[u]) {
//             int v = edge.destination;
//             int weight = edge.weight;

//             if (dist[u] + weight < dist[v]) {
//                 dist[v] = dist[u] + weight;
//                 prev[v] = u;
//                 pq.push({dist[v], v});
//             }
//         }
//     }

//     // Reconstruct the shortest path
//     std::vector<int> shortestPath;
//     for (int v = g.adjacencyList.size() - 1; v != -1; v = prev[v]) {
//         shortestPath.push_back(v);
//     }
//     std::reverse(shortestPath.begin(), shortestPath.end());

//     return shortestPath;
// }
// int main() {
//     Graph g;

//     // Build the graph from JSON
//     BuildGraphFromJSON(g, "Save_Edge_Node_here/mapping.json");

// long long sourceNode = 7374219748LL;
// long long destinationNode = 1643351828LL;


//     // Example: Run Dijkstra's algorithm from the source to the destination
// std::vector<int> SHORTEST_PATH(Graph& g, int start);

//     // Print the shortest path
//     std::cout << "Shortest Path from " << sourceNode << " to " << destinationNode << ":\n";
//     for (long long vertex : shortestPath) {
//         std::cout << "Vertex " << vertex << "\n";
//         if (vertex == destinationNode) {
//             break;  // Stop printing when reaching the destination
//         }
//     }

//     return 0;
// }

