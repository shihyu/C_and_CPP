import serial
import sys
import time
import traceback

def workWithPort(devName, f):
  def acquireSerial(devName):
    count = 50
    while 0 < count:
      try:
        return serial.Serial(port = devName)
      except:
        traceback.print_exc(file=sys.stdout)
      time.sleep(3)
      count -= 1
    raise Exception("Cannot find device %s." % devName)

  ser = acquireSerial(devName)
  ser.open()
  try:
    f(ser)
  finally:
    ser.close()  

def dummyRead(ser):
  ser.write('\r\n')
  time.sleep(1)
  ser.flushInput()
