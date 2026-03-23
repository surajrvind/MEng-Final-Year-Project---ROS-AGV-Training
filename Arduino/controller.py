import serial
import time

port = '/dev/ttyACM0'
baud = 9600

uno = serial.Serial(port, baud, timeout=.1)
time.sleep(1)
print("sir yes sir")

def write_read(x):
    uno.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = uno.readline()
    return data

while True:
    num = input("Enter a number: ")
    
    value = write_read(num)
    print(value)