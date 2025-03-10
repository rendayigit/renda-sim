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

        self.common_colors = [
            (255, 0, 0),  # Red
            (0, 255, 0),  # Green
            (0, 0, 255),  # Blue
            (255, 255, 0),  # Yellow
            (255, 0, 255),  # Magenta
            (0, 255, 255),  # Cyan
            (128, 0, 0),  # Dark Red
            (0, 128, 0),  # Dark Green
            (0, 0, 128),  # Dark Blue
            (128, 128, 0),  # Brown
            (128, 0, 128),  # Purple
            (0, 128, 128),  # Teal
        ]

        self.color_index = 0

        self.plot_widget.addLegend()

    def add_variable(self, name, value, time):
        """Add a new variable with a given name, value, and time."""
        if name not in self.data:
            self.data[name] = {"x": [time], "y": [value]}
            color = self.common_colors[self.color_index]
            self.lines[name] = self.plot_widget.plot(pen=pg.mkPen(color=color), name=name)
            self.colors[name] = color
            self.color_index = (self.color_index + 1) % len(self.common_colors)
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
        plotter.add_variable("Value D", random.random() * 4, _time)
        plotter.add_variable("Value E", random.random() * 5, _time)
        plotter.add_variable("Value F", random.random() * 6, _time)
        _time += 1

    timer = QTimer()
    timer.timeout.connect(update_plot)
    timer.start(100)  # Update every 100ms

    sys.exit(app.exec_())

''' CONSIDERED USAGE
a = 0
b = 0
c = 0
time = 0

def update_table(): # loop
    plotter.add_variable("Value A", a, time)
    plotter.add_variable("Value B", b, time)
    plotter.add_variable("Value C", c, time)

def update_time(_time):
    time = _time

def update_a(_a):
    _a = a

Messaging().add_topic_handler("SIM_TIME", update_time)

Messaging().add_topic_handler("Value A", update_a)

Messaging().add_topic_handler("Value A", lambda val, a: val)
Messaging().add_topic_handler("Value B", lambda val, b: val)
Messaging().add_topic_handler("Value C", lambda val, c: val)
'''