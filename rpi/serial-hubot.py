#coding: utf-8

import serial

SERIAL_DEV = '/dev/tty.usbmodem1411'
SERIAL_BOUDRATE = 57600

s = serial.Serial(SERIAL_DEV, SERIAL_BOUDRATE)

while True:
      print s.readline()

