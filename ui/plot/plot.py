import threading
import time
import matplotlib.pyplot as plt
import math


class GenericPlotter:
    def __init__(self, title="Generic Plot", xlabel="X", ylabel="Y"):
        self.fig, self.ax = plt.subplots()
        self.xdata, self.ydata = [], []

        self.title = title
        self.xlabel = xlabel
        self.ylabel = ylabel

        self.ax.set_title(self.title)
        self.ax.set_xlabel(self.xlabel)
        self.ax.set_ylabel(self.ylabel)
        self.ax.set_autoscaley_on(True)

        self.time = 0

    def update_plot(self, new_y):
        self.xdata.append(self.time)
        self.ydata.append(new_y)
        self.ax.clear()
        self.ax.plot(self.xdata, self.ydata, "ro-")
        self.fig.canvas.draw()
        self.fig.canvas.flush_events()
        self.time = self.time + 1  # TODO: increment with last sim time delta

    def start_test_thread(self):
        def test_thread_func():
            x_val = 0
            while True:
                self.update_plot(math.sin(x_val))
                x_val += 0.1
                time.sleep(0.1)

        test_thread = threading.Thread(target=test_thread_func)
        test_thread.start()

    def show(self):
        plt.show()


if __name__ == "__main__":
    plotter = GenericPlotter(title="Real-time Plot", xlabel="Time (s)", ylabel="Value")
    plotter.start_test_thread()
    plotter.show()
