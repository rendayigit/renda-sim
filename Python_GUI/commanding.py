"""Transmit commands to the engine"""

import json
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
            cls._instance.socket = cls._instance.context.socket(zmq.REQ)
            cls._instance.socket.connect("tcp://localhost:12340")

        return cls._instance

    def __init__(self):
        # Explicitly define socket attribute for better static analysis
        if not hasattr(self, "socket"):  # Prevent reinitialization in the singleton
            self.socket = None

    # TODO(renda): Need timeout option or blocks forever
    def request(self, command: str) -> str:
        """Send a command and wait for a response from the engine"""
        self.socket.send_string(json.dumps(command))  # Send the command
        return self.socket.recv_json()  # Receive and decode the response
