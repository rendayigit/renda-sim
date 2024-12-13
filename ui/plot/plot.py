import threading
import time
import math
import matplotlib.pyplot as plt
import matplotlib.animation as animation


class GenericPlotter:
    def __init__(self, title="Generic Plot", xlabel="X", ylabel="Y", max_data_points=100):
        self.xdata, self.ydata = [], []
        self.max_data_points = max_data_points

        self.fig, self.ax = plt.subplots()
        self.title = title
        self.xlabel = xlabel
        self.ylabel = ylabel

        self.ax.set_title(self.title)
        self.ax.set_xlabel(self.xlabel)
        self.ax.set_ylabel(self.ylabel)
        self.ax.set_autoscaley_on(True)

        (self.line,) = self.ax.plot([], [], "ro-")

        self.time = 0

    def init_animation(self):
        return (self.line,)

    def update_plot(self, frame_data):
        new_y = frame_data

        self.xdata.append(self.time)
        self.ydata.append(new_y)

        self.time = self.time + 1

        # Limit data points to maintain performance
        if len(self.xdata) > self.max_data_points:
            self.xdata = self.xdata[-self.max_data_points :]
            self.ydata = self.ydata[-self.max_data_points :]

        # Update line data efficiently
        self.line.set_data(self.xdata, self.ydata)

        # Dynamically adjust x and y-axis limits
        xmin, xmax = min(self.xdata), max(self.xdata)
        ymin, ymax = min(self.ydata), max(self.ydata)
        x_range = xmax - xmin
        y_range = ymax - ymin
        self.ax.set_xlim(xmin - 0.1 * x_range, xmax + 0.1 * x_range)
        self.ax.set_ylim(ymin - 0.1 * y_range, ymax + 0.1 * y_range)

        return (self.line,)

    def start_animation(self):
        anim = animation.FuncAnimation(
            self.fig, self.update_plot, frames=self.generate_data, init_func=self.init_animation, save_count=100, interval=100, blit=True
        )  # Update every 100ms
        plt.show()

    def generate_data(self):
        x_val = 0
        while True:
            yield math.sin(x_val)
            x_val += 0.1
            time.sleep(0.01)  # Simulate data generation time


if __name__ == "__main__":
    plotter = GenericPlotter(title="Real-time Plot", xlabel="Time (s)", ylabel="Value")
    plotter.start_animation()
