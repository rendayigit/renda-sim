"""Renda Sim GUI Main Window"""

import wx
from main_window.bind import MainWindowEventBinder


class MainWindow(wx.Frame):
    """Main Window Class"""

    def __init__(self, parent, title):
        super().__init__(parent, title=title)

        self.CreateStatusBar()
        self.SetStatusText("Simulator ready")

        # Create a MenuBar
        menu_bar = wx.MenuBar()

        # Create the File Menu
        file_menu = wx.Menu()
        self.start_stop_menu_item = file_menu.Append(wx.ID_ANY, "&Start/Stop\tCtrl+R", "Start/Stop the simulation")
        self.reset_menu_item = file_menu.Append(wx.ID_ANY, "Reset\tCtrl+X", "Reset the simulation")
        self.stop_at_menu_item = file_menu.Append(wx.ID_ANY, "Stop At", "Stop the simulation at given time")
        self.stop_in_menu_item = file_menu.Append(wx.ID_ANY, "Stop In", "Stop the simulation in given amount of time")
        self.step_menu_item = file_menu.Append(wx.ID_ANY, "Step", "Run the simulation 1 step")
        self.run_for_menu_item = file_menu.Append(wx.ID_ANY, "Run For", "Run the simulation for given amount of time")
        self.run_until_menu_item = file_menu.Append(wx.ID_ANY, "Run Until", "Run the simulation until given time")
        self.store_menu_item = file_menu.Append(wx.ID_ANY, "Store", "Store the current simulation state")
        self.restore_menu_item = file_menu.Append(wx.ID_ANY, "Restore", "Restore the simulation state from file")
        self.speed_menu_item = file_menu.Append(wx.ID_ANY, "Speed", "Change the simulation speed")
        file_menu.AppendSeparator()
        self.settings_menu_item = file_menu.Append(wx.ID_ANY, "Settings", "Change the simulation settings")
        file_menu.AppendSeparator()
        self.quit_menu_item = file_menu.Append(wx.ID_EXIT, "&Quit\tCtrl+Q", "Quit the application")

        # Create the Variable Display Menu
        variable_display_menu = wx.Menu()
        self.plot_menu_item = variable_display_menu.Append(wx.ID_ANY, "&Plot Selected Variables\tCtrl+P", "Plot the variables")
        variable_display_menu.AppendSeparator()
        self.save_variables_menu_item = variable_display_menu.Append(wx.ID_ANY, "&Save Variables", "Save the variables to file")
        self.load_variables_menu_item = variable_display_menu.Append(wx.ID_ANY, "&Load Variables", "Load the variables from file")
        variable_display_menu.AppendSeparator()
        self.clear_menu_item = variable_display_menu.Append(wx.ID_ANY, "&Clear Table", "Clear the variables")

        # Create the Help Menu
        help_menu = wx.Menu()
        self.manual_menu_item = help_menu.Append(wx.ID_HELP, "&Manual\tF1", "Open The Manual")
        self.about_menu_item = help_menu.Append(wx.ID_ABOUT, "&About", "About Renda Sim")

        menu_bar.Append(file_menu, "&File")
        menu_bar.Append(variable_display_menu, "&Variable Display")
        menu_bar.Append(help_menu, "&Help")

        # Set the MenuBar for the frame
        self.SetMenuBar(menu_bar)

        self.start_btn = wx.Button(self, wx.ID_ANY, "Start", wx.DefaultPosition, wx.DefaultSize)

        self.start_btn.SetBackgroundColour(wx.Colour("#ffcc00"))
        self.start_btn.SetForegroundColour(wx.Colour("black" if wx.SystemSettings.GetAppearance().IsDark() else "wxSYS_COLOUR_WINDOWTEXT"))

        self.reset_btn = wx.Button(self, wx.ID_ANY, "Reset", wx.DefaultPosition, wx.DefaultSize)

        self.reset_btn.SetBackgroundColour(wx.Colour("#ff4545"))
        self.reset_btn.SetForegroundColour(wx.Colour("white"))

        self.step_btn = wx.Button(self, wx.ID_ANY, "Step", wx.DefaultPosition, wx.DefaultSize)
        self.store_btn = wx.Button(self, wx.ID_ANY, "Store", wx.DefaultPosition, wx.DefaultSize)
        self.restore_btn = wx.Button(self, wx.ID_ANY, "Restore", wx.DefaultPosition, wx.DefaultSize)
        self.plot_btn = wx.Button(self, wx.ID_ANY, "Plot", wx.DefaultPosition, wx.DefaultSize)

        sim_time_label = wx.StaticText(self, wx.ID_ANY, "Simulation Time (s) ")

        sim_time_display = wx.TextCtrl(
            self,
            wx.ID_ANY,
            wx.EmptyString,
            wx.DefaultPosition,
            wx.DefaultSize,
            wx.TE_READONLY,
        )

        top_horizontal_sizer = wx.BoxSizer(wx.HORIZONTAL)
        top_horizontal_sizer.Add(self.start_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(self.reset_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(self.step_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(self.store_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(self.restore_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(self.plot_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)

        top_horizontal_sizer.AddStretchSpacer()
        top_horizontal_sizer.Add(sim_time_label, 0, wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(sim_time_display, 0, wx.ALIGN_CENTER_VERTICAL, 5)

        # Create the models tree
        self.models_tree = wx.TreeCtrl(
            self,
            wx.ID_ANY,
            wx.DefaultPosition,
            wx.Size(300, 400),
            wx.TR_HAS_BUTTONS | wx.TR_LINES_AT_ROOT,
        )

        self.tree_root = self.models_tree.AddRoot("Simulation Models")
        self.models_tree.Expand(self.tree_root)

        # Create the variables list
        self.variable_list = wx.ListCtrl(
            self,
            wx.ID_ANY,
            wx.DefaultPosition,
            wx.Size(1000, 400),
            wx.LC_REPORT,
        )

        self.variable_list.InsertColumn(0, "Variable", wx.LIST_FORMAT_LEFT, 200)
        self.variable_list.InsertColumn(1, "Description", wx.LIST_FORMAT_LEFT, 400)
        self.variable_list.InsertColumn(2, "Value", wx.LIST_FORMAT_LEFT, 150)
        self.variable_list.InsertColumn(3, "Type", wx.LIST_FORMAT_LEFT, 100)

        # Create the logs display
        self.logs = wx.TextCtrl(
            self,
            wx.ID_ANY,
            "",
            wx.DefaultPosition,
            wx.Size(1200, 100),
            wx.TE_READONLY | wx.TE_MULTILINE,
        )

        middle_horizontal_sizer = wx.BoxSizer(wx.HORIZONTAL)
        middle_horizontal_sizer.Add(self.models_tree, 0, wx.ALL | wx.EXPAND, 5)
        middle_horizontal_sizer.Add(self.variable_list, 1, wx.ALL | wx.EXPAND, 5)

        vertical_sizer = wx.BoxSizer(wx.VERTICAL)
        vertical_sizer.Add(top_horizontal_sizer, 0, wx.ALL | wx.EXPAND, 5)
        vertical_sizer.Add(middle_horizontal_sizer, 1, wx.ALL | wx.EXPAND, 5)
        vertical_sizer.Add(self.logs, 0, wx.ALL | wx.EXPAND, 5)

        self.SetSizerAndFit(vertical_sizer)

        # Initialize binders
        self.binder = MainWindowEventBinder(self)
