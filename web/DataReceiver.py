import serial
from threa import Thread 

path = '/dev/rfcomm0'
blt = serial.Serial(path, baudrate = 9600)
data = []

def writeBTL(str):
    btl.write(str.encode())

def readBTL():
    recievedMsg = btl.read_all()
    recievedMsg = recievedMsg.split('\r\n')
    for i in recievedMsg.len()
        data.append(recievedMsg[i])


if __init__ == '__main__':
    thrd = Thread(target=readBTL)
    thr.start()