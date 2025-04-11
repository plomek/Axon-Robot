from flask import Flask, Response, render_template, request, jsonify
import serial
import subprocess
import time
import os
import signal
import threading

app = Flask(__name__)

# Hardware configuration
UART_PORT = '/dev/ttyS0'
BAUD_RATE = 115200

# Global objects
uart = None
camera_process = None
frame_buffer = b''
buffer_lock = threading.Lock()

def setup_hardware():
    """Initialize hardware components"""
    global uart
    os.system(f'sudo chmod 666 {UART_PORT} 2>/dev/null')
    
    try:
        # Initialize UART
        uart = serial.Serial(UART_PORT, BAUD_RATE, timeout=1)
        print("UART initialized successfully")
    except Exception as e:
        print(f"UART initialization error: {str(e)}")
        exit(1)

    # Check camera
    try:
        subprocess.run(['libcamera-hello', '-t', '100'], check=True)
    except Exception as e:
        print(f"Camera error: {str(e)}")
        exit(1)

def start_camera_stream():
    """Start low-latency camera stream"""
    global camera_process
    try:
        camera_process = subprocess.Popen(
            [
                'libcamera-vid',
                '-n',
                '--width', '1080',
                '--height', '720',
                '--framerate', '15',
                '--codec', 'mjpeg',
                '--flush',
                '--inline',
                '--listen',
                '-t', '0',
                '-o', '-'
            ],
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
            bufsize=0,
            preexec_fn=os.setsid
        )
        print("Camera process started")
    except Exception as e:
        print(f"Camera error: {str(e)}")

def camera_reader_thread():
    """Thread for reading camera data"""
    global frame_buffer
    while True:
        try:
            # Find frame start marker
            while True:
                header = camera_process.stdout.read(2)
                if header == b'\xff\xd8':
                    break

            # Read complete frame
            frame = header
            while True:
                chunk = camera_process.stdout.read(4096)
                frame += chunk
                if frame[-2:] == b'\xff\xd9':
                    break

            with buffer_lock:
                frame_buffer = frame

        except Exception as e:
            print(f"Camera read error: {str(e)}")
            time.sleep(0.1)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/macro')
def macro():
    return render_template('macro.html')

@app.route('/color_control')  # <--- NEW ROUTE
def color_control():
    return render_template('color_control.html')

@app.route('/video_feed')
def video_feed():
    """Video stream with minimal buffering"""
    def generate():
        last_frame = b''
        while True:
            with buffer_lock:
                if frame_buffer != last_frame:
                    yield (b'--frame\r\n'
                           b'Content-Type: image/jpeg\r\n\r\n' 
                           + frame_buffer 
                           + b'\r\n')
                    last_frame = frame_buffer
            time.sleep(0.001)
    
    return Response(
        generate(),
        mimetype='multipart/x-mixed-replace; boundary=frame',
        headers={
            'X-Accel-Buffering': 'no',
            'Cache-Control': 'no-cache, no-store, must-revalidate',
            'Pragma': 'no-cache',
            'Expires': '0'
        }
    )

@app.route('/command', methods=['POST'])
def send_command():
    global uart
    cmd = request.form.get('command', '').strip()
    print(f"Sending: {cmd}")
    
    try:
        if not uart or not uart.is_open:
            uart = serial.Serial(UART_PORT, BAUD_RATE, timeout=1)
        uart.write(f"{cmd}\n".encode())
        return '', 204
    except Exception as e:
        print(f"UART error: {str(e)}")
        return 'Communication error', 500

@app.route('/cpu-temp')
def cpu_temp():
    try:
        with open('/sys/class/thermal/thermal_zone0/temp', 'r') as f:
            temp = int(f.read()) / 1000
            return jsonify({'temp': f"{temp:.1f}"})
    except Exception as e:
        print(f"Temperature read error: {str(e)}")
        return jsonify({'temp': 'N/A'})

def cleanup(signum=None, frame=None):
    print("\nShutting down application...")
    if camera_process:
        os.killpg(os.getpgid(camera_process.pid), signal.SIGKILL)
    if uart and uart.is_open:
        uart.close()
    os._exit(0)

if __name__ == '__main__':
    signal.signal(signal.SIGINT, cleanup)
    signal.signal(signal.SIGTERM, cleanup)
    
    setup_hardware()
    start_camera_stream()
    
    # Start camera reader thread
    threading.Thread(target=camera_reader_thread, daemon=True).start()
    
    # System optimizations
    os.system("sudo sysctl -w net.core.rmem_max=1048576")
    os.system("sudo sysctl -w net.core.wmem_max=1048576")
    
    app.run(host='0.0.0.0', 
            port=5000, 
            threaded=True, 
            use_reloader=False)