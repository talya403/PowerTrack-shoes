import folium
from folium.plugins import MarkerCluster
import webbrowser
import os
import serial
import re
import time

# Replace 'COM_PORT' with your actual serial port (e.g., 'COM3' on Windows or '/dev/ttyUSB0' on Linux)
SERIAL_PORT = '/dev/cu.usbserial-0001'
BAUD_RATE = 115200

# Initialize serial connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

# Initialize map
m = folium.Map(location=[0, 0], zoom_start=2)
marker_cluster = MarkerCluster().add_to(m)

# Save initial map
map_file = 'map.html'
m.save(map_file)

# Open the map in the default web browser
webbrowser.open('file://' + os.path.realpath(map_file))


def read_coordinates():
    while True:
        line = ser.readline().decode('utf-8')
        match = re.search(r'received packet "(.+?)" with Rssi', line)
        if match:
            coords = match.group(1)
            lat, lon = map(float, coords.split(','))
            return lat, lon


if __name__ == "__main__":
    while True:
        # lat, lon = 31.776154,35.198273
        lat, lon = read_coordinates()
        print("Latitude: {}, Longitude: {}".format(lat, lon))

        # Add new marker to the map
        folium.Marker(location=[lat, lon], popup="SOS call was received from Lat: {}, Lon: {}".format(lat, lon)).add_to(marker_cluster)

        # Save updated map
        m.save(map_file)

        # Pause for a short period to simulate real-time update (optional)
        time.sleep(30)
        lon += 0.1
        lat += 0.1
