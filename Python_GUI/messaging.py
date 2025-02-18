"""Messaging utilities for GUI"""

import threading
import json
import wx
import zmq


class Messaging:
    """Messaging utilities for GUI"""

    _instance = None  # Class-level instance variable for singleton implementation

    def __new__(cls, main_window):
        """Singleton instance"""
        if cls._instance is None:
            cls.main_window = main_window
            # Create the singleton instance
            cls._instance = super(Messaging, cls).__new__(cls)

            # Initialize ZeroMQ context and socket
            cls._instance.context = zmq.Context(1)
            cls._instance.subscriber = cls._instance.context.socket(zmq.SUB)
            cls._instance.subscriber.connect("tcp://localhost:12345")
            cls._instance.subscriber.set(zmq.SUBSCRIBE, "TIME".encode())
            cls._instance.subscriber.set(zmq.SUBSCRIBE, "EVENT".encode())
            cls._instance.subscriber.set(zmq.SUBSCRIBE, "VARIABLE".encode())

            cls._instance.is_running = False

        return cls._instance

    def __init__(self, main_window):
        # Explicitly define attributes for better static analysis
        if not hasattr(self, "subscriber"):  # Prevent reinitialization in the singleton
            self.main_window = main_window
            self.subscriber = None
            self.is_running = False
            self.thread = threading.Thread(target=self._messaging_thread)

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
            command_json = json.loads(bytes(frames[1]).decode())

            # TODO(renda): Find a better way to do this
            if topic == "TIME":
                wx.CallAfter(self.main_window.sim_time_display.ChangeValue, command_json["simTime"])
            elif topic == "EVENT":
                log = "[" + command_json["level"] + "] " + command_json["log"] + "\n"
                wx.CallAfter(self.main_window.event_logs.AppendText, log)
            elif topic == "VARIABLE":
                for i in range(self.main_window.variable_list.GetItemCount()):
                    if self.main_window.variable_list.GetItem(i).GetText() == command_json["variablePath"]:
                        wx.CallAfter(self.main_window.variable_list.SetItem, i, 2, str(command_json["variableValue"]))

            # if self.topic_handler_argument_map.__contains__(topic):
            #     wx.CallAfter(self.topic_handler_map[topic], *self.topic_handler_argument_map[topic], messagedata)
            # else:
            #     wx.CallAfter(self.topic_handler_map[topic], messagedata)
