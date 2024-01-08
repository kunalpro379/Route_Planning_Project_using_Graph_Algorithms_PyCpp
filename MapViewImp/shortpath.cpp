#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <sstream>
// A simplified GeoJSON structure for demonstration purposes
struct GeoJSONFeature {
    std::string type;
    std::string id;
    std::vector<std::vector<double>> coordinates;
    double length;
};

// Function to calculate the Haversine distance between two points
double haversineDistance(const std::vector<double>& coord1, const std::vector<double>& coord2) {
    const double R = 6371.0; // Earth radius in kilometers
    double lat1 = coord1[1];
    double lon1 = coord1[0];
    double lat2 = coord2[1];
    double lon2 = coord2[0];

    double dLat = (lat2 - lat1) * (M_PI / 180.0);
    double dLon = (lon2 - lon1) * (M_PI / 180.0);

    double a = std::sin(dLat / 2.0) * std::sin(dLat / 2.0) +
               std::cos(lat1 * (M_PI / 180.0)) * std::cos(lat2 * (M_PI / 180.0)) *
               std::sin(dLon / 2.0) * std::sin(dLon / 2.0);

    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

    return R * c;
}

// Dijkstra's algorithm implementation
std::vector<double> dijkstra(const std::vector<GeoJSONFeature>& graph, size_t source, size_t target) {
    size_t n = graph.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<bool> visited(n, false);

    dist[source] = 0;

    for (size_t i = 0; i < n - 1; ++i) {
        size_t u = 0;
        double minDist = std::numeric_limits<double>::infinity();

        // Find the vertex with the minimum distance
        for (size_t j = 0; j < n; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }

        visited[u] = true;

        // Relaxation step
        for (size_t v = 0; v < n; ++v) {
            double weight = haversineDistance(graph[u].coordinates.back(), graph[v].coordinates.front());
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    return dist;
}

// Your graph data structure and Dijkstra's algorithm implementation
// ...

int main() {
    // Read the GeoJSON data from a file
    std::ifstream file("edges.geojson");
    if (!file.is_open()) {
        std::cerr << "Error opening GeoJSON file." << std::endl;
        return 1;
    }

    // Read the file content into a string
    std::string geoJSON((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Parse GeoJSON features
    size_t pos = 0;
    std::vector<GeoJSONFeature> features;
    while ((pos = geoJSON.find("Feature", pos)) != std::string::npos) {
        GeoJSONFeature feature;
        feature.type = "Feature";
        // Simplified parsing logic; adapt this based on your actual GeoJSON structure
        // This example assumes a FeatureCollection containing features with 'type' and 'coordinates'
        size_t start = geoJSON.find("[[", pos);
        size_t end = geoJSON.find("]]", start);
        std::string coordinatesStr = geoJSON.substr(start, end - start + 2);
        std::replace(coordinatesStr.begin(), coordinatesStr.end(), ',', ' '); // Replace commas with spaces
        std::istringstream iss(coordinatesStr);
        double lat, lon;
        while (iss >> lon >> lat) {
            feature.coordinates.push_back({lon, lat});
        }
        feature.length = std::stod(geoJSON.substr(geoJSON.find("length", pos) + 8, 10)); // Extract length

        features.push_back(feature);

        // Move to the next position
        pos += 7; // Skip past "Feature"
    }

    // Implement the rest of your code, building the graph and running Dijkstra's algorithm
    // ...
        size_t sourceIndex = 0;
    size_t targetIndex = 3;

    // Run Dijkstra's algorithm
    std::vector<double> shortestDistances = dijkstra(graph, sourceIndex, targetIndex);

    // Output the shortest distances
    std::cout << "Shortest Distance from node " << sourceIndex << " to node " << targetIndex << ": "
              << shortestDistances[targetIndex] << " kilometers" << std::endl;

  
}
