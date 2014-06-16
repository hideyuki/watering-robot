#!/usr/bin/env python
#coding: utf-8

import serial
import time

#SERIAL_DEV = '/dev/tty.usbmodem1411'
SERIAL_DEV = '/dev/ttyACM0'
SERIAL_BAUDRATE = 9600

s = serial.Serial(SERIAL_DEV, SERIAL_BAUDRATE)

# wait for preparing the Arduino
time.sleep(3.0)

s.write("m\r\n")
moisture = int(s.readline())

time.sleep(1.0)

s.write("t\r\n")
temperature = int(s.readline())

print "Moisture: " + moisture
print "Temperature: " + temperature

