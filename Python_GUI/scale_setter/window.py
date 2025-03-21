"""Renda Sim GUI Scale Setter Window"""

import wx
from scale_setter.bind import ScaleSetterWindowEventBinder


class ScaleSetter(wx.Frame):
    """Scale Setter Class"""

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

        scale_selection_sizer = wx.BoxSizer(wx.HORIZONTAL)

        self.scale_label = wx.StaticText(self, label="Scale:")
        self.scale_text = wx.TextCtrl(self, value="1.0")
        self.scale_slider = wx.Slider(self, value=10, minValue=10, maxValue=100, style=wx.SL_HORIZONTAL)

        scale_selection_sizer.Add(self.scale_label, 0, wx.ALL | wx.CENTER, 5)
        scale_selection_sizer.Add(self.scale_text, 0, wx.ALL, 5)
        scale_selection_sizer.Add(self.scale_slider, 1, wx.ALL | wx.EXPAND, 5)

        main_sizer = wx.BoxSizer(wx.VERTICAL)
        main_sizer.Add(scale_selection_sizer, 0, wx.ALL | wx.EXPAND, 10)
        main_sizer.Add(controls_sizer, 0, wx.ALL | wx.EXPAND, 10)

        self.SetSizerAndFit(main_sizer)

        ScaleSetterWindowEventBinder(self, command_string)

    