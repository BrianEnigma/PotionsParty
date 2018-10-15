#!/bin/bash

PID=`ps ax|grep forest_sound.py | grep -v grep | sed 's/^ *//' | cut -d ' ' -f 1`

kill $PID
killall omxplayer
killall omxplayer.bin

