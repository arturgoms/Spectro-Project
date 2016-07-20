#!/usr/bin/python3

import serial

def getSerial():
    try:
        port = serial.Serial('/dev/ttyS0', baudrate=9600, timeout=1.0)
        while True:
            with open("file.txt", "w") as f:
                f.writelines(port)
            f.close()
    except Exception as e:
        print("Erro na Porta! %s" %e)

if __name__ == '__main__':
    getSerial()
