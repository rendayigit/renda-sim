"""Transmit commands to the engine"""

import zmq


class Commanding:
    """Singleton class to transmit commands to the engine"""

    _instance = None  # Class-level instance variable for singleton implementation

    def __new__(cls):
        if cls._instance is None:
            # Create the singleton instance
            cls._instance = super(Commanding, cls).__new__(cls)

            # Initialize ZeroMQ context and socket
            cls._instance.context = zmq.Context(1)
            cls._instance.socket = cls._instance.context.socket(zmq.PAIR)
            cls._instance.socket.connect("tcp://localhost:12340")

        return cls._instance

    def __init__(self):
        # Explicitly define socket attribute for better static analysis
        if not hasattr(self, "socket"):  # Prevent reinitialization in the singleton
            self.socket = None

    def transmit(self, command: str):
        """Transmit command to the engine"""
        if not isinstance(command, str):
            raise ValueError("Command must be a string")

        self.socket.send(command.encode())  # Send the command as bytes

    def request(self, command: str) -> str:
        """Send a command and wait for a response from the engine"""
        self.transmit(command)  # Send the command
        return self.socket.recv().decode()  # Receive and decode the response

    def request_json(self, command: str) -> str:
        """Send a command and wait for a response from the engine"""
        self.transmit(command)  # Send the command
        return self.socket.recv_json()  # Receive and decode the response
