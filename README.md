<div align="center">
  <h1>Axon Humanoid AI Robot</h1>
  <img src="/.github/1.jpg" alt="Axon Robot" width="500"/>
  <img src="/.axongif1.gif" alt="Axon Robot" width="500"/>
</div>

First of all, we want to say that the whole project is kinda junk and messy—it’s still a prototype and we were learning as we went along. For example, the CAD design is, in our opinion, terrible to manage from the inside even if it looks cool on the outside. So, if you decide to work on this project, you might be able to speed things up by using what we've already done, but trust us—it’s not a simple job.

Axon is an open-source AI robot platform designed to interact with its environment through dynamic arm and head movements, plus advanced voice control powered by AI-based speech recognition. It’s a "modular" system that encourages experimentation and customization in both hardware and software.

## Features

- **Kinda Working Movements:** The robot can move its arms, "drive," and do some head movement.
- **Voice-Controlled:** Uses AI-powered speech recognition for intuitive, voice-based control.
- **Modular & Customizable:** Made for easy upgrades and tweaks, so you can customize both the hardware and software.
- **CAD Designs Included:** All the CAD files are here for anyone interested in building or modifying the robot.
- **Simple Knowledge Base:** Works like a basic chatbot, but we added UART actions so you can execute some commands.

## CAD Models

All of the CAD files are available on [Onshape](https://www.onshape.com) and Printables. It might be hard for you to print everything like we did because we specially bought a huge 3D printer — the Elegoo Neptune 4 Max.

## Installation & Setup

Okay, so this is kinda hard because it's a prototype. You’ll need to install files on a Raspberry Pi and a PC (or some server capable of running Llama 3.1 or newer models). Once you download everything, get the `client.py` and `app.py` on the Raspberry Pi, and on your "server" run `main.py`. If you're smart, you'll figure it out—if you really want to do something with this (and you're not as clueless as we were), you should probably write your own scripts that work better. Just use ours as a blueprint.

## Documentation

Right now, we don't have any solid documentation. We’ve got some rough sketches explaining how it works. We might put together proper docs later, but honestly, you probably shouldn’t expect perfection from this moving trash can.

## Contributing

Contributions, suggestions, and improvements are very welcome! To contribute:

- Fork the repository.
- Create a new branch for your changes.
- Submit a pull request and describe your modifications in detail.

For additional guidelines, please see the [CONTRIBUTING.md](CONTRIBUTING.md) file.

## License

This project is licensed under the [MIT License](LICENSE).

<div align="center">
  <img src="/.github/2.jpg" alt="Axon CAD Design" width="400"/>
</div>

---

For more details, updates, or to get involved, check out our GitHub repository. Let’s build the future of open-source humanoid AI robotics together!
