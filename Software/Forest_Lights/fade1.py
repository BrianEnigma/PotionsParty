#!/usr/bin/python

from phue import Bridge
import pprint
import time

TRANSITION_SEC = 5
DELAY_SEC = 120

COLORS = [
    {
        'on': True,
        'bri': 254,
        'sat': 254,
        'xy': [0.1938, 0.6821],
        'transitiontime': TRANSITION_SEC * 10
    },
    {
        'on': True,
        'bri': 254,
        'sat': 254,
        'xy': [0.1545, 0.0971],
        'transitiontime': TRANSITION_SEC * 10
    }
]
index = 0



while True:
    b = Bridge('10.0.1.250')
    
    # If the app is not registered and the button is not pressed, press the 
    # button and call connect() (this only needs to be run a single time)
    b.connect()
    
    alt_index = (index + 1) % 2
    
    b.set_light('Forest1', COLORS[index])
    b.set_light('Forest2', COLORS[index])
    time.sleep(DELAY_SEC)

    b.set_light('Forest1', COLORS[index])
    b.set_light('Forest2', COLORS[alt_index])

    index = (index + 1) % 2
    time.sleep(DELAY_SEC)
