import os
import requests
import pygame
import speech_recognition as sr
from gtts import gTTS
import serial

# -------------------------------------
# CONFIGURATION
# -------------------------------------
SERVER_URL = 'http://192.168.153.95:5000'  # Flask server address

# UART configuration
UART_PORT = '/dev/ttyS0'  # On Windows might be 'COM3'
UART_BAUDRATE = 115200

try:
    uart = serial.Serial(UART_PORT, UART_BAUDRATE, timeout=1)
    print(f"UART: Connected to port {UART_PORT}")
except serial.SerialException as e:
    print(f"UART: Connection error with port {UART_PORT}: {e}")
    uart = None

# Activation/deactivation phrases
ACTIVATION_PHRASE = "Akson"
DEACTIVATION_PHRASE = "Akson stop"

# Flag for MP3 file switching (prevents file locking)
audio_toggle = True

# Initialize pygame, microphone and speech recognition
os.environ['SDL_AUDIODRIVER'] = 'alsa'  # Force ALSA instead of JACK
pygame.mixer.init()
recognizer = sr.Recognizer()
mic = sr.Microphone()

# Flag indicating if the model is active
active = False

# -------------------------------------
# TTS/STT FUNCTIONS
# -------------------------------------
def text_to_speech(text, lang='pl'):
    """
    Converts text to speech using gTTS and plays it via pygame.
    """
    global audio_toggle
    if not text:
        print("Error: No text to synthesize.")
        return
    
    filename = "response1.mp3" if audio_toggle else "response2.mp3"
    
    tts = gTTS(text=text, lang=lang)
    tts.save(filename)
    
    pygame.mixer.music.load(filename)
    pygame.mixer.music.play()
    
    while pygame.mixer.music.get_busy():
        pass
    
    old_filename = "response2.mp3" if audio_toggle else "response1.mp3"
    if os.path.exists(old_filename):
        try:
            os.remove(old_filename)
        except PermissionError:
            print(f"Cannot delete {old_filename}, file is in use.")
    
    audio_toggle = not audio_toggle

def recognize_speech_from_mic():
    """
    Recognizes speech from microphone using SpeechRecognition library.
    """
    with mic as source:
        print("Listening...")
        recognizer.adjust_for_ambient_noise(source)
        audio = recognizer.listen(source)
        
    try:
        print("Recognizing speech...")
        text = recognizer.recognize_google(audio, language="pl-PL")
        return text
    except sr.UnknownValueError:
        print("Could not recognize speech.")
    except sr.RequestError:
        print("Error connecting to speech recognition service.")
    return None

# -------------------------------------
# UART COMMUNICATION FUNCTIONS
# -------------------------------------
def send_uart_command(command):
    """
    Sends command via UART to ESP32.
    """
    if uart:
        try:
            uart.write(f"{command}\n".encode('utf-8'))
            print(f"UART: Sent command: {command}")
        except Exception as e:
            print(f"UART: Error sending command: {e}")
    else:
        print("UART: Port not available, cannot send command.")

# -------------------------------------
# SERVER COMMUNICATION FUNCTIONS
# -------------------------------------
def send_message(message):
    """
    Sends request to Flask server. Plays response (TTS) and executes UART actions if available.
    """
    try:
        response = requests.post(f"{SERVER_URL}/send", json={'message': message})
        response.raise_for_status()
        response_data = response.json()

        answer = response_data.get('answer', "I don't have an answer to that question.")
        action = response_data.get('action')

        print(f"Bot: {answer}")
        text_to_speech(answer, lang='pl')

        if action:
            print(f"Bot: Executing action: {action}")
            send_uart_command(action)
    
    except requests.exceptions.RequestException as e:
        print(f"Server connection error: {e}")
        text_to_speech("Cannot connect to server.", lang='pl')

# -------------------------------------
# MAIN PROGRAM LOOP
# -------------------------------------
if __name__ == '__main__':
    print("Hello! Project has been started")
    text_to_speech("Hello!", lang='pl')
    
    while True:
        user_input = recognize_speech_from_mic()
        if not user_input:
            continue

        # Activation/deactivation logic
        if not active:
            if ACTIVATION_PHRASE.lower() in user_input.lower():
                active = True
                print("Bot: I'm listening to your question.")
                text_to_speech("I'm listening to your question.", lang='pl')
            else:
                print("Bot: Waiting for activation phrase.")
                continue
        else:
            if DEACTIVATION_PHRASE.lower() in user_input.lower():
                active = False
                print("Bot: Deactivation.")
                text_to_speech("Deactivation.", lang='pl')
                continue
            elif user_input.lower() in ["end", "exit", "quit"]:
                print("Bot: Goodbye!")
                text_to_speech("Goodbye!", lang='pl')
                break

        send_message(user_input)
