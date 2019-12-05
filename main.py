import time
#from infrared import infrared
from ultrasound import ultrasound
#from output import output

def main():

    # Instantiate ir and us objects. We will read from these objects
    us = ultrasound()

    # Pre-checks before starting main loop
    assert us.sensor_is_online()

    # Main loop to be run
    try:
        while True:
            time.sleep(1.0)
            print(us.read())
    except KeyboardInterrupt:
        print("Keyboard interrupt received")
        # Do some graceful shutdown instead of immediately crashing the program


if __name__ == '__main__':
    main()


"""
ir = infrared(triggerpin=20,
              uartpin=15,
              numbers=8)
us = ultrasound(uartpin=15,
                numbers=8)

test = ir.check()
test2 = us.check()
print(test)
print(test2)"""
