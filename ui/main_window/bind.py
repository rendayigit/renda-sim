"""Event binder for Main Window"""

import wx
from main_window.handlers import MainWindowHandlers


class MainWindowEventBinder:
    """Event binder for Main Window"""

    def __init__(self, main_window):
        self.main_window = main_window

        # Initialize handlers
        self.handlers = MainWindowHandlers(main_window)

        # Bind menu events
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_start_stop, self.main_window.start_stop_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_stop_at, self.main_window.stop_at_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_stop_in, self.main_window.stop_in_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_reset, self.main_window.reset_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_step, self.main_window.step_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_run_for, self.main_window.run_for_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_run_until, self.main_window.run_until_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_store, self.main_window.store_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_restore, self.main_window.restore_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_speed, self.main_window.speed_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_settings, self.main_window.settings_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_quit, self.main_window.quit_menu_item)
        self.main_window.Bind(wx.EVT_MENU, self.handlers.on_about, self.main_window.about_menu_item)

        # Bind button events
        self.main_window.Bind(wx.EVT_BUTTON, self.handlers.on_start_stop, self.main_window.start_btn)
        self.main_window.Bind(wx.EVT_BUTTON, self.handlers.on_reset, self.main_window.reset_btn)
        self.main_window.Bind(wx.EVT_BUTTON, self.handlers.on_step, self.main_window.step_btn)
        self.main_window.Bind(wx.EVT_BUTTON, self.handlers.on_store, self.main_window.store_btn)
        self.main_window.Bind(wx.EVT_BUTTON, self.handlers.on_restore, self.main_window.restore_btn)
        self.main_window.Bind(wx.EVT_BUTTON, self.handlers.on_plot, self.main_window.plot_btn)
