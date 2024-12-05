"""Messaging utilities for GUI"""

import threading
import time
import wx
import zmq


class Messaging:
    """Messaging utilities for GUI"""

    def __init__(self, main_window):
        self.window = main_window

        context = zmq.Context(1)

        self.subscriber = context.socket(zmq.SUB)
        self.subscriber.connect("tcp://localhost:12345")

        self.subscriber.set(zmq.SUBSCRIBE, "SIM_TIME".encode())

        thread = threading.Thread(target=self.messaging_thread)
        thread.start()

    def messaging_thread(self):
        """Messeging thread"""
        while True:
            frames = self.subscriber.recv_multipart(copy=False)
            topic = bytes(frames[0]).decode()
            messagedata = bytes(frames[1]).decode()

            if topic == "SIM_TIME":
                wx.CallAfter(self.window.sim_time_display.ChangeValue, messagedata)

            time.sleep(0.01)
