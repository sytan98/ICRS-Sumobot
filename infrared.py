import RPi.GPIO as GPIO 
import time 
# check function 
def check(lfld):
    time.sleep(.3)
    print GPIO.input(lfld)
    return 

# to use Raspberry Pi board pin numbers 
GPIO.setmode(GPIO.BOARD) 

# set up GPIO output channel
lfld = 15  #left front line detector

GPIO.setup(lfld, GPIO.IN)
# check the sensor 1000 times
for i in range(0,1000): 
    check(lfld) 

GPIO.cleanup()

#hi