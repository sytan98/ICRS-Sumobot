# ICRS-Sumobot

## Overview of script:

### C scripts
infrared.h --> Contains the class of infrared sensors with instance methods such as read() to read input data from interrupt pins.

distance.h --> Contains the class of ultrasound sensors with instance methods such as read() to read input data from uart pins.

opticalflow.h -> Contains the class of optical flow sensors with instance methods such as read() to read input data from ? pins.

main.c --> Main script that imports ir sensor libraries and ultrasound sensor libraries to do various actions which can be broken down into
            1. Staying alive (What to do when sumobot hits line)
            2. Attacking mode (Track ultrasound readings and go towards direction of least distance)
            3. Defending mode (Constantly move in a star movement and evade when opponent approaches)

main_full_template.c -> Template file to generate formatted_main.c 

### Python scripts
format_main_c_file.py --> Takes in a template file and main.c file, and combines both

## How to use:
If working on main, *do not* edit main_full_template.c! Instead, work on main.c only and edit code as demarcated

1. Download STM32CubeMX

Before programming your application, you have to write an start up file, initialize the clock tree, the peripherals, etc. Those tasks are daunting and repeated for every projects. Most of the Arduino fans don’t experience this because that process is done and transparent to them. But configuring the peripherals is one of the most important parts of the microcontroller because you will have the full control of your micro, you will expext its behaviors. Luckily, most vendors provide a graphical tool to help us doing the configuration, and that tool will generate the code to a project with IDEs (mentioned above ) of choice. These tools can be a standalone software like STM32CubeMx from ST.

2. Configure Pins and Clock Configuration

Pin assignments using STM32CubeMX and use clock configuration to control clocking speed.

3. Generate Code

Generate code and open it in an IDE (recommended: Keil uVision5)
```
HAL_Peripheral_Action(parameters);
/* for example */
HAL_GPIO_Toggle(GPIO_Port, GPIO_Pin); 
HAL_UART_Transmit(parameters);
```
4. Peripheral Libraries

There are many ways to program a microcontroller. The most respected way (effective or not is another story) is doing everything from scratch, program registers directly, plus using assembly. The rest will likely program in C, using kinds of libraries or SDKs provided by vendor.
Hardware abstraction layer (HAL) provides us a high level, high abstraction library. It means the library is common for every STM32 family. When using this library, you will see that, the work flow, functions, processes are the same for every microcontroller, which means you will move away a bit further from the hardware world.

## Useful links:
Link about how to use branches: https://confluence.atlassian.com/bitbucket/branching-a-repository-223217999.html
How to program STM32: https://medium.com/microcontroller-for-not-so-dummy/how-to-program-an-stm32-c3ea2f7c8f8a?
https://simonmartin.ch/resources/stm32/dl/
