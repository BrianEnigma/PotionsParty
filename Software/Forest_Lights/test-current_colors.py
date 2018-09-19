#!/usr/bin/python

from phue import Bridge
import pprint

b = Bridge('10.0.1.250')

# If the app is not registered and the button is not pressed, press the 
# button and call connect() (this only needs to be run a single time)
b.connect()

data = b.get_light('Forest1')
pp = pprint.PrettyPrinter(indent=4)
pp.pprint(data['state'])

# {   u'alert': u'select',
#     u'bri': 254,
#     u'colormode': u'xy',
#     u'ct': 153,
#     u'effect': u'none',
#     u'hue': 24432,
#     u'mode': u'homeautomation',
#     u'on': True,
#     u'reachable': True,
#     u'sat': 254,
#     u'xy': [0.1938, 0.6821]}

data = b.get_light('Forest2')
pp = pprint.PrettyPrinter(indent=4)
pp.pprint(data['state'])

# {   u'alert': u'none',
#     u'bri': 254,
#     u'colormode': u'xy',
#     u'ct': 153,
#     u'effect': u'none',
#     u'hue': 45472,
#     u'mode': u'homeautomation',
#     u'on': True,
#     u'reachable': True,
#     u'sat': 254,
#     u'xy': [0.1545, 0.0971]}
