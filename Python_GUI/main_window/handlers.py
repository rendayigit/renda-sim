"""Event handlers for Main Window"""

import wx
from commanding import Commanding
from engine_controls.window import EngineControls
from messaging import Messaging


class MainWindowHandlers:
    """Event handlers for Main Window"""

    def __init__(self, main_window):
        self.main_window = main_window

        scheduler_running = Commanding().request("SCHEDULER")

        if scheduler_running == "RUNNING":
            self._start()

    def on_engine(self, _event):
        """Engine button callback"""
        engine_window = EngineControls(None, title="Engine Controls")
        engine_window.Show()

    def on_start_stop(self, _event):
        """Start/Stop button callback"""

        scheduler_running = Commanding().request("SCHEDULER")

        if scheduler_running == "STOPPED":
            self._start()
            Commanding().transmit("START")
        else:
            self._stop()
            Commanding().transmit("STOP")

    def _start(self):
        """Start receiving sim time updates from the engine"""
        self.main_window.start_btn.SetLabel("Stop")
        self.main_window.SetStatusText("Simulation running...")

    def _stop(self):
        """Stop receiving sim time updates from the engine"""
        self.main_window.start_btn.SetLabel("Start")
        self.main_window.SetStatusText("Simulation stopped.")

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
        self.main_window.Close()

    def on_about(self, _event):
        """About button callback"""
        wx.MessageBox(
            "This is a simulator designed by Renda, see\nhttps://github.com/rendayigit/renda-sim\nfor more details.",
            "About",
            wx.OK | wx.ICON_INFORMATION,
        )

    def on_tree(self, _event):
        """Tree control callback"""
        item = self.main_window.models_tree.GetSelection()
        if item.IsOk():
            # Check if the selected item has children
            child, _ = self.main_window.models_tree.GetFirstChild(item)

            if child.IsOk():  # If the item has a valid child, skip the rest of the logic
                return

            parts = []
            while item.IsOk():
                parent = self.main_window.models_tree.GetItemParent(item)  # Get the parent item
                if not parent.IsOk():  # Skip if root item
                    break
                parts.insert(0, self.main_window.models_tree.GetItemText(item))  # Add the item's text at the beginning
                item = parent  # Move to the parent item
            path = ".".join(parts)  # Join all parts with a dot

            print(f"Selected path: {path}")  # TODO(Renda): remove after testing

            # If child is already being monitored, skip the rest of the logic
            for item in self._get_all_items(self.main_window.variable_list):
                if path == item.GetText():
                    return

            var = Commanding().request("VARIABLE_ADD:" + path)
            var_desc, var_value, var_type = var.split(",")

            print(f"{var} -> {var_desc}, {var_value}, {type}")  # TODO(Renda): remove after testing

            item_index = self.main_window.variable_list.InsertItem(self.main_window.variable_list.GetItemCount(), path)
            self.main_window.variable_list.SetItem(item_index, 1, var_desc)
            self.main_window.variable_list.SetItem(item_index, 2, var_value)
            self.main_window.variable_list.SetItem(item_index, 3, var_type)
            Messaging().add_topic_handler(path, self.main_window.variable_list.SetItem, item_index, 2)

    def on_list(self, event):
        """List control callback"""
        # Get selection
        selection = []
        item = self.main_window.variable_list.GetFirstSelected()
        while item != -1:
            selection.append(self.main_window.variable_list.GetItemText(item))
            item = self.main_window.variable_list.GetNextSelected(item)
        print(f"Selected items: {selection}")  # TODO(Renda): remove after testing

        menu = wx.Menu()
        item = wx.MenuItem(menu, wx.NewId(), "Remove All")
        menu.Append(item)
        self.main_window.Bind(wx.EVT_MENU, handler=lambda _: self._delete_all_items(self.main_window.variable_list), id=item.GetId())

        if len(selection) != 0:
            item = wx.MenuItem(menu, wx.NewId(), "Remove Selection")
            menu.Append(item)
            self.main_window.Bind(
                wx.EVT_MENU, lambda _: [self._delete_item_by_name(self.main_window.variable_list, i) for i in selection], id=item.GetId()
            )

            item = wx.MenuItem(menu, wx.NewId(), "Plot Selection")
            menu.Append(item)
            self.main_window.Bind(
                wx.EVT_MENU, lambda _: [self._plot_items(i) for i in selection], id=item.GetId()
            )

        self.main_window.variable_list.PopupMenu(menu, event.GetPosition())

    def _get_all_items(self, list_ctrl):
        item_list = []
        item_count = list_ctrl.GetItemCount()
        for i in range(item_count):
            item = list_ctrl.GetItem(i)
            item_list.append(item)
        return item_list

    def _delete_all_items(self, list_ctrl):
        for item in self._get_all_items(list_ctrl):
            Commanding().transmit("VARIABLE_REMOVE:" + item.GetText())

        list_ctrl.DeleteAllItems()

    def _delete_item_by_name(self, list_ctrl, item_name):
        Commanding().transmit("VARIABLE_REMOVE:" + item_name)

        item_count = list_ctrl.GetItemCount()
        for i in range(item_count):
            item_text = list_ctrl.GetItemText(i)
            if item_text == item_name:
                list_ctrl.DeleteItem(i)
                break

    def _plot_items(self, item_name):
        import sys
        from plot.plot2 import GenericPlotter
        from PyQt5.QtWidgets import QApplication
        
        app = QApplication(sys.argv)

        plotter = GenericPlotter(title="Real-time Plot", xlabel="Time (s)", ylabel="Variables")
        plotter.show()

        a = 0

        def update_table(time):
            plotter.add_variable(item_name, a, time)

        Messaging().add_topic_handler("SIM_TIME", update_table)
        Messaging().add_topic_handler(item_name, lambda val, a: val)

        sys.exit(app.exec_())