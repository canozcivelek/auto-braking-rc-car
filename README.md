# Auto Braking RC Car

## Project Description & Objective

This project was created to replicate the safety feature called autonomous emergency braking (AEB) implemented in todays cars.
Basically, a radar mounted in the front of the car constantly scans the road ahead, and when a collision is imminent with driver 
not reacting to the situation, this system takes over and applies the brakes to prevent collisions or reduce the impact. In this project, 
an ultrasonic sensor is used to constantly measure distance ahead, and based on the current speed, it engages brakes to stop the car before
hitting any obstacle. A Hall effect sensor is used to measure speed, and this data is used to determine how far the car needs to apply brakes to avoid a collision.

#### [**Demo Video**](https://youtu.be/oikVViVeHMs) (Click to see the full video)

![](https://imgur.com/hMaiTxC.gif)

## Deployment
This project isn't a software project since there is hardware involved too. Braking this project down to (1)software and (2)hardware would make sense to get a better idea of how the code works and how to get it up and running on any machine.

#### Prerequisites
To successfully run this project, it is required to have the following software and hardware components installed:
* Arduino IDE (https://www.arduino.cc/en/main/software)
* Arduino UNO microcontroller
* Breadboard
* Ultrasonic sensor (PL-1605)
* Hall effect sensor (KY-003)
* Magnet (preferrably neodymium)
* Cables
* External power source for Arduino and another one for the servo motor

#### Dependencies and Environment
It should be noted that this project was developed on a Microsoft Windows 10 (64 Bit) machine, however, it should work on other platforms too with minor tweaks here and there. Servo library should be installed for Arduino to control the servo motor on the RC car.

#### Software
Clone this repository by launching the command prompt and changing to your desired directory. Then type 
```
git clone https://github.com/canozcivelek/auto-braking-rc-car.git
```
Having already satisfied the prerequisites, software side of this project is now completed.

#### Hardware
As mentioned in the prerequisites section, you'll need an Arduino UNO, a breadboard, an ultrasonic sensor, a Hall effect sensor, a magnet, some cables end external batteries. Place the ultrasonic sensor at the very front of the car and connect its trig pin to Arduino pin 9, echo pin to Arduino pin 10, the GND pin to Arduino GND and 5V pin to Arduino 5V. As for the Hall effect sensor, connect its 5V and GND pins to Arduino 5V and GND, and its signal pin to Arduino pin 2. Finally, make connections from servo motor that controls the brakes to pin 5 for signal, and other two for 5V and GND again. To power the Arduino, use an external 9V battery. It turns out that servo should be powered separately as it requires too much power and it is highly recommended not to share the power source with Arduino. To power the servo motor, I used a 6V NiMh battery and made the following connections: battery GND (black cable) to Arduino GND, battery + (red cable) to servo red cable, servo digital (white) to Arduino pin 5.

[This](Pictures/setup.jpg) is how my setup looks like

[And this](Pictures/wheel.jpg) is a close up of how I used the Hall effect sensor

![Another Look](Pictures/slomoDemo.gif)

---

## How the Code Works
Upon inspecting [autoBrake.ino](autoBrake) file, it's first seen including the _servo.h_ library needed to control servo motor (brakes). Then variable definitions are made to be used by the sensors. Moving on to the loop function, RPM measuring is done with Hall effect sensor picking up magnetic field and the rate at which magnetic field is detected is then converted to revolutions per minute (RPM). Then distance is measured as ultrasonic sensor sends an ultrasound that travels through and bounces off of a surface back to the sensor. This _duration_ variable is then multiplied by speed of sound and divided by 2 to reveal the actual distance in centimeters.
The rest of the code consists of if checks to monitor the speed and distance ahead, and applying brakes when necessary. As monitored speed increases, braking distance also increases as there needs to be a greater gap to come to a full stop before a collision can occur. All the distance and speed combinations are tested several times and suits best with this particular setup. They are subject to change to whatever suits best for any other setup.

## Important Notes
It should be noted that this particular model is gas powered and during development and testing of this project, the car's engine is never powered. The demos were done by simply pushing the car manually with only brakes working. It shouldn't be used if regular use of the car is intended as the control of throttle servo which also controls brakes is under Arduino microcontroller. This is a project that I made for self-improvement and educational purposes.



      





















