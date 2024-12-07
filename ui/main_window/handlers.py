"""Event handlers for Main Window"""

import wx
from messaging import Messaging
from commanding import Commanding


class MainWindowHandlers:
    """Event handlers for Main Window"""

    def __init__(self, main_window):
        self.main_window = main_window

        self.messaging = Messaging("SIM_TIME", self.main_window.sim_time_display.ChangeValue)

        event_logging = Messaging("EVENT_LOG", self.main_window.event_logs.AppendText)
        event_logging.start()

        scheduler_running = Commanding().request("SCHEDULER_STATUS")

        if scheduler_running == "RUNNING":
            self._start()

    def on_start_stop(self, _event):
        """Start/Stop button callback"""

        scheduler_running = Commanding().request("SCHEDULER_STATUS")

        if scheduler_running == "STOPPED":
            self._start()
            Commanding().transmit("START")
        else:
            self._stop()
            Commanding().transmit("STOP")

    def _start(self):
        """Start receiving sim time updates from the engine"""
        self.messaging.start()
        self.main_window.start_btn.SetLabel("Stop")
        self.main_window.SetStatusText("Simulation running...")

    def _stop(self):
        """Stop receiving sim time updates from the engine"""
        self.messaging.stop()
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
        pass  # TODO: Implement
