#!/usr/bin/env python

from BaseHTTPServer import BaseHTTPRequestHandler,HTTPServer
import pprint
import re
import SocketServer

from phue import Bridge

BRIDGE_IP = '10.0.1.250'

MY_HTTP_PORT = 8000

lights_to_animate = [ \
        'Desk',
        'Chair',
        'Sofa',
        'Dining Room',
        'Accent',
        'Bookshelf'
        ]

initial_state = {}

def save_state(initial_state):
    bridge = Bridge('10.0.1.250')
    bridge.connect()

    for light_name in lights_to_animate:
        data = bridge.get_light(light_name)
        initial_state[light_name] = data['state']

def restore_state(initial_state):
    bridge = Bridge('10.0.1.250')
    bridge.connect()
    for light_name in lights_to_animate:
        data = initial_state[light_name]
        bridge.set_light(light_name, {'bri': data['bri'], 'sat': data['sat'], 'xv': data['xv']})

class HTTPRESTRequestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        return
    def do_GET(self):
        if None != re.search('/api/activate', self.path):
            print("ACTIVATE!")
        else:
            print("IGNORING: " + self.path)
        return

handler = HTTPRESTRequestHandler
httpd = SocketServer.TCPServer(('', MY_HTTP_PORT), handler)
httpd.serve_forever()

