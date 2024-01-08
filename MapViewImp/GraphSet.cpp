#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

// Define a structure to represent a node
struct Node {
    string id;
    vector<pair<string, double>> neighbors; // pair: (targetNodeId, weight)
};

// Define a structure to represent a graph
struct Graph {
    unordered_map<string, Node> nodes;

    void addEdge(string source, string target, double weight) {
        nodes[source].id = source;
        nodes[target].id = target;
        nodes[source].neighbors.emplace_back(target, weight);
    }
};

std::vector<pair<string, double>> dijkstra(const Graph& graph, string source, string target) {
    std::priority_queue<std::pair<double, string>, std::vector<std::pair<double, string>>, std::greater<std::pair<double, string>>> pq;
    std::unordered_map<string, double> distance;
    std::unordered_map<string, string> previous;

    // Initialize distances
    for (const auto& node : graph.nodes) {
        distance[node.first] = std::numeric_limits<double>::infinity();
        previous[node.first] = "";
    }
    distance[source] = 0;

    // Insert source node into the priority queue
    pq.push({0, source});

    // Dijkstra's algorithm
    while (!pq.empty()) {
        double currentDistance = pq.top().first;
        string current = pq.top().second;
        pq.pop();

        if (current == target) {
            break;  // Reached the target node, no need to explore further
        }

        for (const auto& neighborPair : graph.nodes.at(current).neighbors) {
            string neighbor = neighborPair.first;
            double weight = neighborPair.second;

            if (distance[current] + weight < distance[neighbor]) {
                distance[neighbor] = distance[current] + weight;
                previous[neighbor] = current;
                pq.push({distance[neighbor], neighbor});
            }
        }
    }

    // Reconstruct the shortest path
    std::vector<pair<string, double>> path;
    string current = target;
    while (!previous[current].empty()) {
        path.push_back({current, distance[current]});
        current = previous[current];
    }
    path.push_back({source, 0.0});

    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    // Create a graph
    Graph graph;

    // Read 'uv_mapping.txt' file
    ifstream file("mapping.txt");
    if (!file.is_open()) {
        cerr << "Error: cannot open file" << endl;
        return 1;
    }

    string source, target;
    double weight;
    while (file >> source >> target >> weight) {
        graph.addEdge(source, target, weight);
    }

    // Specify source and target nodes
    string sourceNode = "2143585200";
    string targetNode = "7252080901";

    std::vector<pair<string, double>> shortestPath = dijkstra(graph, sourceNode, targetNode);

    // Print the shortest path
    std::cout << "Shortest Path:" << std::endl;
    ofstream output("shortest_path.txt");
    for (const auto& node : shortestPath) {
        std::cout << "Node: " << node.first << ", Weight: " << node.second << " -> ";
        output << "Node: " << node.first << ", Weight: " << node.second << " -> ";
    }
    std::cout << std::endl;
    output.close();

    return 0;
}
