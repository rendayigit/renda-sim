import wx

class Application(wx.App):
    def OnInit(self):
        frame = MainWindow(None, title="Renda Sim GUI")
        frame.Show()
        return True

class MainWindow(wx.Frame):
    def __init__(self, parent, title):
        super().__init__(parent, title=title)

        # Define custom IDs
        ID_START_STOP_BTN = wx.NewIdRef()
        ID_START_STOP_MENU = wx.NewIdRef()
        ID_STOP_AT = wx.NewIdRef()
        ID_STOP_AT_MENU = wx.NewIdRef()
        ID_STOP_IN = wx.NewIdRef()
        ID_STOP_IN_MENU = wx.NewIdRef()
        ID_RESET_BTN = wx.NewIdRef()
        ID_RESET_MENU = wx.NewIdRef()
        ID_STEP_BTN = wx.NewIdRef()
        ID_STEP_MENU = wx.NewIdRef()
        ID_RUN_FOR_BTN = wx.NewIdRef()
        ID_RUN_FOR_MENU = wx.NewIdRef()
        ID_RUN_UNTIL_BTN = wx.NewIdRef()
        ID_RUN_UNTIL_MENU = wx.NewIdRef()
        ID_STORE_BTN = wx.NewIdRef()
        ID_STORE_MENU = wx.NewIdRef()
        ID_RESTORE_BTN = wx.NewIdRef()
        ID_RESTORE_MENU = wx.NewIdRef()
        ID_SPEED_BTN = wx.NewIdRef()
        ID_SPEED_MENU = wx.NewIdRef()
        ID_SETTINGS_BTN = wx.NewIdRef()
        ID_SETTINGS_MENU = wx.NewIdRef()
        ID_PLOT_BTN = wx.NewIdRef()
        ID_PLOT_MENU = wx.NewIdRef()
        ID_SAVE_VARIABLES_MENU = wx.NewIdRef()
        ID_LOAD_VARIABLES_MENU = wx.NewIdRef()
        ID_CLEAR_VARIABLES_MENU = wx.NewIdRef()
        ID_MODELS_TREE = wx.NewIdRef()
        ID_VARIABLES_LIST = wx.NewIdRef()

        self.CreateStatusBar()
        self.SetStatusText("Simulator ready")

        # Create a MenuBar
        menuBar = wx.MenuBar()
        
        # Create the File Menu
        fileMenu = wx.Menu()
        startStopMenuItem = fileMenu.Append(ID_START_STOP_MENU, "&Start/Stop\tCtrl+R", "Start/Stop the simulation")
        resetMenuItem = fileMenu.Append(ID_RESET_MENU, "Reset\tCtrl+X", "Reset the simulation")
        stopAttackMenuItem = fileMenu.Append(ID_STOP_AT_MENU, "Stop At", "Stop the simulation at given time")
        stopInMenuItem = fileMenu.Append(ID_STOP_IN_MENU, "Stop In", "Stop the simulation in given amount of time")
        stepMenuItem = fileMenu.Append(ID_STEP_MENU, "Step", "Run the simulation 1 step")
        runForMenuItem = fileMenu.Append(ID_RUN_FOR_MENU, "Run For", "Run the simulation for given amount of time")
        runUntilMenuItem = fileMenu.Append(ID_RUN_UNTIL_MENU, "Run Until", "Run the simulation until given time")
        storeMenuItem = fileMenu.Append(ID_STORE_MENU, "Store", "Store the current simulation state")
        restoreMenuItem = fileMenu.Append(ID_RESTORE_MENU, "Restore", "Restore the simulation state from file")
        speedMenuItem = fileMenu.Append(ID_SPEED_MENU, "Speed", "Change the simulation speed")
        fileMenu.AppendSeparator()
        settingsMenuItem = fileMenu.Append(ID_SETTINGS_MENU, "Settings", "Change the simulation settings")
        fileMenu.AppendSeparator()
        quitMenuItem = fileMenu.Append(wx.ID_EXIT, "&Quit\tCtrl+Q", "Quit the application")

        # Create the Variable Display Menu
        variableDisplayMenu = wx.Menu()
        plotMenuItem = variableDisplayMenu.Append(ID_PLOT_MENU, "&Plot Selected Variables\tCtrl+P", "Plot the variables")
        variableDisplayMenu.AppendSeparator()
        saveVariablesMenuItem = variableDisplayMenu.Append(ID_SAVE_VARIABLES_MENU, "&Save Variables", "Save the variables to file")
        loadVariablesMenuItem = variableDisplayMenu.Append(ID_LOAD_VARIABLES_MENU, "&Load Variables", "Load the variables from file")
        variableDisplayMenu.AppendSeparator()
        clearMenuItem = variableDisplayMenu.Append(ID_CLEAR_VARIABLES_MENU, "&Clear Table", "Clear the variables")
        
        # Create the Help Menu
        helpMenu = wx.Menu()
        manualMenuItem = helpMenu.Append(wx.ID_HELP, "&Manual\tF1", "Open The Manual")
        aboutMenuItem = helpMenu.Append(wx.ID_ABOUT, "&About", "About Renda Sim")

        menuBar.Append(fileMenu, "&File")
        menuBar.Append(variableDisplayMenu, "&Variable Display")
        menuBar.Append(helpMenu, "&Help")
        
        # Set the MenuBar for the frame
        self.SetMenuBar(menuBar)
        
        # Bind menu events
        self.Bind(wx.EVT_MENU, self.onStartStop, startStopMenuItem)
        self.Bind(wx.EVT_MENU, self.onStopAttack, stopAttackMenuItem)
        self.Bind(wx.EVT_MENU, self.onStopIn, stopInMenuItem)
        self.Bind(wx.EVT_MENU, self.onReset, resetMenuItem)
        self.Bind(wx.EVT_MENU, self.onStep, stepMenuItem)
        self.Bind(wx.EVT_MENU, self.onRunFor, runForMenuItem)
        self.Bind(wx.EVT_MENU, self.onRunUntil, runUntilMenuItem)
        self.Bind(wx.EVT_MENU, self.onStore, storeMenuItem)
        self.Bind(wx.EVT_MENU, self.onRestore, restoreMenuItem)
        self.Bind(wx.EVT_MENU, self.onSpeed, speedMenuItem)
        self.Bind(wx.EVT_MENU, self.onSettings, settingsMenuItem)
        self.Bind(wx.EVT_MENU, self.onQuit, quitMenuItem)
        self.Bind(wx.EVT_MENU, self.onAbout, aboutMenuItem)

        startBtn = wx.Button(self, ID_START_STOP_BTN, "Start/Stop", wx.DefaultPosition, wx.DefaultSize)
        resetBtn = wx.Button(self, ID_RESET_BTN, "Reset", wx.DefaultPosition, wx.DefaultSize)
        stepBtn = wx.Button(self, ID_STEP_BTN, "Step", wx.DefaultPosition, wx.DefaultSize)
        storeBtn = wx.Button(self, ID_STORE_BTN, "Store", wx.DefaultPosition, wx.DefaultSize)
        restoreBtn = wx.Button(self, ID_RESTORE_BTN, "Restore", wx.DefaultPosition, wx.DefaultSize)
        plotBtn = wx.Button(self, ID_PLOT_BTN, "Plot", wx.DefaultPosition, wx.DefaultSize)

        self.Bind(wx.EVT_BUTTON, self.onStartStop, startBtn)
        self.Bind(wx.EVT_BUTTON, self.onReset, resetBtn)
        self.Bind(wx.EVT_BUTTON, self.onStep, stepBtn)
        self.Bind(wx.EVT_BUTTON, self.onStore, storeBtn)
        self.Bind(wx.EVT_BUTTON, self.onRestore, restoreBtn)
        self.Bind(wx.EVT_BUTTON, self.onPlot, plotBtn)
    
        topHorizontalSizer = wx.BoxSizer(wx.HORIZONTAL)
        topHorizontalSizer.Add(startBtn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        topHorizontalSizer.Add(resetBtn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        topHorizontalSizer.Add(stepBtn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        topHorizontalSizer.Add(storeBtn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        topHorizontalSizer.Add(restoreBtn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        topHorizontalSizer.Add(plotBtn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)

        verticalSizer = wx.BoxSizer(wx.VERTICAL)
        verticalSizer.Add(topHorizontalSizer, 0, wx.ALL | wx.EXPAND, 5)
        
        self.SetSizerAndFit(verticalSizer)

    # Event Handlers

    def onStartStop(self, event):
        #wx.MessageBox("Start", "Start Clicked", wx.OK | wx.ICON_INFORMATION)
        self.SetLabel("Stop") # FIXME

    def onStopAttack(self, event):
        pass

    def onStopIn(self, event):
        pass

    def onReset(self, event):
        pass

    def onStep(self, event):
        pass

    def onRunFor(self, event):
        pass

    def onRunUntil(self, event):
        pass

    def onStore(self, event):
        pass

    def onRestore(self, event):
        pass

    def onPlot(self, event):
        pass

    def onSpeed(self, event):
        pass

    def onSettings(self, event):
        pass
    
    def onQuit(self, event):
        self.Close()
    
    def onAbout(self, event):
        wx.MessageBox("This is a simulator designed by Renda, see \nhttps://github.com/rendayigit/renda-sim \nfor more details.", "About", wx.OK | wx.ICON_INFORMATION)

if __name__ == "__main__":
    app = Application()
    app.MainLoop()
