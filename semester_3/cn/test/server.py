import socket
import json
import sys
from threading import Thread
from queue import Queue
import select

IP = '0.0.0.0'
PORT = 7000


class Server:
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connections = []
        self.connections_data = {}  # (connection, ip, port)

    def run(self):

        self.socket.bind((self.ip, self.port))
        self.socket.listen(5)
        print('Awaiting connection...')

        while True:
            connection, address = self.socket.accept()
            t = Thread(target=self.client, args=(connection, address,))
            t.start()

            # prints the address of the user that just connected
            print(address[0] + 'connected')

    def connections_string(self):
        connections = ''

        for c in self.connections_data.values():
            connection = c['address'] + ':' + str(c['port']) + ','
            connections += connection

        connections = connections[:-1]
        return connections

    def client(self, connection, address):
        if connection not in self.connections:
            self.connections.append(connection)
            self.connections_data[connection] = {}
            self.connections_data[connection]['address'] = address[0]

        try:
            message = connection.recv(1024)
            print(message)
            self.connections_data[connection]['port'] = message
            self.broadcast(self.connections_string())

        except:
            return

    def broadcast(self, message):
        """Broadcasts a message to all the clients."""
        for s in self.connections:
            s.send(bytes(message, encoding='utf-8'))


def main():
    serv = Server(IP, PORT)
    serv.run()


main()
