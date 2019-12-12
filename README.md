# ICRS-Sumobot

## Overview of script:

### C scripts
infrared.c --> Contains the class of infrared sensors with instance methods such as read() to read input data from interrupt pins.

distance.c --> Contains the class of ultrasound sensors with instance methods such as read() to read input data from uart pins.

struct ultrasound{
            int name;
            float distance;
}

ultrasound read_distance(){
            returns the name of the ultrasound that is closest to the enemy and the distance
}

opticalflow.c -> Contains the class of optical flow sensors with instance methods such as read() to read input data from ? pins.

main.c --> Main script that imports ir sensor libraries and ultrasound sensor libraries to do various actions which can be broken down into
            1. Staying alive (What to do when sumobot hits line)
            2. Attacking mode (Track ultrasound readings and go towards direction of least distance)
            3. Defending mode (Constantly move in a star movement and evade when opponent approaches)

main_full_template.c -> Template file to generate formatted_main.c 

### Python scripts
format_main_c_file.py --> Takes in a template file and main.c file, and combines both

## How to use:
If working on main, *do not* edit main_full_template.c! Instead, work on main.c only and edit code as demarcated

## Useful links:
Link about how to use branches: https://confluence.atlassian.com/bitbucket/branching-a-repository-223217999.html
