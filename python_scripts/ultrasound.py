import wiringpi2 as wiringpi  
import time

class ultrasound:

# Initializer / Instance Attributes
	def __init__(self, uartpin, numbers):
		self.uartpin = uartpin
		self.numbers = numbers

	#reading input function	
	def read(self):
		wiringpi.wiringPiSetupGpio()  
		wiringpi.pinMode(self.uartpin, 0)
		ser = wiringpi.serialOpen('/dev/serial0', 115200)
		data = []
		while True:
			data.append(wiringpi.serialGetchar(ser))
			print(wiringpi.serialGetchar(ser))
			sleep(0.03)
		return data

	def check(self):
		return "{} and {}".format(self.uartpin, self.numbers)