"""Messaging utilities for GUI"""

import wx
import zmq
import threading
import time


class Messaging:
    """Messaging utilities for GUI"""

    def __init__(self, main_window):
        self.window = main_window

        self.context = zmq.Context(1)

        self.subscriber = self.context.socket(zmq.SUB)
        self.subscriber.connect("tcp://localhost:12345")

        self.subscriber.set(zmq.SUBSCRIBE, "SIM_TIME".encode())

        self.thread = threading.Thread(target=self.messaging_thread)
        self.thread.start()

    def messaging_thread(self):
        """Messeging thread"""
        while True:
            # Receive a message from the server
            message = self.subscriber.recv_string()

            if message == "SIM_TIME":
                continue

            wx.CallAfter(self.window.sim_time_display.ChangeValue, message)

            time.sleep(0.01)
