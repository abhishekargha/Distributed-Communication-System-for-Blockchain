import socket

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Define the server host and port
host = '192.168.1.24'  # The IP address of your laptop
port = 5005  # The same port as used by the ESP32

# Bind the socket to the host and port
sock.bind((host, port))

# Listen for incoming connections
sock.listen(1)
print(f'Server started on {host}:{port}')

# Define the forwarding server host and port
forward_host = '192.168.1.25'  # The IP address of the next server
forward_port = 5006  # The port of the next server

while True:
    # Wait for a connection
    print('Waiting for a connection...')
    connection, client_address = sock.accept()

    try:
        print(f'Connection from {client_address}')

        # Receive the data in small chunks and print it
        while True:
            data = connection.recv(16)
            print(f'Received "{data.decode()}"')
            if data:
                print('Sending data back to the client')
                connection.sendall(data)

                # Forward the data to the next server
                print('Forwarding data to the next server')
                forward_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                forward_sock.connect((forward_host, forward_port))
                forward_sock.sendall(data)
                forward_sock.close()
            else:
                print('No more data from', client_address)
                break

    finally:
        # Clean up the connection
        connection.close()
