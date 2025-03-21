"""Event handlers for Scale Setter Window"""

import wx
from commanding import Commanding


class ScaleSetterWindowHandlers:
    """Event handlers for Scale Setter Window"""

    def __init__(self, scale_setter, command_string):
        self.scale_setter = scale_setter
        self.command_string = command_string

    def on_cancel(self, event):
        """Cancel Handler"""
        event.Skip()

        self.scale_setter.Close()

    def on_slider_change(self, event):
        """Updates the text control when the slider changes."""
        event.Skip()
        scale_value = self.scale_setter.scale_slider.GetValue() / 10.0
        self.scale_setter.scale_text.SetValue(str(scale_value))

    def on_update_scale(self, event):
        """Scale Selection Handler"""
        event.Skip()
        try:
            scale_value = float(self.scale_setter.scale_text.GetValue())
            if scale_value <= 0.0:
                wx.MessageBox("Scale must be positive", "Invalid Input", wx.OK | wx.ICON_ERROR)
                self.scale_setter.scale_text.SetValue("1.0")
            else:
                self.scale_setter.scale_slider.SetValue(int(scale_value * 10))
                Commanding().request({"command": self.command_string, "rate": scale_value})
        except ValueError:
            wx.MessageBox("Invalid scale value. Please enter a number.", "Invalid Input", wx.OK | wx.ICON_ERROR)
            self.scale_setter.scale_text.SetValue("1.0")
