import sys
import math
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
from PyQt5.QtCore import QTimer
import pyqtgraph as pg


class GenericPlotter(QMainWindow):
    def __init__(self, title="Generic Plot", xlabel="X", ylabel="Y", max_data_points=100):
        super().__init__()

        self.data = {}  # Dictionary to store data for multiple plots
        self.max_data_points = max_data_points

        self.setWindowTitle(title)
        self.setGeometry(100, 100, 800, 600)

        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)

        self.layout = QVBoxLayout()
        self.central_widget.setLayout(self.layout)

        self.plot_widget = pg.PlotWidget(title=title)
        self.plot_widget.setLabel("bottom", xlabel)
        self.plot_widget.setLabel("left", ylabel)
        self.layout.addWidget(self.plot_widget)

        self.lines = {}  # Dictionary to store line objects for each plot
        self.time = 0

    def add_plot(self, name, color):
        """Add a new plot with a given name and line color."""
        self.data[name] = {"x": [], "y": []}
        self.lines[name] = self.plot_widget.plot(pen=pg.mkPen(color=color), name=name)

    def update_plot(self):
        for name, line in self.lines.items():
            new_y = math.sin(self.time) if name == "sin" else math.cos(self.time)
            self.data[name]["x"].append(self.time)
            self.data[name]["y"].append(new_y)

            # Limit data points to maintain performance
            if len(self.data[name]["x"]) > self.max_data_points:
                self.data[name]["x"] = self.data[name]["x"][-self.max_data_points :]
                self.data[name]["y"] = self.data[name]["y"][-self.max_data_points :]

            # Update line data efficiently
            line.setData(self.data[name]["x"], self.data[name]["y"])

        # Dynamically adjust x and y-axis limits
        all_x = [val for sublist in [d["x"] for d in self.data.values()] for val in sublist]
        all_y = [val for sublist in [d["y"] for d in self.data.values()] for val in sublist]

        if all_x and all_y:
            xmin, xmax = min(all_x), max(all_x)
            ymin, ymax = min(all_y), max(all_y)
            x_range = xmax - xmin
            y_range = ymax - ymin
            self.plot_widget.setXRange(xmin - 0.1 * x_range, xmax + 0.1 * x_range)
            self.plot_widget.setYRange(ymin - 0.1 * y_range, ymax + 0.1 * y_range)

        self.time += 0.1


if __name__ == "__main__":
    app = QApplication(sys.argv)

    plotter = GenericPlotter(title="Real-time Plot", xlabel="Time (s)", ylabel="Value")

    # TODO: Instead of doing these 4 lines, we need to have a single function that takes a variable name
    # and a variable value. Every time a new variable is added via this function the table shall add a new plot for this
    # variable along with its value. And every time a new value for an existent variable is provided via
    # this function the value of the already added plot shall be updated.
    plotter.add_plot("sin", (255, 0, 0))  # Red
    plotter.add_plot("cos", (0, 0, 255))  # Blue
    plotter.data["sin"] = {"x": [], "y": []}
    plotter.data["cos"] = {"x": [], "y": []}

    plotter.show()

    timer = QTimer()
    timer.timeout.connect(plotter.update_plot)
    timer.start(100)  # Update every 100ms

    sys.exit(app.exec_())
