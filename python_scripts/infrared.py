#import RPi.GPIO as IO 
import wiringpi2 as wiringpi  
import time 

"""
Input:
1 or 0 (true or false)
Interrupt pin says if any IR sensor is triggered
UART pin says which IR sensor is triggered
e.g. IR sensors labelled clockwise from front

Output:
Heading (where it is facing) (0 to 359)
Angle (direction in which we want to move relative to heading) (0 to 359)
Velocity in angle (0 to 255)
[heading,angle,velocity]

Will output two arrays
1) Move away from triggered sensor direction
2) Spin towards centre
"""
class infrared:

# Initializer / Instance Attributes
    def __init__(self, triggerpin, uartpin, numbers):
        self.triggerpin = triggerpin
        self.uartpin = uartpin
        self.numbers = numbers

#reading input function
    def readheading(self):
        wiringpi.wiringPiSetupGpio()  
        wiringpi.pinMode(self.pin, 0)
        ser = wiringpi.serialOpen('/dev/serial0', 115200)
        data = []
        while True:
            data.append(wiringpi.serialGetchar(ser))
            print(wiringpi.serialGetchar(ser))
            sleep(0.03)
        return data

    #get perpendicular angle (0-359)
    def calculate():
        if (sensor <= 4):
            perpendicular = (sensor * 45 - 22.5) + 180
        elif (sensor > 4):
            perpendicular = (sensor * 45 - 22.5) - 180
        return perpendicular

    def check(self):
        return "{} and {}".format(self.triggerpin, self.numbers)
    
    

"""
#setup pins
UART_pin=15
trigger=2
IO.setup(UART_pin,IO.IN) # UART pin
IO.setup(trigger,IO.IN) # Trigger pin

#get values
sensor = IO.input(UART_pin)
triggered = IO.input(trigger)

#get perpendicular angle (0-359)
#Perpendicular angle calculated from angle between front and sensor.
# There is an error in this calculation (won't be exactly perpendicular)
if (sensor <= 4):
    perpendicular = (sensor * 45 - 22.5) + 180
elif (sensor > 4):
    perpendicular = (sensor * 45 - 22.5) - 180

#Generate output
if (triggered==True):
    IR_output_1 = [0,perpendicular,255] # Move away from boundary
    IR_output_2 = [perpendicular,0,255] # Rotate to perpendicular angle 
# Could this perpendicular angle change after moving backwards? e.g. being pushed...?
# We could use computer vision at this point to make sure we don't rotate away from robot and instead rotate until it is facing the opponent.
    
"""