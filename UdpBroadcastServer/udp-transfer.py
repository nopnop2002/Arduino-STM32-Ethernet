import socket
import time
import datetime

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

while True:
	now = datetime.datetime.now()
	rmsg = "Hello UDP {}".format(now)
	#s.sendto(b'Hello UDP', ('255.255.255.255', 9876))
	s.sendto(rmsg.encode(), ('255.255.255.255', 9876))
	time.sleep(10)
