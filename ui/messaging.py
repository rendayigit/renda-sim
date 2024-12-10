"""Messaging utilities for GUI"""

import threading
import time
import wx
import zmq


class Messaging:
    """Messaging utilities for GUI"""

    def __init__(self, topic, callable_func, *args):
        self.topic = topic
        self.callable_func = callable_func
        self.args = args

        context = zmq.Context(1)

        self.subscriber = context.socket(zmq.SUB)
        self.subscriber.connect("tcp://localhost:12345")

        self.subscriber.set(zmq.SUBSCRIBE, topic.encode())

        self.thread = threading.Thread(target=self._messaging_thread)
        self.is_running = True

    def start(self):
        """Starts the messaging thread"""
        if not self.is_running:
            self.is_running = True
            self.thread = threading.Thread(target=self._messaging_thread)

        self.thread.start()

    def stop(self):
        """Stops the messaging thread"""
        if self.thread.is_alive():
            self.is_running = False
            self.thread.join()

    def _messaging_thread(self):
        """Messeging thread"""
        while self.is_running:
            frames = self.subscriber.recv_multipart(copy=False)
            topic = bytes(frames[0]).decode()
            messagedata = bytes(frames[1]).decode()

            if topic == self.topic:
                wx.CallAfter(self.callable_func, *self.args, messagedata)

            # time.sleep(0.01)
