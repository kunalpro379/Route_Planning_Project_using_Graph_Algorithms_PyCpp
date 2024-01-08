import geopandas as gpd

# Read GeoJSON file for edges
edges_gdf = gpd.read_file('MapViewImp/Data_Save_here/all_edges.geojson')

# Extract 'osmid' values as a list
osmid_list = edges_gdf['osmid'].tolist()

# Pair adjacent 'osmid' values to get edges
edges_uv_list = list(zip(osmid_list, osmid_list[1:]))

# Save 'u' and 'v' data to a text file
with open('MapViewImp/Data_Save_here/mapping.txt', 'w') as text_file:
    for edge in edges_uv_list:
        text_file.write(f"{edge[0]} {edge[1]}\n")

# Print the contents of the 'mapping.txt' file
with open('MapViewImp/Data_Save_here/mapping.txt', 'r') as text_file:
    contents = text_file.read()

print(edges_gdf)
print(edges_gdf.columns)

