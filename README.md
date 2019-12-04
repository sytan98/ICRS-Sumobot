# ICRS-Sumobot

## Overview of script:

infrared.py --> Contains the class of infrared sensors with instance methods such as read() to read input data from interrupt pins.

ultrasound.py --> Contains the class of ultrasound sensors with instance methods such as read() to read input data from uart pins.

output.py --> To handle sending of outputs from raspberry pi to microcontroller with actions to be taken by robot. Includes instance methods such as movefoward() and rotate(). It sends out output in the form of an array of [heading,angle,velocity]

main.py --> Main script initiates output class.
            Main script that imports ir sensor class and ultrasound sensor class to do various actions which can be broken down into
            1. Staying alive (What to do when sumobot hits line)
            2. Attacking mode (Track ultrasound readings and go towards direction of least distance)
            3. Defending mode (Constantly move in a star movement and evade when opponent approaches)

computervision.py --> Handles camera inputs and does object detection

Link about how to use branches: https://confluence.atlassian.com/bitbucket/branching-a-repository-223217999.html
