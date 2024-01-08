#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <limits>
#include <queue>
#include <algorithm>

struct Edge {
    int destination;
    int weight;

    Edge(int destiny, int w) : destination(destiny), weight(w) {}
};

struct Graph {
    std::unordered_map<int, std::vector<Edge>> adjacencyList;
};

void BuildGraphFromJSON(Graph& g) {
    // Read the mapping data from the JSON file
    std::ifstream jsonFile("Save_Edge_Node_here/mapping.json");

    // Check if the file exists
    if (!jsonFile.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    // Read the entire file content
    std::string jsonString((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());
    jsonFile.close();

    // Parse JSON manually
    size_t startPos = jsonString.find("\"edges\":") + 9;
    size_t endPos = jsonString.find("]", startPos) + 1;

    std::string edgesSubstring = jsonString.substr(startPos, endPos - startPos);

    // Process each edge in the substring
    size_t currentPos = edgesSubstring.find("{");
    while (currentPos != std::string::npos) {
        std::string uStr, vStr;  // Declare uStr and vStr here
        size_t endOfEdge = edgesSubstring.find("}", currentPos);
        std::string edge = edgesSubstring.substr(currentPos, endOfEdge - currentPos + 1);

        // Parse 'u' and 'v' manually
        size_t uPos = edge.find("\"u\":") + 5;
        size_t vPos = edge.find("\"v\":") + 5;

        try {
            uStr = edge.substr(uPos, edge.find(",", uPos) - uPos);
            vStr = edge.substr(vPos, edge.find("}", vPos) - vPos);

            long long u = std::stoll(uStr);
            long long v = std::stoll(vStr);

            // Add edge to the graph
            g.adjacencyList[u].emplace_back(v, 1);  // Assuming unit weight for simplicity
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
            std::cerr << "Problematic substring (u): " << uStr << std::endl;
            std::cerr << "Problematic substring (v): " << vStr << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << std::endl;
            std::cerr << "Problematic substring (u): " << uStr << std::endl;
            std::cerr << "Problematic substring (v): " << vStr << std::endl;
        }

        // Move to the next edge
        currentPos = edgesSubstring.find("{", endOfEdge);
    }
}

std::vector<int> SHORTEST_PATH(Graph& g, int start) {
    // Determine the number of nodes in the graph
    int numNodes = g.adjacencyList.size();

    // Initialization
    std::vector<int> dist(numNodes, std::numeric_limits<int>::max());
    std::vector<int> prev(numNodes, -1);
    dist[start] = 0;

    // Priority queue to store vertices and their distances
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const Edge& edge : g.adjacencyList[u]) {
            int v = edge.destination;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // Reconstruct the shortest path
    std::vector<int> shortestPath;
    for (int v = numNodes - 1; v != -1; v = prev[v]) {
        shortestPath.push_back(v);
    }
    std::reverse(shortestPath.begin(), shortestPath.end());

    return shortestPath;
}



int main() {
    Graph g;

    // Build the graph from JSON
    BuildGraphFromJSON(g);

    // // Example: Print the adjacency list (for verification)
    // for (int i = 0; i < g.adjacencyList.size(); ++i) {
    //     std::cout << "Node " << i << " is connected to: ";
    //     for (const Edge& edge : g.adjacencyList[i]) {
    //         std::cout << edge.destination << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // Example: Run Dijkstra's algorithm from vertex 0
    std::vector<int> shortestPath = SHORTEST_PATH(g, 0);

    // Print the shortest path
    std::cout << "Shortest Path:\n";
    for (int vertex : shortestPath) {
        std::cout << "Node " << vertex << std::endl;
    }

    return 0;
}
