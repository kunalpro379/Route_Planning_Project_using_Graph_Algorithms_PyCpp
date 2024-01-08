import ipyleaflet
import networkx

def draw_route(G, route, zoom=15):
    if len(G)>=1500:
        # Too many nodes to use ipyleaflet
        return osmnx.plot_route_folium(G=G,route=route)
    
    # Calculate the center node of the graph
    # This used to be accessible from extended_stats, but now we have to do it manually with a undirected graph in networkx
    undir = G.to_undirected()
    length_func = networkx.single_source_dijkstra_path_length
    sp = {source: dict(length_func(undir, source, weight="length")) for source in G.nodes}
    eccentricity = networkx.eccentricity(undir,sp=sp)
    center = networkx.center(undir,e=eccentricity)[0]

    # Create the leaflet map and center it around the center of our graph
    G_gdfs = osmnx.graph_to_gdfs(G)
    nodes_frame = G_gdfs[0]
    ways_frame = G_gdfs[1]
    center_node = nodes_frame.loc[center]
    location = [center_node.y,center_node.x]
    m = ipyleaflet.Map(center=location, zoom=zoom)

    # Get our starting and ending nodes
    start_node = nodes_frame.loc[route[0]]
    end_node = nodes_frame.loc[route[-1]]
    start_xy = [start_node.y, start_node.x]
    end_xy = [end_node.y,end_node.x]

    # Add both nodes as markers
    m.add_layer(ipyleaflet.Marker(location=start_xy, draggable=False))
    m.add_layer(ipyleaflet.Marker(location=end_xy, draggable=False))

    # Add edges of route
    for u,v in zip(route[0:],route[1:]):
        try:
            x,y = (ways_frame.query(f'u == {u} and v == {v}').to_dict('list')['geometry'])[0].coords.xy
        except:
            x,y = (ways_frame.query(f'u == {v} and v == {u}').to_dict('list')['geometry'])[0].coords.xy

        points = map(list, [*zip([*y],[*x])])
        ant_path = ipyleaflet.AntPath(
            locations = [*points], 
            dash_array=[1, 10],
            delay=1000,
            color='#7590ba',
            pulse_color='#3f6fba'
        )
        m.add_layer(ant_path)

    return m
draw_route(graph, shortest_route)