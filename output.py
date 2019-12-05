import wiringpi2 as wiringpi  

class output():
    # left turn
    def leftturn():
        # right wheel
        rwpin = 32
        # left wheel
        lwpin = 31
        GPIO.output(rwpin, GPIO.HIGH)
        GPIO.output(lwpin, GPIO.HIGH)
        time.sleep(.00165)
        GPIO.output(rwpin, GPIO.LOW)
        GPIO.output(lwpin, GPIO.LOW)
        time.sleep(.02)
        return


    # straight
    def straight():
        for i in range(0, 5):
            # right wheel
            rwpin = 32
            # left wheel
            lwpin = 31
            GPIO.output(rwpin, GPIO.HIGH)
            GPIO.output(lwpin, GPIO.HIGH)
            time.sleep(.0013)
            GPIO.output(rwpin, GPIO.LOW)
            time.sleep(.0004)
            GPIO.output(lwpin, GPIO.LOW)
            time.sleep(.02)
        return
