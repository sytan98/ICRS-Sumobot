# ICRS-Sumobot

## Overview of script:

input.py --> To handle inputs from microcontroller with sensor data via GPIO

output.py --> To handle sending of outputs from raspberry pi to microcontroller with actions to be taken by robot.

main.py --> Main script that imports ir sensor class and ultrasound sensor class to do various actions which can be broken down into
            1. Staying alive (What to do when sumobot hits line)
            2. Attacking mode (Track ultrasound readings and go towards direction of least distance)
            3. Defending mode (Constantly move in a star movement and evade when opponent approaches)

infrared.py --> Contains the class of infrared sensors

ultrasound.py --> Contains the class of ultrasound sensors

computervision.py --> Handles camera inputs and does object detection
