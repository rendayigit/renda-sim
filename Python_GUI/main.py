"""Renda Sim GUI Main Application"""

import json
import wx
from main_window.window import MainWindow
from main_window.window import populate_tree
from commanding import Commanding
from messaging import Messaging


class Application(wx.App):
    """Main Application Class"""

    def OnInit(self):  # pylint: disable=invalid-name
        """Function called when UI is ready"""
        main_window = MainWindow(None, title="Renda Sim GUI")
        main_window.Show()

        model_tree_json = Commanding().request({"command": "MODEL_TREE"})

        populate_tree(main_window.models_tree, model_tree_json["modelTree"], main_window.tree_root)

        Messaging(main_window).start()

        return True


if __name__ == "__main__":
    app = Application()
    app.MainLoop()
