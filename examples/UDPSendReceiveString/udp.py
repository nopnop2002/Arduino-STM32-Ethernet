import socket
import time

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
while(1):
        s.sendto(b'Hello UDP', ('192.168.10.177', 8888))
        data, addr = s.recvfrom(1024)
        print("data: {}, addr: {}".format(data, addr))
        time.sleep(2)
