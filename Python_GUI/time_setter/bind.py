"""Event binder for Time Setter Window"""

import wx
from time_setter.handlers import TimeSetterWindowHandlers


class TimeSetterWindowEventBinder:
    """Event binder for Time Setter Window"""

    def __init__(self, time_setter):
        self.time_setter = time_setter

        # Initialize handlers
        self.handlers = TimeSetterWindowHandlers(time_setter)

        self.time_setter.okay_btn.Bind(wx.EVT_BUTTON, self.handlers.on_update_duration)
        self.time_setter.cancel_btn.Bind(wx.EVT_BUTTON, self.handlers.on_cancel)
