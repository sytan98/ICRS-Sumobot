import serial
from time import sleep


class ultrasound:

    def __init__(self, serial_port="/dev/serial0",
                 baud_rate=115200,
                 sleep_time=0.03):
        """
        Args:
            serial_port (str): The location of serial port
                               Defaults to "/dev/serial0"
            baud_rate (int): Rate information is read from control side
            sleep_time (float): Time between reads(?)

        Raises:
            FileNotFoundError : If serial port cannot be found
        """
        self.change_baud_rate(baud_rate)
        self.serial_port = serial_port

        try:
            self.ser = serial.Serial(serial_port, baud_rate)
        except serial.serialutil.SerialException:
            raise FileNotFoundError("Serial port not found")

    # Reading input function
    def read(self):
        """Gets and prints the spreadsheet's header columns

        Returns:
            ultrasound: a list of ints representing
        """
        received_data = self.ser.read()              # Read serial port
        sleep(self.sleep_time)
        data_left = self.ser.inWaiting()             # Check for remaining byte
        received_data += self.ser.read(data_left)

        ultrasound = []
        for i in range(0, 17, 2):
            ultrasound.append((int(received_data[i] << 8)
                               + int(received_data[i+1])))

        return ultrasound

    def change_baud_rate(self, new_baud_rate):
        """Checks baud_rate is valid then changes attribute"""
        if self.baud_rate_is_in_range:
            self.baud_rate = new_baud_rate
        else:
            raise ValueError("Invalid baud rate! Must be >0 and <250000")

    def change_sleep_time(self, new_sleep_time):
        """Changes sleep time in seconds"""
        self.sleep_time = new_sleep_time

    def sensor_is_online(self):
        """Check serial port is open"""
        return self.ser.Open()

    def baud_rate_is_in_range(baud_rate_to_check):
        """Checks that baud rate is between 0 and 250000 and is int"""
        if isinstance(baud_rate_to_check, int):
            return (baud_rate_to_check < 0) or (baud_rate_to_check >= 250000)
        else:
            return False
