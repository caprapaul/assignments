import socket
import select
import queue


def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    server.bind(('', 3000))
    server.setblocking(False)
    server.listen(5)
    inputs = [server]
    outputs = []
    message_queues = {}

    while inputs:
        readable, writeable, exception = select.select(
            inputs, outputs, message_queues)
        for s in readable:
            if s is server:
                connection, client_address = s.accept()
                connection.setblocking(False)
                inputs.append(connection)
                message_queues[connection] = queue.Queue()

            else:
                data = s.recv(1024)
                if data:
                    message_queues[s].put(data)
                    if s not in outputs:
                        outputs.append(s)

        for s in writeable:
            try:
                msg = message_queues[s].get_nowait()
                s.send(bytes("answer", 'utf-8'))
            except queue.Empty:
                outputs.remove(s)

        for s in exception:
            inputs.remove(s)
            if s in outputs:
                outputs.remove(s)
            s.close()
            del message_queues[s]


main()
