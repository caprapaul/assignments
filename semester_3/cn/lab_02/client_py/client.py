import socket
import threading
import time
import random
import string


def find_leader_address(leader_socket: socket.socket):
    while True:
        data, addr = leader_socket.recvfrom(len('leader'))

        message = data.decode('utf-8')
        if message == 'leader':
            return addr


def normal_student(port):
    find_leader_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    find_leader_socket.bind(('', port))
    addr = find_leader_address(find_leader_socket)
    find_leader_socket.close()
    student_connection = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    while True:
        send_val = random.uniform(0.0, 1.0)
        if send_val > 0.5:
            question_length = random.randint(3, 30)
            question = ''.join(random.choice(string.ascii_letters)
                               for _ in range(question_length))
            print("Generated question: ", question)
            student_connection.sendto(
                question_length.to_bytes(4, byteorder='little'), addr)
            student_connection.sendto(bytes(question, 'utf-8'), addr)
        time.sleep(3)
    # find_leader_socket.close()


def broadcast_group(port, broadcast_socket: socket.socket):
    while True:
        broadcast_socket.sendto(bytes('leader', 'utf-8'),
                                ('255.255.255.255', port))
        time.sleep(5)


def broadcast_wait(broadcast_socket: socket.socket, teacher_socket: socket.socket):
    while True:
        data = broadcast_socket.recv(4)
        question_length = int.from_bytes(data, byteorder='little')
        data = broadcast_socket.recv(question_length)
        question = data.decode('utf-8')
        print("Recieved question: ", question)
        teacher_socket.send(question_length.to_bytes(
            4, byteorder='little') + bytes(question, 'utf-8'))


def wait_teacher_answer(port, broadcast_socket: socket.socket, teacher_socket: socket.socket):
    while True:
        data = teacher_socket.recv(100)
        print(data.decode('utf-8'))
        broadcast_socket.sendto(data, ('255.255.255.255', port))


def group_leader(port):
    teacher_connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    teacher_connection.connect(('127.0.0.1', 3000))
    broadcast_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    broadcast_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    broadcast_thread = threading.Thread(
        args=(port, broadcast_socket,), target=broadcast_group)
    broadcast_thread.start()

    broadcast_waiting_thread = threading.Thread(
        args=(broadcast_socket, teacher_connection), target=broadcast_wait)
    broadcast_waiting_thread.start()

    wait_teacher_answer_thread = threading.Thread(
        args=(port, broadcast_socket, teacher_connection,), target=wait_teacher_answer)
    wait_teacher_answer_thread.start()


def main():
    port = input("Give group port=")
    student_type = input("Group leader? (1 = true, 0 = false) ")
    if int(student_type) == 1:
        group_leader(int(port))
    else:
        normal_student(int(port))


main()
