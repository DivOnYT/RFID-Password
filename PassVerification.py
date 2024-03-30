import serial
import subprocess

# Ouvrir le port série
ser = serial.Serial('COM4', 9600) # Remplacez 'COMX' par le bon port COM

while True:
    # Lire depuis le port série
    line = ser.readline().strip().decode('utf-8')
    # Vérifier si le signal est reçu
    if line == 'PC_SIGNAL':
        # Exécuter le code Python externe
        print("Password Detected")