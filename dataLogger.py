#!/usr/bin/python3

import serial
from time import sleep

def getSerial():
    try:
        port = serial.Serial('/dev/ttys0', baudrate=9600, timeout=1)
        while True:
            data = port.readline()
            temperatura, altitude = data.split('separando')
            with open ("temperatura.txt", "w") as f:
                print temperatura
                f.writelines(temperatura)
                f.close()
            with open ("humidade.txt", "w") as f:
                print humidade
                f.writelines(humidade)
                f.close()
    except Exception as e:
        print("Erro' %s" %e)
if __name__ == '__main__':
    getSerial()
