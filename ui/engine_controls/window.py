"""Renda Sim GUI Engine Controls Window"""

import wx


class EngineControls(wx.Frame):
    """Engine Controls Class"""

    def __init__(self, parent, title):
        super().__init__(parent, title=title)

        # Create Local Panel and Add Local Controls
        self.local_panel = wx.Panel(self, wx.ID_ANY, style=wx.SUNKEN_BORDER)
        self.local_label = wx.StaticText(self.local_panel, wx.ID_ANY, "Local Controls")

        self.start_local_btn = wx.Button(self.local_panel, wx.ID_ANY, "Start Local Engine")
        self.start_local_btn.SetBackgroundColour(wx.Colour("#ffcc00"))
        self.start_local_btn.SetForegroundColour(wx.Colour("black" if wx.SystemSettings.GetAppearance().IsDark() else "wxSYS_COLOUR_WINDOWTEXT"))

        self.connect_local_btn = wx.Button(self.local_panel, wx.ID_ANY, "Connect to Local Engine")
        self.connect_local_btn.SetBackgroundColour(wx.Colour("#ffcc00"))
        self.connect_local_btn.SetForegroundColour(wx.Colour("black" if wx.SystemSettings.GetAppearance().IsDark() else "wxSYS_COLOUR_WINDOWTEXT"))

        self.kill_local_btn = wx.Button(self.local_panel, wx.ID_ANY, "Kill Local Engine")
        self.kill_local_btn.SetBackgroundColour(wx.Colour("#ff4545"))
        self.kill_local_btn.SetForegroundColour(wx.Colour("white"))

        # Layout for Local Panel
        local_sizer = wx.BoxSizer(wx.VERTICAL)
        local_sizer.Add(self.local_label, 1, wx.ALL | wx.ALIGN_CENTER_HORIZONTAL, 5)
        local_buttons_sizer = wx.BoxSizer(wx.HORIZONTAL)
        local_buttons_sizer.Add(self.start_local_btn, 0, wx.ALL, 5)
        local_buttons_sizer.Add(self.connect_local_btn, 0, wx.ALL, 5)
        local_buttons_sizer.Add(self.kill_local_btn, 0, wx.ALL, 5)
        local_sizer.Add(local_buttons_sizer, 0, wx.ALL | wx.EXPAND, 5)
        self.local_panel.SetSizer(local_sizer)

        # Create Remote Panel and Add Remote Controls
        self.remote_panel = wx.Panel(self, wx.ID_ANY, style=wx.SUNKEN_BORDER)
        self.remote_label = wx.StaticText(self.remote_panel, wx.ID_ANY, "Remote Controls")

        self.ip_port_label = wx.StaticText(self.remote_panel, wx.ID_ANY, "Remote Address (IP:Port)")
        self.ip_port = wx.TextCtrl(self.remote_panel, wx.ID_ANY, "0.0.0.0:0000")

        self.connect_remote_btn = wx.Button(self.remote_panel, wx.ID_ANY, "Connect to Remote Engine")
        self.connect_remote_btn.SetBackgroundColour(wx.Colour("#ffcc00"))
        self.connect_remote_btn.SetForegroundColour(wx.Colour("black" if wx.SystemSettings.GetAppearance().IsDark() else "wxSYS_COLOUR_WINDOWTEXT"))

        # Layout for Remote Panel
        remote_sizer = wx.BoxSizer(wx.VERTICAL)
        remote_sizer.Add(self.remote_label, 1, wx.ALL | wx.ALIGN_CENTER_HORIZONTAL, 5)
        ip_sizer = wx.BoxSizer(wx.HORIZONTAL)
        ip_sizer.Add(self.ip_port_label, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        ip_sizer.Add(self.ip_port, 1, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        remote_sizer.Add(ip_sizer, 0, wx.ALL | wx.EXPAND, 5)
        remote_sizer.Add(self.connect_remote_btn, 0, wx.ALL | wx.EXPAND, 5)
        self.remote_panel.SetSizer(remote_sizer)

        # Main Layout: Add Panels
        main_sizer = wx.BoxSizer(wx.VERTICAL)
        main_sizer.Add(self.local_panel, 0, wx.ALL | wx.EXPAND, 10)
        main_sizer.Add(self.remote_panel, 0, wx.ALL | wx.EXPAND, 10)

        self.SetSizerAndFit(main_sizer)
