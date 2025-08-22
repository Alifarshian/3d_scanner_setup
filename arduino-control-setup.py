import serial
import keyboard
arduino = serial.Serial(port='COM9', baudrate=9600, timeout=1)
while True:              
    command_setting = input("mode(Set-Scan) ")
    if command_setting=="Set":
       while True: 
            if keyboard.is_pressed("a"):
                arduino.write(b'a')
            if keyboard.is_pressed("d"):
                arduino.write(b'd')
            if keyboard.is_pressed("w"):
                arduino.write(b'w')
            if keyboard.is_pressed("s"):
                arduino.write(b's')
            if keyboard.is_pressed("e"):
                break
    if command_setting=='Scan':
        while True:
            if keyboard.is_pressed("f"):
                arduino.write(b'f')
            if keyboard.is_pressed("b"):
                arduino.write(b'b')
            if keyboard.is_pressed("e"):
                break
    if command_setting=='h':
        break        
    
