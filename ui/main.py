import wx

class Application(wx.App):
    def __init__(self):
        super().__init__()
        
        frame = wx.Frame(parent=None, title='Renda Sim GUI')
        frame.Show()

class MainWindow(wx.Frame):
    def __init__(self, parent, title):
        super().__init__(parent=parent, title=title)

    def OnInit(self):
        pass

if __name__ == '__main__':
    app = Application()
    app.MainLoop()