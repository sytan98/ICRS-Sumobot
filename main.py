import time
import logging

#from infrared import infrared
from ultrasound import ultrasound
#from output import output


class mainframe:

    def __init__(self):
        try:
            self.us = ultrasound()
            # self.ir = infrared()
        except FileNotFoundError:
            print("Serial port not found")

    def self_checks(self):
        if hasattr(self, 'us'):
            return True
        else:
            return False


def main():
    # Instantiate ir and us objects. We will read from these objects
    frame = mainframe()

    # Main loop to be run
    if frame.self_checks():
        try:
            while True:
                time.sleep(1.0)
                print(frame.us.read())
                print(time.time())
        except KeyboardInterrupt:
            print("Keyboard interrupt received")
            # Do some graceful shutdown, e.g. save files etc
    else:
        print("Setup failed! Exiting now...")


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
