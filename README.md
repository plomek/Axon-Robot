<div align="center">
  <h1>Axon Humanoid AI Robot</h1>
  <img src="/.github/axongif1.gif" alt="Axon Robot in action" width="500"/>
</div>

<b>Axon is currently a working prototype. While it’s fully functional, it's not yet fully polished and still needs some improvements and refinements to make it easier to assemble, more reliable, and more user-friendly. Just keep in mind that when we started this project, we had no cad experience and were 16 and 17 years old we are working on it sice May 2024.</b>

Axon is an open-source robot that uses AI. It can move its arms and head, and it can also drive around. It has AI-powered speech recognition, so you can control it with your voice. It uses a database of questions with actions, along with a large language model (LLM), to answer other questions. It also has a built-in screen, colorful LED eyes, and can be controlled through a website interface.
<div align="center">
  <img src="/.github/3.jpg"/>
</div>


## Features

- **Movements:** The robot can move its arms, "drive," and turn his head.
- **Voice-Controlled:** Uses AI-powered speech recognition for voice-based control.
- **Modular & Customizable:** The magnetic "armor" is easly deatachable for easy replacement and modification.
- **CAD Designs Included:** All the CAD files are available for anyone interested in building or modifying the robot.
- **Simple Knowledge Base:** Works like a basic chatbot, with UART actions so you can execute any command on esp32 to make it do stuff.

## CAD Models

All of the CAD files are available on [Onshape](https://cad.onshape.com/documents/940cdfcdb0dfad6e1a4b6d02/w/9cf2ed19ea888e5cc5dfd799/e/9b8e8ab3c406b01155d91643) and stl files avillable on [Printables](https://www.printables.com/model/1260260-axon-open-source-humanoid-robot). This project is <b>not beginer friendly!</b> You should have some knowlage about 3D printing and CAD preferably onshape. Some parts will need to be split into smaller pieces unless you have a very large 3D printer. The robot was designed to be printed on a 420x420 mm build plate. It was printed it on the Neptune 4 Max, but it should be possible to print it on a smaller 3D printer with some adjustments. It might even be better to print the base in multiple parts to make it easier to open after assembly.

As of now, some parts still need to be CNC-cut from metal, along with two metal sheets that need to be CNC'd and bent into shape. However, It should be redesiged to be 3D printable and possibly to use servos instead of unreliable geared motors with encoders whitch are hard to controll, making the robot easier to replicate.

The robot is supported by a structural aluminum profile, 20x20 mm with a 6 mm slot, which needs to be connected to the center of the bottom plate whith can be done, for example, using a metal plate and corner brackets.

## Installation & Setup

You’ll need to install files on a Raspberry Pi and a PC (or some server capable of running Llama 3.1 or newer models). Once you download everything, copy the `client.py` and `app.py` (which serve as your control panel web app) to the Raspberry Pi, and on your "server" run `main.py`. If you're smart, you'll figure it out – but if you really want to do something with this (and you're not as clueless as we were), you should probably write your own scripts that work better. Just use ours as a blueprint.

## Documentation

Comming Soon™

## Contributing

Contributions, suggestions, and improvements are very welcome! To contribute:

- Fork the repository.
- Create a new branch for your changes.
- Submit a pull request and describe your modifications in detail.

<div align="center">
  <img src="/.github/1.jpg" alt="Axon Robot" width="500"/>
</div>

<div align="center">
  <img src="/.github/2.jpg" alt="Axon CAD Design" width="500"/>
</div>

Robot wiering:
The robot is controlled by a Raspberry Pi through a web interface or voice commands. These commands are sent to four ESP32 modules. Each ESP32 receives its specific command and performs an action, such as changing the eye color. While it's possible to use 3 or even 2 ESP32 modules with the right code, we're using 4 because it was easier to split the code this way. Each ESP32 controls a different part of the robot:<br>
1.Head servo and LED<br>
2.Robot driving<br>
3.Arm servos<br>
4.Arm motors with limit switches. (experimental right now, the encoders don't work well with all four motors at once, so it relies on timers and limit switches, which don't always work perfectly).<br>

## Parts List
3D Printer:
Recomended Neptune 4 Max preferably with a 0.8mm or 0.6mm nozzle for larger parts or any other 420mmx420mmx480mm or larger printer. You should be able to still print it on a smaller pritner by redesigning some parts or splitting prints in to multiple parts

Stepper Motor & Drivers:
2x Nema 17 Stepper Motor for driving
2x Stepper Motor Drivers eg. TMC2209 V1.3

Microcontrollers & Boards:
ESP32 Development Boards (4 units)
RPI4 or newer

Filament & 3D Printing Materials:
Esun PLA+ Filament, White (+-7 kg)
Esun PLA+ Filament, Additional (2 kg, grey)
optional TPU Filament for tires (250 g)


Structural & Mechanical Components:
Rotary Wheel (75 mm diameter) 53mm x 40mm mounting hole spacing
Aluminum Profile 20mmx20mm lenght 1040mm and some way to mount it to the bottom like metal plate and corner brackets

Sensors & Accessories:
raspberry pi camera v3 wide
Ultrasonic Sensor
Breadboards and cables various lengths (crimping your own longer cables eg.with 22awg wire and a cable crimper is recomended)

Power Components:
XT60 Connectors for charging
AWG12 Cable – Black (2 meters)
AWG12 Cable – Red (2 meters)
3s5p li-ion battery LG 18650 MJ1
any 3s+ liion Battery charger - hota d6 pro
Power distribiution board
Led power switch
li-ion battery indicator
Multiple step up and step down converters:
5V for raspberry pi and servos...
12V for stepper motors 
24V for arm motors 
3.3V or 5V for esp32 
Any Battery Management System (BMS)/Balancer
2x Cytron MDD10A 2 channel motor driver

Motors:
1x Servo Motor, 13 kg torque (full metal gear) for head
8x Servo Motor, blue 35kg torque DS3235 for arms
Servo Connectors and Crimping Tool
4x Bringsmart A58SW-555B geared motor with encoders

Miscellaneous Hardware:
Elastic Paracord for hand
fishing wire for hand
50x Neodymium magnets 8mmx2mm
Heat-Shrink Tape and ca glue or hotglue

Audio & Visual Components:
any wireless usb mic – Hollyland Lark M1 Solo
Waveshare Touchscreen LCD – 10.1″ IPS, 1024×600 resolution
90 degree HDMI Adapter cable
