import os
import sys
import time
import socket
from threading import Thread

HOST = ''
PORT = 80

Users = {}

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST,PORT))
x = 0

#The thread that listens and writes to file
def conCurr(conn,addr):
    print("Starting thread for address: " + str(addr))
    f = open("./logs/" + str(addr).replace(".","_") + ".txt",'a')
    while(True):
        try:
            data = conn.recv(5)
        except:
            f.close()
            print("Client disconnected.")
            return
        data = data.decode('UTF-8','ignore')
        data = ''.join(data.split())
        f.write(data)

while(True):
    if(True):
        s.listen(1)
        conn,addr = s.accept()
        thre = Thread(target = conCurr, args=(conn,addr,)).start()
        x = x+1
