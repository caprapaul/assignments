import socket
import json
import sys
from threading import Thread
from queue import Queue
import select

IP = '0.0.0.0'
PORT = 7777


class Command:
    def __init__(identifier, execute):
        self.identifier = identifier
        self.execute = execute
        self.running = False


class Server:
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.commands = {}

    def register_command(command: Command):
        self.commands[command.identifier] = command

    def run(self):
        self.running = True

        self.socket.setblocking(0)
        self.socket.bind((self.ip, self.port))
        self.socket.listen(5)
        print('Awaiting connection...')

        inputs = [self.socket]
        outputs = []
        messages = {}

        while self.running:
            readable, writable, exceptional = select.select(
                inputs, outputs, [])

            for s in readable:
                if s is self.socket:
                    connection, address = s.accept()
                    connection.setblocking(0)
                    print('Connected: ', address)
                    inputs.append(connection)
                    messages[connection] = Queue()

                elif s is sys.stdin:
                    self.__on_input()

                else:
                    self.__on_connect(connection)

    def __on_input():
        command = sys.stdin.readline()

        if command == 'exit':
            self.running = False

    def __on_connect(connection):
        try:
            raw_data = connection.recv(1024)

            if not raw_data:
                return

            json_data = raw_data.decode('utf-8')
            data = json.loads(json_data)
            command = data['command']

            if command not in self.commands:
                response = {
                    'status': 'UNKNOWN_COMMAND',
                }
                json_response = json.dumps(data, separators=(',', ':'))

                connection.send(bytes(json_response, 'utf-8'))

                return

            body = data['body']

            self.commands[command].execute(connection, body)

        except Exception as e:
            print(e)

        finally:
            connection.close()


def sum_c(connection, body):
    numbers = body['numbers']

    s = 0
    for x in numbers.split(','):
        num = int(x)
        s += num


server = Server(IP, PORT)
sum_command = Command('sum', sum_c)

server.run()
