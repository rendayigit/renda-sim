"""Event handlers for Time Setter Window"""

from commanding import Commanding


class TimeSetterWindowHandlers:
    """Event handlers for Time Setter Window"""

    def __init__(self, time_setter, command_string):
        self.time_setter = time_setter
        self.command_string = command_string

    def on_update_duration(self, event):
        """Time Selection Handler"""
        event.Skip()

        hours = self.time_setter.hours_spin.GetValue()
        minutes = self.time_setter.minutes_spin.GetValue()
        seconds = self.time_setter.seconds_spin.GetValue()
        milliseconds = self.time_setter.milliseconds_spin.GetValue()

        total_milliseconds = (hours * 3600000) + (minutes * 60000) + (seconds * 1000) + milliseconds
        Commanding().request({"command": self.command_string, "millis": total_milliseconds})

    def on_cancel(self, event):
        """Cancel Handler"""
        event.Skip()

        self.time_setter.Close()
