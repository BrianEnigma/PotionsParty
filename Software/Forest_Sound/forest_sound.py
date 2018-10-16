#!/usr/bin/env python

import os
import random
import sys
import threading
import time

# 0 = no adjustment, 1200 = +12dB, can even go negative
base_volume_adjustment = 0
effects_volume_adjustment = 0
effects_delay_min = (3 * 60)
effects_delay_max = (5 * 60)

def play_base():
    while True:
        cmd = "omxplayer -o local --vol %d base.mp3" % base_volume_adjustment
        print("(Re)starting base mp3\n")
        print("   --- %s\n" % cmd)
        rc = os.system(cmd)
        if 0 != rc:
            sys.exit(1)

def pick_effect():
    effects_files = [f for f in os.listdir("./Effects/") if f.endswith(".mp3") and os.path.isfile(os.path.join("./Effects/", f))]    
    #print(effects_files)
    return effects_files[random.randrange(0, len(effects_files))]

def play_effects():
    while True:
        effect_file = pick_effect()
        cmd = "omxplayer -o local --vol %d 'Effects/%s'" % (effects_volume_adjustment, effect_file)
        print("Playing effect mp3 %s\n" % effect_file)
        print("   --- %s\n" % cmd)
        rc = os.system(cmd)
        if 0 != rc:
            sys.exit(1)
        delay_amount = random.randrange(effects_delay_min, effects_delay_max)
        print("Effect thread delaying %d seconds\n" % delay_amount)
        time.sleep(delay_amount)

random.seed()
threads = []
threads.append(threading.Thread(target=play_base))
threads.append(threading.Thread(target=play_effects))
for t in threads:
    t.start()
