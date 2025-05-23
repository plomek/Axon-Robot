<div align="center">
  <h1>Axon Humanoid AI Robot</h1>
</div>

<b>Axon is currently a working prototype. While it’s fully functional, it's not yet fully polished and still needs some improvements and refinements to make it easier to assemble, more reliable, and more user-friendly. Just keep in mind that when we started this project, we had no CAD experience and were 16 and 17 years old.</b>
<div align="center">
    <img src="/.github/axongif1.gif" alt="Axon Robot in action" width="500"/>
</div>
  
Axon is an open-source robot that uses AI. It can move its arms and head, and it can also drive around. It has AI-powered speech recognition, so you can control it with your voice. It uses a database of questions with actions, along with a large language model (LLM), to answer other questions. It also has a built-in screen, colorful LED eyes, and can be controlled through a website interface. We are working on it since May 2024
<div align="center">
  <img src="/.github/3.jpg"/>
</div>


## Features

- **Movements:** The robot can move its arms, "drive," and turn his head.
- **Voice-Controlled:** Uses AI-powered speech recognition for voice-based control.
- **Modular & Customizable:** The magnetic "armor" is easily detachable for easy replacement and modification.
- **CAD Designs Included:** All the CAD files are avilable for anyone interested in building or modifying the robot.
- **Simple Knowledge Base:** Works like a basic chatbot, with UART actions so you can execute any command on esp32 to make it do stuff.

## CAD Models

