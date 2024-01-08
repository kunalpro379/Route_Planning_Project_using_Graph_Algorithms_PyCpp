# GmapSet.py

import tkinter as tk
import tkintermapview
from geopy.geocoders import Nominatim
import folium
import json

class MapViewerApp:
    def __init__(self, root):
        self.root = root
        self.root.geometry(f"{800}x{600}")
        self.root.title("Map Viewer")

        # Entry for source location
        self.source_entry = tk.Entry(self.root, width=30)
        self.source_entry.grid(row=0, column=0, padx=10, pady=10)

        # Entry for destination location
        self.destination_entry = tk.Entry(self.root, width=30)
        self.destination_entry.grid(row=0, column=1, padx=10, pady=10)

        # Button to update the map
        update_button = tk.Button(self.root, text="Update Map", command=self.update_map)
        update_button.grid(row=0, column=2, padx=10, pady=10)

        # Create map widget
        self.map_widget = tkintermapview.TkinterMapView(self.root, width=800, height=600, corner_radius=0)
        self.map_widget.grid(row=1, column=0, columnspan=3)

        # Initialize source_coords and destination_coords
        self.source_coords = None
        self.destination_coords = None

        self.update_map()

    def get_coordinates(self, location_name):
        geolocator = Nominatim(user_agent="my_geocoder")
        location = geolocator.geocode(location_name)
        if location:
            return location.latitude, location.longitude
        else:
            raise ValueError("Try again")

    def update_map(self):
        # Get coordinates from the entry widgets
        try:
            source_coords = self.get_coordinates(self.source_entry.get())
            destination_coords = self.get_coordinates(self.destination_entry.get())
        except ValueError as e:
            print(f"Error: {e}")
            return

        # Set source and destination coordinates as class attributes
        self.source_coords = source_coords
        self.destination_coords = destination_coords

        # Save coordinates to a JSON file
        coordinates_data = {
            "source_coords": {
                "latitude": source_coords[0],
                "longitude": source_coords[1]
            },
            "destination_coords": {
                "latitude": destination_coords[0],
                "longitude": destination_coords[1]
            }
        }

        with open("MapViewImp/Data_Save_here/coordinates.json", "w") as json_file:
            json.dump(coordinates_data, json_file)

        # Calculate the midpoint between source and destination for centering the map
        center_coords = (
            (source_coords[0] + destination_coords[0]) / 2,
            (source_coords[1] + destination_coords[1]) / 2
        )

        # Set the initial view to the center of the coordinates
        self.map_widget.set_position(center_coords[0], center_coords[1])
        self.map_widget.set_zoom(10)

        # Create a Folium map
        m = folium.Map(location=center_coords, zoom_start=10)
        folium.Marker(location=source_coords, icon=folium.Icon(color='green', icon='check', prefix='fa')).add_to(m)
        folium.Marker(location=destination_coords, icon=folium.Icon(color='red', icon='check', prefix='fa')).add_to(m)

        # Save the map to an HTML file
        m.save("my_map.html")

        return source_coords, destination_coords

# Function to retrieve source and destination coordinates
def get_coords():
    return MapViewerApp.source_coords, MapViewerApp.destination_coords

if __name__ == "__main__":
    root = tk.Tk()
    app = MapViewerApp(root)
    root.mainloop()
