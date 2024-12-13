import threading
import time
import matplotlib.pyplot as plt
import math


class GenericPlotter:
    def __init__(self, title="Generic Plot", xlabel="X", ylabel="Y", max_data_points=100):
        self.fig, self.ax = plt.subplots()
        self.xdata, self.ydata = [], []
        self.max_data_points = max_data_points

        self.title = title
        self.xlabel = xlabel
        self.ylabel = ylabel

        self.ax.set_title(self.title)
        self.ax.set_xlabel(self.xlabel)
        self.ax.set_ylabel(self.ylabel)
        self.ax.set_autoscaley_on(True)

        # Create a line object and store it
        self.line, = self.ax.plot([], [], 'ro-')

        self.time = 0

    def update_plot(self, new_y):
        self.xdata.append(self.time)
        self.ydata.append(new_y)

        # Limit data points to maintain performance
        if len(self.xdata) > self.max_data_points:
            self.xdata = self.xdata[-self.max_data_points:]
            self.ydata = self.ydata[-self.max_data_points:]

        # Update line data efficiently
        self.line.set_data(self.xdata, self.ydata)

        # Dynamically adjust x and y-axis limits
        xmin, xmax = min(self.xdata), max(self.xdata)
        ymin, ymax = min(self.ydata), max(self.ydata)
        x_range = xmax - xmin
        y_range = ymax - ymin
        self.ax.set_xlim(xmin - 0.1 * x_range, xmax + 0.1 * x_range)
        self.ax.set_ylim(ymin - 0.1 * y_range, ymax + 0.1 * y_range)

        self.fig.canvas.draw()
        self.fig.canvas.flush_events()
        self.time = self.time + 1  # TODO: increment with last sim time delta

    def start_test_thread(self):
        def test_thread_func():
            x_val = 0
            while True:
                self.update_plot(math.sin(x_val))
                x_val += 0.1
                time.sleep(0.01)

        test_thread = threading.Thread(target=test_thread_func)
        test_thread.start()

    def show(self):
        plt.show()


if __name__ == "__main__":
    plotter = GenericPlotter(title="Real-time Plot", xlabel="Time (s)", ylabel="Value")
    plotter.start_test_thread()
    plotter.show()