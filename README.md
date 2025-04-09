<div align="center">
  <h1>Axon Humanoid AI Robot</h1>
  <img src="/.github/1.jpg" alt="Axon Robot" width="500"/>
</div>

Axon is an open-source AI robot platform designed to interact with its environment through dynamic arm and head movements, autonomous navigation, and advanced voice control powered by AI-based speech recognition. It is a modular system that encourages experimentation and customization in both hardware and software.

## Features

- **Articulated Movements:** Capable of fluid arm and head motions to express emotions or perform tasks.
- **Autonomous Navigation:** Designed to drive around and navigate various environments.
- **Voice-Controlled:** Incorporates AI-powered speech recognition for intuitive, voice-based operation.
- **Modular & Customizable:** Built for easy upgrades and modifications, allowing users to tweak hardware and software.
- **CAD Designs Included:** Comprehensive CAD files are available for users interested in building or customizing the robot.

## CAD Models

All of the CAD files are available in the `/cad` directory of this repository. These files contain detailed designs for the robot's chassis, limbs, and internal components.  
For those interested in fabrication or customization, please refer to the assembly and design guidelines provided within the CAD documentation.

## Installation & Setup

### Hardware Assembly

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/axon-humanoid-ai-robot.git
    cd axon-humanoid-ai-robot
    ```

2. Review the CAD designs in the `/cad` folder and follow the assembly instructions provided in the `/docs` directory for building the hardware.

3. Assemble the mechanical parts according to the provided wiring diagrams and CAD models.

### Software Setup

1. Ensure you have Python installed (preferably 3.7+). Install the necessary Python packages:
    ```bash
    pip install -r requirements.txt
    ```

2. Start the robot’s control software:
    ```bash
    python main.py
    ```

3. The user interface and control panel are available as part of the project's front-end. Open the HTML files (e.g., `index.html`, `macro.html`, `color_control.html`) in your web browser to simulate the UI.

## Documentation

Full documentation—including detailed assembly instructions, wiring diagrams, and software configuration—is available in the `/docs` folder. Please review these documents for step-by-step guidance on building and operating Axon.

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

For more details, updates, or to get involved, visit our GitHub repository. Let's build the future of open-source humanoid AI robotics together!
