"""Event binder for Scale Setter Window"""

import wx
from scale_setter.handlers import ScaleSetterWindowHandlers


class ScaleSetterWindowEventBinder:
    """Event binder for Scale Setter Window"""

    def __init__(self, scale_setter, command_string):
        self.scale_setter = scale_setter

        # Initialize handlers
        self.handlers = ScaleSetterWindowHandlers(scale_setter, command_string)

        self.scale_setter.scale_slider.Bind(wx.EVT_SLIDER, self.handlers.on_slider_change)
        self.scale_setter.okay_btn.Bind(wx.EVT_BUTTON, self.handlers.on_update_scale)
        self.scale_setter.cancel_btn.Bind(wx.EVT_BUTTON, self.handlers.on_cancel)
