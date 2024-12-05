"""Renda Sim GUI Main Application"""

import wx
from main_window.window import MainWindow
from messaging import Messaging


class Application(wx.App):
    """Main Application Class"""

    def OnInit(self):  # pylint: disable=invalid-name
        """Function called when UI is ready"""
        frame = MainWindow(None, title="Renda Sim GUI")
        frame.Show()
        messaging = Messaging(frame)
        return True


if __name__ == "__main__":
    app = Application()
    app.MainLoop()
