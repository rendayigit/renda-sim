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
            var = Commanding().request("VARIABLE:" + path)
            var_desc, var_value, var_type = var.split(",")
            print(f"{var} -> {var_desc}, {var_value}, {type}")  # TODO(Renda): remove after testing

            item_index = self.main_window.variable_list.InsertItem(self.main_window.variable_list.GetItemCount(), path)
            self.main_window.variable_list.SetItem(item_index, 1, var_desc)
            self.main_window.variable_list.SetItem(item_index, 2, var_value)
            self.main_window.variable_list.SetItem(item_index, 3, var_type)
            test = Messaging(path, self.main_window.variable_list.SetItem, item_index, 2)  # TODO(Renda): need a way to terminate if var removed
            test.start()

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
        if len(selection) != 0:
            item = wx.MenuItem(menu, wx.NewId(), "Remove Selection")
            menu.Append(item)

        self.main_window.variable_list.PopupMenu(menu, event.GetPosition())
