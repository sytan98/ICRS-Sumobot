import RPi.GPIO as GPIO
import time

class ultrasound():
	
#detect function
# GPIO port numbers  
import wiringpi2 as wiringpi  
wiringpi.wiringPiSetupGpio()  
wiringpi.pinMode(15, 0) # sets GPIO 25 to input  

ser = wiringpi.serialOpen('/dev/serial0', 115200)

data = []
while True:
    data.append(wiringpi.serialGetchar(ser))
    print(wiringpi.serialGetchar(ser))
    sleep(0.03)


def detect(trig, ech):
	time.sleep(.01)
	#send out a 10 microsecond signal
	GPIO.output(trig,GPIO.HIGH)
	time.sleep(.00001)
	GPIO.output(trig,GPIO.LOW)
	#Initiate Signaloff and Starttime.  Starttime is used in case the Rpi misses the high signal.  
	#We don't want the Rpi to stay in a loop for more than .1 seconds waiting for the high signal.
	starttime=time.time()
	signaloff=time.time()
	#check the time and record it as signaloff.  This is when the echo input goes high (to 1)
	while GPIO.input(ech)==0 and time.time() < starttime+.1:
		signaloff=time.time()

	#check the time when you hear a signal back.
	#We don't want the RPi to be in this loop for more than .1 seconds.
	signalon=time.time()
	while GPIO.input(ech)==1 and time.time() < signaloff+.1:
		signalon=time.time()

	#take the difference then multiply by a constant (17000) to calculate distance in cm.
	timepassed=signalon-signaloff
	distance=timepassed*17000
	print distance
	return

#RPi board pin numbers
GPIO.setmode(GPIO.BOARD)

#setup BPIO output channel and input channel
in1=38 #Receive echo signal
out1=40 #send ping out
GPIO.setup(out1, GPIO.OUT)
GPIO.setup(in1, GPIO.IN)

#check proximity 1000 times
for i in range(0,1000):
	time.sleep(.01)
	detect(out1, in1)

GPIO.cleanup()