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
