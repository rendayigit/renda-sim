"""Event handlers for Main Window"""

import wx


class MainWindowHandlers:
    """Event handlers for Main Window"""

    def __init__(self, main_window):
        self.main_window = main_window

    def on_start_stop(self, _event):
        """Start/Stop button callback"""
        self.main_window.start_btn.SetLabel("Stop")
        self.main_window.SetStatusText("Simulation running...")

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
        pass  # TODO: Implement
