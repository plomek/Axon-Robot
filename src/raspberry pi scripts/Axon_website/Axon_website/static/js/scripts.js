document.addEventListener('DOMContentLoaded', function() {
    const commandLine = document.getElementById('command-line');
    const cpuTempElement = document.getElementById('cpu-temp');
    const enableToggle = document.getElementById('enable-toggle');
    const clearButton = document.getElementById('clear-button');
    let isOn = false;

    // Funkcja wysy?aj?ca komend? do serwera
    function sendCommand(command) {
        commandLine.value += `${command}\n`;
        commandLine.scrollTop = commandLine.scrollHeight;

        fetch('/command', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
            },
            body: `command=${command}`,
        }).catch(error => console.error('Error sending command:', error));
    }

    // Funkcja aktualizuj?ca temperatur? CPU
    function updateTemperature() {
        fetch('/cpu-temp')
            .then(response => response.json())
            .then(data => {
                cpuTempElement.textContent = data.temp;
            })
            .catch(error => {
                console.error('Error fetching CPU temperature:', error);
                cpuTempElement.textContent = 'N/A';
            });
    }

    // Obs?uga przycisw ruchu
    document.querySelectorAll('.control-btn.movement-btn').forEach(button => {
        button.addEventListener('mousedown', function() {
            const command = this.getAttribute('data-command');
            sendCommand(`${command}-down`);
        });

        button.addEventListener('mouseup', function() {
            const command = this.getAttribute('data-command');
            sendCommand(`${command}-up`);
        });
    });

    // Obs?uga pozosta?ych przyciskw
    document.querySelectorAll('.control-btn:not(.movement-btn)').forEach(button => {
        button.addEventListener('click', function() {
            const command = this.getAttribute('data-command');
            sendCommand(command);
        });
    });

    // Toggle button
    enableToggle.addEventListener('click', function() {
        isOn = !isOn;
        const command = isOn ? "on" : "off";
        enableToggle.textContent = isOn ? "On" : "Off";
        enableToggle.classList.toggle("btn-success", isOn);
        enableToggle.classList.toggle("btn-danger", !isOn);
        sendCommand(`enable-${command}`);
    });

    // Clear button
    clearButton.addEventListener('click', function() {
        commandLine.value = '';
    });

    // Aktualizacja temperatury co 2 sekundy
    setInterval(updateTemperature, 2000);
    updateTemperature(); // Pierwsze wywo?anie
});
