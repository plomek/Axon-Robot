<div align="center">
  <h1>Axon Humanoid AI Robot</h1>
  <img src="/.github/1.jpg" alt="Axon Robot" width="500"/>
</div>

First of all, we want to say that the whole project is kinda junk and messy – it’s still a prototype, and we were learning as we went along. For example, the CAD design is, in our opinion, terrible to manage from the inside even if it looks cool on the outside. So, if you decide to work on this project, you might be able to speed things up by using what we've already done, but trust us – it’s not a simple job. We’re open-sourcing this because some Redditors told us to do it. Just keep in mind that when we started this project, we were 16 and 17 years old (2024 May).

Axon is an open-source AI robot platform designed to interact with its environment through dynamic arm and head movements, plus voice control with speech recognition. It’s a "modular" system that encourages experimentation and customization in both hardware and software.

## Features

- **Kinda Working Movements:** The robot can move its arms, "drive," and perform some head movements.
- **Voice-Controlled:** Uses AI-powered speech recognition for intuitive, voice-based control.
- **Modular & Customizable:** Made for easy upgrades and tweaks, so you can modify both the hardware and software.
- **CAD Designs Included:** All the CAD files are available for anyone interested in building or modifying the robot.
- **Simple Knowledge Base:** Works like a basic chatbot, enhanced with UART actions so you can execute some commands.

## CAD Models

All of the CAD files are available on [Onshape](https://cad.onshape.com/documents/940cdfcdb0dfad6e1a4b6d02/w/9cf2ed19ea888e5cc5dfd799/e/9b8e8ab3c406b01155d91643) and Printables. It might be hard for you to print everything like we did because we specially bought a huge 3D printer — the Elegoo Neptune 4 Max.

## Installation & Setup

Okay, so this is kinda hard because it's a prototype. You’ll need to install files on a Raspberry Pi and a PC (or some server capable of running Llama 3.1 or newer models). Once you download everything, copy the `client.py` and `app.py` (which serve as your control panel web app) to the Raspberry Pi, and on your "server" run `main.py`. If you're smart, you'll figure it out – but if you really want to do something with this (and you're not as clueless as we were), you should probably write your own scripts that work better. Just use ours as a blueprint.

## Documentation

Right now, we don't have any solid documentation. We’ve got some rough sketches that explain how it works. We might put together proper docs later, but honestly, you probably shouldn’t expect perfection from this moving trash can.

## Contributing

Contributions, suggestions, and improvements are very welcome! To contribute:

- Fork the repository.
- Create a new branch for your changes.
- Submit a pull request and describe your modifications in detail.

<div align="center">
  <img src="/.github/axongif1.gif" alt="Axon Robot in action" width="500"/>
</div>

<div align="center">
  <img src="/.github/2.jpg" alt="Axon CAD Design" width="400"/>
</div>

## Parts List
3D Printer:
Neptune 4 Max

Stepper Motor & Drivers:
Stepper Motor (2 unit)
Stepper Motor Drivers (2 units)

Microcontrollers & Boards:
ESP32 Development Boards (4 units)
RPI4 (1 unit)

Power & Battery Management:
Battery Management System (BMS)/Balancer (1 unit)
Charge Indicator (1 unit, sourced from Aliexpress)
Cytron Motor Drivers (2 units)
Power Converters (2 units, from Aliexpress)

Filament & 3D Printing Materials:
Esun PLA+ Filament, White (+-7 kg)
Esun PLA+ Filament, Additional (2 kg, grey)
TPU Filament (250 g)


Structural & Mechanical Components:
Rotary Wheel (75 mm diameter)
Aluminum Profiles 20x20 with Screws (for frame assembly)
Deburring Tool

Sensors & Accessories:
Touch Sensor Module(s)
Ultrasonic Sensor
Level Shifters (4 units)
Breadboards and Connecting Cables (various lengths for ESP32 accessories)

Connectors & Cables:
XT60 Connector Pairs (5 pairs)
AWG12 Cable – Black (2 meters)
AWG12 Cable – Red (2 meters)

Servo Motors:
Servo Motor, 13 kg torque (full metal gear)
Servo Motor, 35 kg torque (8 units DS3235 variant)
Servo Connectors and Crimping Tool

Additional Motors & Converters:
B-Smart Motors (4 units 60 kg torque, form aliexpress) we recommend pay little bit more and redesing it for 60-70kg servos

Miscellaneous Hardware:
Magnetic Inserts and Small Fasteners (M series inserts)
Small Bearings or 4 mm Balls (for mechanical assemblies; quantity as needed)
Elastic Paracord
Magnets (approximately 70 units; specifications as needed)
LG MJ1 Components (15 units; 3s5p)

Audio & Visual Components:
Wireless Microphone – Hollyland Lark M1 Solo
Touchscreen LCD – 10.1″ IPS, 1024×600 resolution
Camera Module – Raspberry Camera v3
HDMI Adapter and Connector

Adhesives & Fastening Tools:
Heat-Shrink Tape and Adhesive
Soldering/Crimping Tools (for connectors)

Other Consumables:
Bungee Cord (5 m) to make working fingers


---

For more details, updates, or to get involved, check out our GitHub repository. Let’s build the future of open-source humanoid AI robotics together!
