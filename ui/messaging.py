"""Messaging utilities for Main Window"""

import zmq


context = zmq.Context(1)

#  Socket to talk to server
subscriber = context.socket(zmq.SUB)
subscriber.connect("tcp://localhost:12345")

subscriber.set(zmq.SUBSCRIBE, "HEART_BEAT".encode())

while True:
    # Receive a message from the server
    message = subscriber.recv_string()

    # Print the received message
    print(f"Received message: {message}")
