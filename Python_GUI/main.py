"""Renda Sim GUI Main Application"""

import wx
from main_window.window import MainWindow
from main_window.window import populate_tree
from main_window.bind import MainWindowEventBinder
from commanding import Commanding
from messaging import Messaging


class Application(wx.App):
    """Main Application Class"""

    def OnInit(self):  # pylint: disable=invalid-name
        """Function called when UI is ready"""
        main_window = MainWindow(None, title="Renda Sim GUI")
        main_window.Show()

        # Initialize binders
        binder = MainWindowEventBinder(main_window)

        model_tree_json = Commanding().request_json("MODEL_TREE")
        populate_tree(main_window.models_tree, model_tree_json, main_window.tree_root)

        Messaging().add_topic_handler("SIM_TIME", main_window.sim_time_display.ChangeValue)

        Messaging().add_topic_handler("EVENT_LOG", main_window.event_logs.AppendText)

        return True


if __name__ == "__main__":
    app = Application()
    app.MainLoop()
