import serial
import gmplot
import pandas as pd
import os, sys, string
import asyncio
serialPort = serial.Serial(port = "COM3", baudrate ="9600", bytesize = 8, timeout = 2, stopbits = serial.STOPBITS_ONE)
lat = []
lon = []
flag=1
counter = 0
data=""
data1=""


async def hey ():   
    while(not(serialPort.in_waiting > 0)):
        data = input()
        serialPort.write(data.encode('Ascii'))
        await asyncio.sleep(1)


asyncio.run(hey())
while(1):
    if (serialPort.in_waiting > 0):
    #    counter =counter+1
        data = serialPort.readline()
        data = data.decode('Ascii')
        if(flag==1):
            if(data =='E'):
                break  
            data1 = data[0:-2]
            lat.append(float(data1))
            print(data1)
            flag = 0
        elif(flag == 0):
            data1 = data[0:-2]
            lon.append(float(data1))
            print(data1)
            flag  = 1

print(lat)
print(lon)

# Create the map plotter:
gmap = gmplot.GoogleMapPlotter(lat[0], lon[0], 18, apikey="AIzaSyB6k3QlQZn73MHIgIHez7sSYIsrJ8hH1Nk")

gmap.scatter(lat, lon, 'green', size=2, marker=False)
gmap.plot(lat,lon,'white',edge_width=5)

# Mark a hidden gem:
gmap.marker(lat[0], lon[0], color='blue')
gmap.marker(lat[-1], lon[-1], color='red')

# Draw the map:
gmap.draw('mapp.html')
os.system("mapp.html")
