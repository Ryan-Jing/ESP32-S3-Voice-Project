import numpy as np
from scipy.io.wavfile import write
import sounddevice as sd
import serial
import pyaudio
import wave

SERIAL_PORT = '/dev/cu.usbmodem1101'  # Update this to match your serial port (macOS)
BAUD_RATE = 1000000               # Baud rate to match your ESP32 configuration
AUDIO_RATE = 44100                    # Sampling rate (must match ESP32)
CHUNK_SIZE = 1024                     # Number of bytes to read at a time
FORMAT = pyaudio.paInt16             # Match your ESP32's sample format
CHANNELS = 1                          # Mono
DURATION = 10

# *************************************************** #
# PLAY AUDIO FROM FILE
# *************************************************** #

# # Load the raw mic data from the file
# with open("mic_data.txt", "r") as f:
#     lines = f.readlines()

# # Convert lines to int16 numpy array
# samples = np.array([int(line.strip()) for line in lines if line.strip()], dtype=np.int16)

# # Define the sample rate (should match SAMPLE_RATE in your C code, e.g., 16000 Hz)
# sample_rate = 88200  # Update this if your C macro SAMPLE_RATE is different

# # Save to WAV file (optional)
# write("output.wav", sample_rate, samples)

# # Play the audio
# sd.play(samples, sample_rate)
# sd.wait()

# *************************************************** #
# PLAY AUDIO FROM SERIAL PORT
# *************************************************** #

# Set up the serial connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

# Set up PyAudio to play the audio
audio = pyaudio.PyAudio()
stream = audio.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=AUDIO_RATE,
                    output=True)

try:
    while True:
        data = ser.read(CHUNK_SIZE)  # Read a chunk of audio data from the serial port
        stream.write(data)           # Play the audio chunk
except KeyboardInterrupt:
    print("Stopping...")
finally:
    stream.stop_stream()
    stream.close()
    audio.terminate()
    ser.close()

# *************************************************** #
# PLAY AUDIO FROM BLUETOOTH
# *************************************************** #
