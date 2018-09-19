#!/usr/bin/python

from phue import Bridge
import time

b = Bridge('10.0.1.250')

# If the app is not registered and the button is not pressed, press the 
# button and call connect() (this only needs to be run a single time)
b.connect()

b.set_light('Forest1', {'bri': 254, 'sat': 254, 'xy': [0.1938, 0.6821]})
b.set_light('Forest2', {'bri': 254, 'sat': 254, 'xy': [0.1938, 0.6821]})
time.sleep(3)
b.set_light('Forest1', {'bri': 254, 'sat': 254, 'xy': [0.1545, 0.0971]})
b.set_light('Forest2', {'bri': 254, 'sat': 254, 'xy': [0.1545, 0.0971]})
time.sleep(3)
b.set_light('Forest1', {'bri': 254, 'sat': 254, 'xy': [0.1938, 0.6821]})
b.set_light('Forest2', {'bri': 254, 'sat': 254, 'xy': [0.1545, 0.0971]})
