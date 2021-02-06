import socket
import threading


SERVER_IP = '127.0.0.1'
SERVER_PORT = 7000
MESSAGE_PORT = 5000


class Client:
    def __init__(self, message_port):
        self.message_port = message_port
        self.clients = []
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.message_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def run(self):
        self.server_socket.connect((SERVER_IP, SERVER_PORT))
        self.server_socket.send(bytes(str(self.message_port), encoding='UTF8'))

        clients_string = self.server_socket.recv(1024).decode('utf-8')
        print(clients_string)

        for c in clients_string.split(','):
            self.clients.append(c)

        self.server_socket.close()


def main():
    client = Client(MESSAGE_PORT)
    client.run()


main()
