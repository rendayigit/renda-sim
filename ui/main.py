"""Module wx GUI Framework """

import wx


class Application(wx.App):
    """Main Application Class"""

    def OnInit(self):  # pylint: disable=invalid-name
        """Function called when UI is ready"""
        frame = MainWindow(None, title="Renda Sim GUI")
        frame.Show()
        return True


class MainWindow(wx.Frame):
    """Main Window Class"""

    def __init__(self, parent, title):
        super().__init__(parent, title=title)

        # Define custom IDs
        id_start_stop_btn = wx.NewIdRef()
        id_start_stop_menu = wx.NewIdRef()
        id_stop_at = wx.NewIdRef()
        id_stop_at_menu = wx.NewIdRef()
        id_stop_in = wx.NewIdRef()
        id_stop_in_menu = wx.NewIdRef()
        id_reset_btn = wx.NewIdRef()
        id_reset_menu = wx.NewIdRef()
        id_step_btn = wx.NewIdRef()
        id_step_menu = wx.NewIdRef()
        id_run_for_btn = wx.NewIdRef()
        id_run_for_menu = wx.NewIdRef()
        id_run_until_btn = wx.NewIdRef()
        id_run_until_menu = wx.NewIdRef()
        id_store_btn = wx.NewIdRef()
        id_store_menu = wx.NewIdRef()
        id_restore_btn = wx.NewIdRef()
        id_restore_menu = wx.NewIdRef()
        id_speed_btn = wx.NewIdRef()
        id_speed_menu = wx.NewIdRef()
        id_settings_btn = wx.NewIdRef()
        id_settings_menu = wx.NewIdRef()
        id_plot_btn = wx.NewIdRef()
        id_plot_menu = wx.NewIdRef()
        id_save_variables_menu = wx.NewIdRef()
        id_load_variables_menu = wx.NewIdRef()
        id_clear_variables_menu = wx.NewIdRef()
        id_models_tree = wx.NewIdRef()
        id_variables_list = wx.NewIdRef()

        self.CreateStatusBar()
        self.SetStatusText("Simulator ready")

        # Create a MenuBar
        menu_bar = wx.MenuBar()

        # Create the File Menu
        file_menu = wx.Menu()
        start_stop_menu_item = file_menu.Append(id_start_stop_menu, "&Start/Stop\tCtrl+R", "Start/Stop the simulation")
        reset_menu_item = file_menu.Append(id_reset_menu, "Reset\tCtrl+X", "Reset the simulation")
        stop_at_menu_item = file_menu.Append(id_stop_at_menu, "Stop At", "Stop the simulation at given time")
        stop_in_menu_item = file_menu.Append(id_stop_in_menu, "Stop In", "Stop the simulation in given amount of time")
        step_menu_item = file_menu.Append(id_step_menu, "Step", "Run the simulation 1 step")
        run_for_menu_item = file_menu.Append(id_run_for_menu, "Run For", "Run the simulation for given amount of time")
        run_until_menu_item = file_menu.Append(id_run_until_menu, "Run Until", "Run the simulation until given time")
        store_menu_item = file_menu.Append(id_store_menu, "Store", "Store the current simulation state")
        restore_menu_item = file_menu.Append(id_restore_menu, "Restore", "Restore the simulation state from file")
        speed_menu_item = file_menu.Append(id_speed_menu, "Speed", "Change the simulation speed")
        file_menu.AppendSeparator()
        settings_menu_item = file_menu.Append(id_settings_menu, "Settings", "Change the simulation settings")
        file_menu.AppendSeparator()
        quit_menu_item = file_menu.Append(wx.ID_EXIT, "&Quit\tCtrl+Q", "Quit the application")

        # Create the Variable Display Menu
        variable_display_menu = wx.Menu()
        plot_menu_item = variable_display_menu.Append(
            id_plot_menu, "&Plot Selected Variables\tCtrl+P", "Plot the variables"
        )
        variable_display_menu.AppendSeparator()
        save_variables_menu_item = variable_display_menu.Append(
            id_save_variables_menu, "&Save Variables", "Save the variables to file"
        )
        load_variables_menu_item = variable_display_menu.Append(
            id_load_variables_menu, "&Load Variables", "Load the variables from file"
        )
        variable_display_menu.AppendSeparator()
        clear_menu_item = variable_display_menu.Append(id_clear_variables_menu, "&Clear Table", "Clear the variables")

        # Create the Help Menu
        help_menu = wx.Menu()
        manual_menu_item = help_menu.Append(wx.ID_HELP, "&Manual\tF1", "Open The Manual")
        about_menu_item = help_menu.Append(wx.ID_ABOUT, "&About", "About Renda Sim")

        menu_bar.Append(file_menu, "&File")
        menu_bar.Append(variable_display_menu, "&Variable Display")
        menu_bar.Append(help_menu, "&Help")

        # Set the MenuBar for the frame
        self.SetMenuBar(menu_bar)

        # Bind menu events
        self.Bind(wx.EVT_MENU, self.on_start_stop, start_stop_menu_item)
        self.Bind(wx.EVT_MENU, self.on_stop_at, stop_at_menu_item)
        self.Bind(wx.EVT_MENU, self.on_stop_in, stop_in_menu_item)
        self.Bind(wx.EVT_MENU, self.on_reset, reset_menu_item)
        self.Bind(wx.EVT_MENU, self.on_step, step_menu_item)
        self.Bind(wx.EVT_MENU, self.on_run_for, run_for_menu_item)
        self.Bind(wx.EVT_MENU, self.on_run_until, run_until_menu_item)
        self.Bind(wx.EVT_MENU, self.on_store, store_menu_item)
        self.Bind(wx.EVT_MENU, self.on_restore, restore_menu_item)
        self.Bind(wx.EVT_MENU, self.on_speed, speed_menu_item)
        self.Bind(wx.EVT_MENU, self.on_settings, settings_menu_item)
        self.Bind(wx.EVT_MENU, self.on_quit, quit_menu_item)
        self.Bind(wx.EVT_MENU, self.on_about, about_menu_item)

        self.start_btn = wx.Button(self, id_start_stop_btn, "Start", wx.DefaultPosition, wx.DefaultSize)
        reset_btn = wx.Button(self, id_reset_btn, "Reset", wx.DefaultPosition, wx.DefaultSize)
        step_btn = wx.Button(self, id_step_btn, "Step", wx.DefaultPosition, wx.DefaultSize)
        store_btn = wx.Button(self, id_store_btn, "Store", wx.DefaultPosition, wx.DefaultSize)
        restore_btn = wx.Button(self, id_restore_btn, "Restore", wx.DefaultPosition, wx.DefaultSize)
        plot_btn = wx.Button(self, id_plot_btn, "Plot", wx.DefaultPosition, wx.DefaultSize)

        sim_time_label = wx.StaticText(self, wx.ID_ANY, "Simulation Time (s) ")

        sim_time_display = wx.TextCtrl(
            self,
            wx.ID_ANY,
            wx.EmptyString,
            wx.DefaultPosition,
            wx.DefaultSize,
            wx.TE_READONLY,
        )

        self.Bind(wx.EVT_BUTTON, self.on_start_stop, self.start_btn)
        self.Bind(wx.EVT_BUTTON, self.on_reset, reset_btn)
        self.Bind(wx.EVT_BUTTON, self.on_step, step_btn)
        self.Bind(wx.EVT_BUTTON, self.on_store, store_btn)
        self.Bind(wx.EVT_BUTTON, self.on_restore, restore_btn)
        self.Bind(wx.EVT_BUTTON, self.on_plot, plot_btn)

        top_horizontal_sizer = wx.BoxSizer(wx.HORIZONTAL)
        top_horizontal_sizer.Add(self.start_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(reset_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(step_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(store_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(restore_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(plot_btn, 0, wx.ALL | wx.ALIGN_CENTER_VERTICAL, 5)

        top_horizontal_sizer.AddStretchSpacer()
        top_horizontal_sizer.Add(sim_time_label, 0, wx.ALIGN_CENTER_VERTICAL, 5)
        top_horizontal_sizer.Add(sim_time_display, 0, wx.ALIGN_CENTER_VERTICAL, 5)

        # Create the models tree
        models_tree = wx.TreeCtrl(
            self,
            id_models_tree,
            wx.DefaultPosition,
            wx.Size(300, 400),
            wx.TR_HAS_BUTTONS | wx.TR_LINES_AT_ROOT,
        )

        # Create the variables list
        variable_list = wx.ListCtrl(
            self,
            id_variables_list,
            wx.DefaultPosition,
            wx.Size(1000, 400),
            wx.LC_REPORT,
        )

        variable_list.InsertColumn(0, "Variable", wx.LIST_FORMAT_LEFT, 200)
        variable_list.InsertColumn(1, "Description", wx.LIST_FORMAT_LEFT, 400)
        variable_list.InsertColumn(2, "Value", wx.LIST_FORMAT_LEFT, 150)
        variable_list.InsertColumn(3, "Type", wx.LIST_FORMAT_LEFT, 100)

        # Create the logs display
        logs = wx.TextCtrl(
            self,
            wx.ID_ANY,
            "",
            wx.DefaultPosition,
            wx.Size(1200, 100),
            wx.TE_READONLY | wx.TE_MULTILINE,
        )

        middle_horizontal_sizer = wx.BoxSizer(wx.HORIZONTAL)
        middle_horizontal_sizer.Add(models_tree, 0, wx.ALL | wx.EXPAND, 5)
        middle_horizontal_sizer.Add(variable_list, 1, wx.ALL | wx.EXPAND, 5)

        vertical_sizer = wx.BoxSizer(wx.VERTICAL)
        vertical_sizer.Add(top_horizontal_sizer, 0, wx.ALL | wx.EXPAND, 5)
        vertical_sizer.Add(middle_horizontal_sizer, 1, wx.ALL | wx.EXPAND, 5)
        vertical_sizer.Add(logs, 0, wx.ALL | wx.EXPAND, 5)

        self.SetSizerAndFit(vertical_sizer)

    # Event Handlers

    def on_start_stop(self, _event):
        """Start/Stop button callback"""
        self.start_btn.SetLabel("Stop")
        self.SetStatusText("Simulation running...")

        # TODO: Implement

    def on_stop_at(self, _event):
        """Stop at button callback"""
        pass  # TODO: Implement

    def on_stop_in(self, _event):
        """Stop in button callback"""
        pass  # TODO: Implement

    def on_reset(self, _event):
        """Reset button callback"""
        pass  # TODO: Implement

    def on_step(self, _event):
        """Step button callback"""
        pass  # TODO: Implement

    def on_run_for(self, _event):
        """Run for button callback"""
        pass  # TODO: Implement

    def on_run_until(self, _event):
        """Run until button callback"""
        pass  # TODO: Implement

    def on_store(self, _event):
        """Store button callback"""
        pass  # TODO: Implement

    def on_restore(self, _event):
        """Restore button callback"""
        pass  # TODO: Implement

    def on_plot(self, _event):
        """Plot button callback"""
        pass  # TODO: Implement

    def on_speed(self, _event):
        """Speed button callback"""
        pass  # TODO: Implement

    def on_settings(self, _event):
        """Settings button callback"""
        pass  # TODO: Implement

    def on_quit(self, _event):
        """Quit button callback"""
        self.Close()

    def on_about(self, _event):
        """About button callback"""
        wx.MessageBox(
            "This is a simulator designed by Renda, see \n"
            "https://github.com/rendayigit/renda-sim \n"
            "for more details.",
            "About",
            wx.OK | wx.ICON_INFORMATION,
        )


if __name__ == "__main__":
    app = Application()
    app.MainLoop()
