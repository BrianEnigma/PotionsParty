#!/usr/bin/python

import pprint
from phue import Bridge

b = Bridge('10.0.1.250')

# If the app is not registered and the button is not pressed, press the 
# button and call connect() (this only needs to be run a single time)
b.connect()

lights = b.lights

pp = pprint.PrettyPrinter(indent=4)
pp.pprint(lights)

# Print light names
for l in lights:
    print(l.name)
    pp.pprint(l)
