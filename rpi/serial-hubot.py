#!/usr/bin/env python
#coding: utf-8

import serial
import time
import os
import urllib

#SERIAL_DEV = '/dev/tty.usbmodem1411'
SERIAL_DEV = '/dev/ttyACM0'
SERIAL_BAUDRATE = 9600

s = serial.Serial(SERIAL_DEV, SERIAL_BAUDRATE)

# wait for preparing the Arduino
time.sleep(2.0)

s.write("m\r\n")
moisture = int(s.readline())

time.sleep(0.1)

s.write("t\r\n")
temperature = int(float(s.readline()))

print "Moisture: " + str(moisture)
print "Temperature: " + str(temperature)

url = os.environ['HUBOT_API_BASE_URL'] + "/hubot/plant0"
params = urllib.urlencode({'moisture': moisture, 'temperature': temperature})
urllib.urlopen(url, params)

