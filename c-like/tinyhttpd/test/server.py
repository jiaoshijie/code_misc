import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.bind(('127.0.0.1', 8088))

sock.listen(4)

print("端口号: 8088")
print("等待连接中......")
print("等待连接中......")

while True:
  connect, addr = sock.accept()

  # print(connect)
  # print(addr)
  buf = connect.recv(1024)
  print(buf)
