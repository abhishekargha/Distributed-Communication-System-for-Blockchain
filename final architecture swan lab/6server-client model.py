import socket
import threading
import time 

class Node:
    def __init__(self, host, port):
        self.host = host
        self.port = port

    def start_server(self, forward_host, forward_port):
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind((self.host, self.port))
        server.listen(1)
        print(f"Server started on {self.host}:{self.port}")

        while True:
            client, address = server.accept()
            data = client.recv(1024)
            if not data:
                break
            print(f"Received: {data.decode()}")
            client.send("Message received".encode())
            time.sleep(5)
            self.forward_message(data.decode(), forward_host, forward_port)

    def forward_message(self, message, host, port):
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect((host, port))
        client.send((message + '\r').encode()) 

if __name__ == "__main__":
    node4 = Node('localhost', 7000)
    threading.Thread(target=node4.start_server, args=('localhost', 5000)).start()
