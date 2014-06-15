#!/usr/bin/env python
#coding: utf-8

import serial
import time

SERIAL_DEV = '/dev/tty.usbmodem1411'
SERIAL_BAUDRATE = 57600

s = serial.Serial(SERIAL_DEV, SERIAL_BAUDRATE)

# wait for preparing the Arduino
time.sleep(3.0)

while True:
  time.sleep(1.0)
  s.write("m\r\n")
  val = int(s.readline())

