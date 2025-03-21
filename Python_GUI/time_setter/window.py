"""Renda Sim GUI Time Setter Window"""

import wx
from time_setter.bind import TimeSetterWindowEventBinder


class TimeSetter(wx.Frame):
    """Time Setter Class"""

    def __init__(self, parent, title, command_string):
        super().__init__(parent, title=title)

        controls_sizer = wx.BoxSizer(wx.HORIZONTAL)
        controls_sizer.AddStretchSpacer()

        self.okay_btn = wx.Button(self, wx.ID_ANY, "Okay")
        self.okay_btn.SetBackgroundColour(wx.Colour("#ffcc00"))
        self.okay_btn.SetForegroundColour(wx.Colour("black" if wx.SystemSettings.GetAppearance().IsDark() else "wxSYS_COLOUR_WINDOWTEXT"))
        controls_sizer.Add(self.okay_btn, 0, wx.ALL, 5)

        self.cancel_btn = wx.Button(self, wx.ID_ANY, "Cancel")
        self.cancel_btn.SetBackgroundColour(wx.Colour("#ff4545"))
        self.cancel_btn.SetForegroundColour(wx.Colour("white"))
        controls_sizer.Add(self.cancel_btn, 0, wx.ALL, 5)

        self.hours_label = wx.StaticText(self, label="Hours:")
        self.hours_spin = wx.SpinCtrl(self, value="0", min=0, max=23)

        self.minutes_label = wx.StaticText(self, label="Minutes:")
        self.minutes_spin = wx.SpinCtrl(self, value="0", min=0, max=59)

        self.seconds_label = wx.StaticText(self, label="Seconds:")
        self.seconds_spin = wx.SpinCtrl(self, value="0", min=0, max=59)

        self.milliseconds_label = wx.StaticText(self, label="Milliseconds:")
        self.milliseconds_spin = wx.SpinCtrl(self, value="0", min=0, max=1000)

        time_selection_sizer = wx.BoxSizer(wx.HORIZONTAL)

        hours_sizer = wx.BoxSizer(wx.HORIZONTAL)
        hours_sizer.Add(self.hours_label, 0, wx.ALL | wx.CENTER, 5)
        hours_sizer.Add(self.hours_spin, 0, wx.ALL, 5)
        time_selection_sizer.Add(hours_sizer)

        minutes_sizer = wx.BoxSizer(wx.HORIZONTAL)
        minutes_sizer.Add(self.minutes_label, 0, wx.ALL | wx.CENTER, 5)
        minutes_sizer.Add(self.minutes_spin, 0, wx.ALL, 5)
        time_selection_sizer.Add(minutes_sizer)

        seconds_sizer = wx.BoxSizer(wx.HORIZONTAL)
        seconds_sizer.Add(self.seconds_label, 0, wx.ALL | wx.CENTER, 5)
        seconds_sizer.Add(self.seconds_spin, 0, wx.ALL, 5)
        time_selection_sizer.Add(seconds_sizer)

        milliseconds_sizer = wx.BoxSizer(wx.HORIZONTAL)
        milliseconds_sizer.Add(self.milliseconds_label, 0, wx.ALL | wx.CENTER, 5)
        milliseconds_sizer.Add(self.milliseconds_spin, 0, wx.ALL, 5)
        time_selection_sizer.Add(milliseconds_sizer)

        # Main Layout: Add Panels
        main_sizer = wx.BoxSizer(wx.VERTICAL)
        main_sizer.Add(time_selection_sizer, 0, wx.ALL | wx.EXPAND, 10)
        main_sizer.Add(controls_sizer, 0, wx.ALL | wx.EXPAND, 10)

        self.SetSizerAndFit(main_sizer)

        TimeSetterWindowEventBinder(self, command_string)
