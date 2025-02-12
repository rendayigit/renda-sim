import sys
import random
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QWidget
from PyQt5.QtCore import QTimer
import pyqtgraph as pg


class GenericPlotter(QMainWindow):
    def __init__(self, title="Generic Plot", xlabel="X", ylabel="Y", max_data_points=100):
        super().__init__()

        self.data = {}  # Dictionary to store data for multiple plots
        self.max_data_points = max_data_points

        self.setWindowTitle(title)

        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)

        self.layout = QVBoxLayout()
        self.central_widget.setLayout(self.layout)

        self.plot_widget = pg.PlotWidget(title=title)
        self.plot_widget.setLabel("bottom", xlabel)
        self.plot_widget.setLabel("left", ylabel)
        self.layout.addWidget(self.plot_widget)

        self.lines = {}  # Dictionary to store line objects for each plot
        self.colors = {}  # Dictionary to store colors for each plot

        self.plot_widget.addLegend()

    def add_variable(self, name, value, time):
        """Add a new variable with a given name, value, and time."""
        if name not in self.data:
            self.data[name] = {"x": [time], "y": [value]}
            self.lines[name] = self.plot_widget.plot(
                pen=pg.mkPen(color=(255, 0, 0) if len(self.lines) == 0 else (0, 255, 0) if len(self.lines) == 1 else (0, 0, 255)), name=name
            )
            self.colors[name] = (255, 0, 0) if len(self.lines) == 0 else (0, 255, 0) if len(self.lines) == 1 else (0, 0, 255)
        else:
            self.data[name]["x"].append(time)
            self.data[name]["y"].append(value)

            # Limit data points to maintain performance
            if len(self.data[name]["x"]) > self.max_data_points:
                self.data[name]["x"] = self.data[name]["x"][-self.max_data_points :]
                self.data[name]["y"] = self.data[name]["y"][-self.max_data_points :]

        # Update line data efficiently
        self.lines[name].setData(self.data[name]["x"], self.data[name]["y"])

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


if __name__ == "__main__":
    app = QApplication(sys.argv)

    plotter = GenericPlotter(title="Real-time Plot", xlabel="Time (s)", ylabel="Value")
    plotter.show()

    _time = 0

    def update_plot():
        global _time
        plotter.add_variable("Value A", random.random(), _time)
        plotter.add_variable("Value B", random.random() * 2, _time)
        plotter.add_variable("Value C", random.random() * 3 - 1.5, _time)
        _time += 1

    timer = QTimer()
    timer.timeout.connect(update_plot)
    timer.start(100)  # Update every 100ms

    sys.exit(app.exec_())
