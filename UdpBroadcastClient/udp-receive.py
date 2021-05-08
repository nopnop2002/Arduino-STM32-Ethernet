import select, socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('<broadcast>', 9876))
s.setblocking(0)

while True:
	result = select.select([s],[],[])
	rbuf = result[0][0].recv(1024)
	#print("recv type={}".format(type(rbuf)))
	if (type(rbuf) is not str):
		msg=rbuf.decode('utf-8')
		#print("type(msg)={}".format(type(msg)))
	print(msg)

