import time
import sys

# from infrared import infrared
from ultrasound import ultrasound
# from output import output


class mainframe:

    def __init__(self):
        self.__sensors_online_status__ = {"ultrasound": False,
                                          "infrared": False}
        # TODO(jqp): Implement init for infrared and other sensors,
        #            possibly differentiating compass and ultrasound.
        #            Also need to find a way to initialise each sensors
        #            independently without one failure leading to halt in
        #            function.
        #            Maybe also include output device status
        try:
            self.us = ultrasound()
            # self.ir = infrared()
        except FileNotFoundError:
            print("Error: file not found")  # TODO(jqp): Improve error message

    def self_checks(self):
        """Updates internal dict to reflect status"""
        if hasattr(self, "us"):
            self.__sensors_online_status__["ultrasound"] = True
        else:
            return False

    def return_sensors_online(self):
        """Properly formats sensor status in a list"""
        return ["{} - {}".format(k, v)
                for k, v in self.__sensors_online_status__.items()]

    def shutdown(self):
        pass
        # TODO(jqp) : Close any open files and/or ports, save things, etc etc


def main():
    # Instantiate mainframe object which contains us and ir instances
    print("\n-----INITIALISING SENSORS-----\n")
    frame = mainframe()
    frame.self_checks()

    # Confirms with user the status of sensors
    print("\nThe following sensors are online:")
    [print(s) for s in frame.return_sensors_online()]
    user_input = input("\nDo you want to continue? [Y/N] ")

    # Forces user to answer properly
    while user_input not in ["Y", "N"]:
        user_input = input("Continue? Type in only [Y/N] ")
    if user_input == "N":
        # frame.shutdown()
        sys.exit("\n-----TERMINATING-----\n")

    # Main loop to be run
    try:
        while True:
            time.sleep(1.0)
            print(frame.us.read())
            print(time.time())
    except KeyboardInterrupt:
        print("Keyboard interrupt received")
        # frame.shutdown()


if __name__ == '__main__':
    main()
