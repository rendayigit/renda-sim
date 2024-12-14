"""Messaging utilities for GUI"""

import threading
import wx
import zmq


class Messaging:
    """Messaging utilities for GUI"""

    _instance = None  # Class-level instance variable for singleton implementation

    def __new__(cls):
        """Singleton instance"""
        if cls._instance is None:
            # Create the singleton instance
            cls._instance = super(Messaging, cls).__new__(cls)

            # Initialize ZeroMQ context and socket
            cls._instance.context = zmq.Context(1)
            cls._instance.subscriber = cls._instance.context.socket(zmq.SUB)
            cls._instance.subscriber.connect("tcp://localhost:12345")

            # TODO(renda): Maybe combine maps for better readability
            cls._instance.topic_handler_map = {}
            cls._instance.topic_handler_argument_map = {}

            cls._instance.thread = threading.Thread(target=cls._instance._messaging_thread)
            cls._instance.is_running = True
            cls._instance.thread.start()

        return cls._instance

    def __init__(self):
        # Explicitly define attributes for better static analysis
        if not hasattr(self, "subscriber"):  # Prevent reinitialization in the singleton
            self.subscriber = None
            self.topic_handler_map = {}
            self.topic_handler_argument_map = {}
            self.is_running = True
            self.thread = threading.Thread(target=self._messaging_thread)

    def add_topic_handler(self, topic, callable_func, *args):
        """Adds a handler for a given topic"""
        self.topic_handler_map[topic] = callable_func
        self.topic_handler_argument_map[topic] = args

        self.subscriber.set(zmq.SUBSCRIBE, topic.encode())

    # TODO(renda): Add option to remove topic handlers

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

            # TODO(renda): Find a better way to do this
            if self.topic_handler_argument_map.__contains__(topic):
                wx.CallAfter(self.topic_handler_map[topic], *self.topic_handler_argument_map[topic], messagedata)
            else:
                wx.CallAfter(self.topic_handler_map[topic], messagedata)