All of the CAD files are available on [Onshape](https://cad.onshape.com/documents/940cdfcdb0dfad6e1a4b6d02/w/9cf2ed19ea888e5cc5dfd799/e/9b8e8ab3c406b01155d91643) and stl files available on [Printables](https://www.printables.com/model/1260260-axon-open-source-humanoid-robot). This project is <b>not beginner friendly!</b> You should have some knowledge about 3D printing and CAD preferably onshape. Some parts will need to be split into smaller pieces unless you have a very large 3D printer. The robot was designed to be printed on a 420x420 mm build plate. It was printed it on the Neptune 4 Max, but it should be possible to print it on a smaller 3D printer with some adjustments. It might even be better to print the base in multiple parts to make it easier to open after assembly.

As of now, some parts still need to be CNC-cut from metal, along with two metal sheets that need to be CNC'd and bent into shape. however, It should be redesigned to be 3D printable and possibly to use servos instead of unreliable geared motors with encoders which are hard to control, making the robot easier to replicate.

Axon is using a modified version of this [Robotic Prosthetic Hand](https://www.thingiverse.com/thing:1691704) by [grossrc](https://www.thingiverse.com/grossrc) for its palm and fingers [asembly video](https://www.youtube.com/watch?v=RJNDjnWV8Eo) use it for palm and fingers only

The robot is supported by a structural aluminum profile, 20x20 mm with a 6 mm slot, which needs to be connected to the center of the bottom plate which can be done, for example, using a metal plate and corner brackets.

<div align="center">
  <img src="/.github/1.jpg" alt="Axon Robot" height="500vh"/><img src="/.github/2.jpg" alt="Axon CAD Design" height="500vh"/>
</div>

## Installation & Setup

You’ll need to install files on a Raspberry Pi and a PC (or some server capable of running Llama 3.1 or newer models). Once you download everything, copy the `client.py` and `app.py` (which serve as your control panel web app) to the Raspberry Pi, and on your "server" run `main.py`. If you're smart, you'll figure it out – but if you really want to do something with this (and you're not as clueless as we were), you should probably write your own scripts that work better. Just use ours as a blueprint.

## Axon Robot Open Source Project – Usage Instructions

### Axon_AI Folder
axon file (no extension):
This is the Ollama configuration file. Use it to configure the language model.

client.py:
This script allows the Raspberry Pi (RPI) to connect to your computer via HTTP. It can work on a local network. If you don’t want to carry your computer/server with you, you can set up port forwarding on your local network to access it remotely.

main.py:
This is the AI engine script. It lets the RPI connect to the server, execute AI commands, and process voice interactions.

knowledge_base.json:
Here you can easily create your own questions and answers. You can also add UART commands that the RPI can send (for example, to an ESP32). This enables voice control of the project and allows you to extend the AI’s knowledge beyond what Ollama provides.

### Axon_Control_Panel Folder
Web Control Panel:
This folder contains a simple Flask-based web page that runs on the RPI. It lets you control the robot and create your own macros easily.

In the HTML, buttons include a data-command attribute that sends a specific UART command exactly as entered when clicked.

The functionality is powered by a JavaScript file.

Note: A few buttons on the navbar are non-functional (they’re there to make the interface look more complete); they do not affect any core features.



## Documentation

Coming Soon™

## Contributing

Contributions, suggestions, and improvements are very welcome! To contribute:

- Fork the repository.
- Create a new branch for your changes.
- Submit a pull request and describe your modifications in detail.
- For the 3D model, you can either make a remix on Printables or send me the model and I will update it there.


Robot wiring:
The robot is controlled by a Raspberry Pi through a web interface or voice commands. These commands are sent to four ESP32 modules. Each ESP32 receives its specific command and performs an action, such as changing the eye color. While it's possible to use 3 or even 2 ESP32 modules with the right code, we're using 4 because it was easier to split the code this way. Each ESP32 controls a different part of the robot:<br>
1.Head servo and LED<br>
2.Robot driving<br>
3.Arm servos<br>
4.Arm motors with limit switches. (experimental right now, the encoders don't work well with all four motors at once, so it relies on timers and limit switches, which don't always work perfectly).<br>

<div align="center">
  <h1>Parts List</h1>
</div>

## 3D Printer:  
- Recommended Neptune 4 Max preferably with a 0.8mm or 0.6mm nozzle for larger parts.  
- Any other 420mmx420mmx480mm or larger printer.  
- You should be able to still print it on a smaller printer by redesigning some parts or splitting prints into multiple parts.  

## Stepper Motor & Drivers:  
- 2x Nema 17 Stepper Motor for driving.  
- 2x Stepper Motor Drivers (e.g., TMC2209 V1.3).  

## Microcontrollers & Boards:  
- ESP32 Development Boards (4 units).  
- RPI4 or newer.  

## Filament & 3D Printing Materials:  
- Esun PLA+ Filament, White (+-7 kg).  
- Esun PLA+ Filament, Additional (2 kg, grey).  
- Optional TPU Filament for tires (250 g).  

## Structural & Mechanical Components:  
- Rotary Wheel (75 mm diameter) 53mm x 40mm mounting hole spacing.  
- Aluminum Profile 20mmx20mm, length 1040mm.  
- Some way to mount it to the bottom (e.g., metal plate and corner brackets).  

## Sensors & Accessories:  
- Raspberry Pi Camera v3 Wide. 
- 50cm camera raspberry pi camera cable
- Ultrasonic Sensor.  
- Breadboards and cables of various lengths.  
- Crimping your own longer cables (e.g., with 22AWG wire and a cable crimper is recommended).
- LED RGB 7 x WS2812 5050

## Power Components:  
- XT60 Connectors for charging.  
- AWG12 Cable – Black (2 meters).  
- AWG12 Cable – Red (2 meters).  
- 3s5p li-ion battery LG 18650 MJ1.  
- Any 3s+ li-ion Battery charger (e.g., Hota D6 Pro).  
- Power distribution board.  
- LED power switch.  
- Li-ion battery indicator.  
- Multiple step-up and step-down converters:  
  - 5V for Raspberry Pi and servos.  
  - 12V for stepper motors.  
  - 24V for arm motors.  
  - 3.3V or 5V for ESP32.  
- Any 3S BMS.  
- 2x Cytron MDD10A 2-channel motor driver.  

## Motors:  
- 1x Servo Motor, 13 kg torque (full metal gear) for head.  
- 8x Servo Motor, blue 35kg torque DS3235 for arms.  
- Servo Connectors and Crimping Tool.  
- 4x Bringsmart A58SW-555B geared motor with encoders.
- 4x limit switches

## Miscellaneous Hardware:  
- Elastic Paracord for hand.  
- Fishing wire for hand.  
- 50x neodymium magnets 8mmx2mm.  
- CA glue or hot glue for magnets.
- Various lenght M3 M4 M5 M6 Screws and bolts

## Audio & Visual Components:  
- Any wireless USB mic (e.g., Hollyland Lark M1 Solo).  
- Waveshare Touchscreen LCD – 10.1″ IPS, 1024×600 resolution.  
- 90-degree HDMI Adapter cable. 

If you have any questions or suggestions, feel free to contact us on Discord: plomek, minc0
