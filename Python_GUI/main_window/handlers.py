"""Event handlers for Main Window"""

import threading
import time
import sys
import wx
from commanding import Commanding
from engine_controls.window import EngineControls
from time_setter.window import TimeSetter
from scale_setter.window import ScaleSetter

# For plotting
from plot.plot2 import GenericPlotter
from PyQt5.QtWidgets import QApplication


class MainWindowHandlers:
    """Event handlers for Main Window"""

    def __init__(self, main_window):
        self.main_window = main_window

        Commanding().request({"command": "STATUS"})

    def on_engine(self, _event):
        """Engine button callback"""
        engine_window = EngineControls(self.main_window, title="Engine Controls")
        engine_window.Show()

    def on_start_stop(self, _event):
        """Start/Stop button callback"""

        Commanding().request({"command": "STATUS"})

        if self.main_window.start_btn.GetLabel() == "Start":
            Commanding().request({"command": "START"})
        else:
            Commanding().request({"command": "STOP"})

    def on_reset(self, _event):
        """Reset button callback"""
        pass  # TODO: Implement

    def on_step(self, _event):
        """Step button callback"""
        Commanding().request({"command": "STEP"})

    def on_progress_sim(self, _event):
        """Run for button callback"""
        progress_sim_window = TimeSetter(self.main_window, "Progress Simulation", "PROGRESS_SIM")
        progress_sim_window.Show()

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
        scale_setter_window = ScaleSetter(self.main_window, "Set Simulation Rate", "SIM_RATE")
        scale_setter_window.Show()

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

            # If the selected item has children, iterate through them
            if child.IsOk():
                self._process_tree_children(item)
                return

            # If the selected item does not have children, process it directly
            self._process_tree_item(item)

    def _process_tree_children(self, parent_item):
        """Recursively process all children of a tree item."""
        child, cookie = self.main_window.models_tree.GetFirstChild(parent_item)
        while child.IsOk():
            # If the child has children, process them recursively
            if self.main_window.models_tree.ItemHasChildren(child):
                self._process_tree_children(child)
            else:
                self._process_tree_item(child)
            child, cookie = self.main_window.models_tree.GetNextChild(parent_item, cookie)

    def _process_tree_item(self, item):
        """Process a single tree item."""
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

        var = Commanding().request({"command": "VARIABLE_ADD", "variablePath": path})
        var_desc = var["variable"]["description"]
        var_value = str(var["variable"]["value"])
        var_type = var["variable"]["type"]

        item_index = self.main_window.variable_list.InsertItem(self.main_window.variable_list.GetItemCount(), path)
        self.main_window.variable_list.SetItem(item_index, 1, var_desc)
        self.main_window.variable_list.SetItem(item_index, 2, var_value)
        self.main_window.variable_list.SetItem(item_index, 3, var_type)

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

        item = wx.MenuItem(menu, wx.NewId(), "Plot")
        menu.Append(item)
        self.main_window.Bind(wx.EVT_MENU, handler=lambda _: self._plot(self.main_window.variable_list.GetFocusedItem()), id=item.GetId())

        if len(selection) != 0:
            item = wx.MenuItem(menu, wx.NewId(), "Remove Selection")
            menu.Append(item)
            self.main_window.Bind(
                wx.EVT_MENU, lambda _: [self._delete_item_by_name(self.main_window.variable_list, i) for i in selection], id=item.GetId()
            )

            item = wx.MenuItem(menu, wx.NewId(), "Plot Selection")
            menu.Append(item)
            self.main_window.Bind(wx.EVT_MENU, lambda _: [self._plot_items(i) for i in selection], id=item.GetId())

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
            Commanding().request({"command": "VARIABLE_REMOVE", "variablePath" : item.GetText() })

        list_ctrl.DeleteAllItems()

    def _delete_item_by_name(self, list_ctrl, item_name):
        Commanding().request({"command": "VARIABLE_REMOVE", "variablePath" : item_name })

        item_count = list_ctrl.GetItemCount()
        for i in range(item_count):
            item_text = list_ctrl.GetItemText(i)
            if item_text == item_name:
                list_ctrl.DeleteItem(i)
                break

    # FIXME: Crashes if adding a second plot
    def _plot(self, item):
        app = QApplication(sys.argv)

        plotter = GenericPlotter(title="Real-time Plotter", xlabel="Time (s)", ylabel="Values")
        plotter.show()

        def thread_loop():
            while True:
                name = self.main_window.variable_list.GetItemText(item, 0)
                value = self.main_window.variable_list.GetItemText(item, 2)
                sim_time = self.main_window.sim_time_display.GetValue()

                # FIXME Cannot figure out why sometimes they are ""
                if sim_time == "" or value == "":
                    continue

                wx.CallAfter(
                    plotter.add_variable,
                    name,
                    float(value),
                    float(sim_time),
                )

                time.sleep(0.1)  # sleep for 100 ms

        thread = threading.Thread(target=thread_loop)
        thread.start()

        app.exec_()

    def _plot_items(self, item_name):
        pass
        # TODO: implement
