import RPi.GPIO as GPIO
import time


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


# check proximity function
def check(trig, ech):
    time.sleep(.01)
    GPIO.output(trig, GPIO.HIGH)
    time.sleep(.00001)
    GPIO.output(trig, GPIO.LOW)
    # Initiate Signaloff and Starttime.  Starttime is used in case the Rpi
    # misses the high signal.
    # We don't want the Rpi to stay in a loop for more than .1 seconds
    # waiting for the high signal.

    starttime = time.time()
    signaloff = time.time()
    # Check the time and record it as signaloff.
    # This is when the echo input goes high (to 1)
    while GPIO.input(ech) == 0 and time.time() < starttime + .1:
        signaloff = time.time()

    # check the time when you hear a signal back.
    # We don't want the RPi to be in this loop for more than .1 seconds.
    signalon = time.time()
    while GPIO.input(ech) == 1 and time.time() < signaloff + .1:
        signalon = time.time()

    # Take the difference then multiply by a constant (17000)
    # to calculate distance in cm.
    timepassed = signalon-signaloff
    distance = timepassed*17000
    print(distance)

    if distance >= 70:
        leftturn()
    else:
        straight()
    return


def backleft():
    for i in range(0, 100):
        # right wheel
        rwpin = 32
        # left wheel
        lwpin = 31
        GPIO.output(rwpin, GPIO.HIGH)
        GPIO.output(lwpin, GPIO.HIGH)
        time.sleep(.0013)
        GPIO.output(lwpin, GPIO.LOW)
        time.sleep(.0003)
        GPIO.output(rwpin, GPIO.LOW)
        time.sleep(.02)
    return


def backright():
    for i in range(0, 100):
        # right wheel
        rwpin = 32
        # left wheel
        lwpin = 31
        GPIO.output(rwpin, GPIO.HIGH)
        GPIO.output(lwpin, GPIO.HIGH)
        time.sleep(.00135)
        GPIO.output(lwpin, GPIO.LOW)
        time.sleep(.0003)
        GPIO.output(rwpin, GPIO.LOW)
        time.sleep(.02)
    return


def blink(pin):
    GPIO.output(pin, GPIO.HIGH)
    time.sleep(.2)
    GPIO.output(pin, GPIO.LOW)
    time.sleep(.2)


if __name__ == '__main__':
    # to use Raspberry Pi board pin numbers
    GPIO.setmode(GPIO.BOARD)
    # set up GPIO output channel for ultrasonic sensor
    in1 = 38
    out1 = 40
    GPIO.setup(out1, GPIO.OUT)
    GPIO.setup(in1, GPIO.IN)

    # LED
    led = 37
    GPIO.setup(led, GPIO.OUT)

    # set up GPIO switch channel
    sw = 33
    GPIO.setup(sw, GPIO.IN)

    # wheels/servos
    GPIO.setup(31, GPIO.OUT)
    GPIO.setup(32, GPIO.OUT)

    # line detector channel
    lfld = 15
    rfld = 16

    GPIO.setup(lfld, GPIO.IN)
    GPIO.setup(rfld, GPIO.IN)

    go = False

    while True:
        print(go)
        if GPIO.input(sw) == 1:
            go = not go

            time.sleep(1)

        if not go:
            blink(led)
        else:
            GPIO.output(led, GPIO.HIGH)
            if GPIO.input(lfld) == 0:
                backleft()
            if GPIO.input(rfld) == 0:
                backright()
            check(out1, in1)
