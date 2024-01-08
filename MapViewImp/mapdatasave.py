import folium
import geopandas as gpd
import json
import networkx
import osmnx

# Load the JSON file
with open("MapViewImp/Data_Save_here/coordinates.json", "r") as json_file:
    data = json.load(json_file)

# Extracted Coordinates as tuples
source_point = (data['source_coords']['latitude'], data['source_coords']['longitude'])
destination_point = (data['destination_coords']['latitude'], data['destination_coords']['longitude'])

# Print the extracted coordinates
print("Source Point:", source_point)
print("Destination Point:", destination_point)

center = ((source_point[0] + destination_point[0]) / 2, (source_point[1] + destination_point[1]) / 2)
print("Drawing Graph >>>>> please wait")

graph = osmnx.graph_from_point(center, dist=3000)

# Get the central coordinates from the graph
center_coords = (graph.nodes[list(graph.nodes)[0]]['y'], graph.nodes[list(graph.nodes)[0]]['x'])

# Create a Folium map
m = folium.Map(location=center_coords, zoom_start=15)
osmnx.plot_graph(graph, figsize=(10, 10), node_size=30, node_color='w')

# Get nodes and edges
nodes, edges = osmnx.graph_to_gdfs(graph)

# First convert the source and destination nodes to Node
X = [source_point[1], destination_point[1]]
Y = [source_point[0], destination_point[0]]
closest_nodes = osmnx.distance.nearest_nodes(graph, X, Y)


folium.Marker(location=source_point, icon=folium.Icon(color='red', icon='camera', prefix='fa')).add_to(m)
folium.Marker(location=center_coords, icon=folium.Icon(color='blue', icon='graduation-cap', prefix='fa')).add_to(m)
folium.Marker(location=destination_point, icon=folium.Icon(color='green', icon='university', prefix='fa')).add_to(m)

# Save nodes and edges to GeoJSON files
nodes.to_file("MapViewImp/Data_Save_here/nodes.geojson", driver="GeoJSON")
print("MapViewImp/Data_Save_here/Nodes data saved")

edges.to_file("MapViewImp/Data_Save_here/edges.geojson", driver="GeoJSON")
print("MapViewImp/Data_Save_here/Edges data saved")

# Read GeoJSON file for edges
edges_gdf = gpd.read_file('Data_Save_here/edges.geojson')

# Extract 'u' and 'v' columns from edges_gdf
edges_uv_df = edges_gdf[['u', 'v']]

# Save 'u' and 'v' data to a JSON file
uv_mapping_data = {"edges": []}
for index, row in edges_uv_df.iterrows():
    uv_mapping_data["edges"].append({"u": int(row['u']), "v": int(row['v'])})

with open('MapViewImp/Data_Save_here/mapping.json', 'w') as json_file:
    json.dump(uv_mapping_data, json_file)

# Print the contents of the 'uv_mapping.json' file
with open('MapViewImp/Data_Save_here/mapping.json', 'r') as json_file:
    contents = json.load(json_file)
    print(contents)

# Display the Folium map
m.save("map_with_graph.html") 