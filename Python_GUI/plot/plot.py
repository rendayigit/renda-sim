import threading
import time
import math
import matplotlib.pyplot as plt
import matplotlib.animation as animation


class GenericPlotter:
    def __init__(self, title="Generic Plot", xlabel="X", ylabel="Y", max_data_points=100):
        self.data = {}  # Dictionary to store data for multiple plots
        self.max_data_points = max_data_points

        self.fig, self.ax = plt.subplots()
        self.title = title
        self.xlabel = xlabel
        self.ylabel = ylabel

        self.ax.set_title(self.title)
        self.ax.set_xlabel(self.xlabel)
        self.ax.set_ylabel(self.ylabel)
        self.ax.set_autoscaley_on(True)

        self.lines = {}  # Dictionary to store line objects for each plot
        self.time = 0

    def add_plot(self, name, style="ro-"):
        """Add a new plot with a given name and line style."""
        self.data[name] = {"x": [], "y": []}
        (line,) = self.ax.plot([], [], style, label=name)
        self.lines[name] = line
        self.ax.legend()  # Update legend to include new plot

    def init_animation(self):
        return list(self.lines.values())

    def update_plot(self, frame_data):
        for name, new_y in frame_data.items():
            self.data[name]["x"].append(self.time)
            self.data[name]["y"].append(new_y)

            # Limit data points to maintain performance
            if len(self.data[name]["x"]) > self.max_data_points:
                self.data[name]["x"] = self.data[name]["x"][-self.max_data_points :]
                self.data[name]["y"] = self.data[name]["y"][-self.max_data_points :]

            # Update line data efficiently
            self.lines[name].set_data(self.data[name]["x"], self.data[name]["y"])

        # Dynamically adjust x and y-axis limits
        all_x = [val for sublist in [d["x"] for d in self.data.values()] for val in sublist]
        all_y = [val for sublist in [d["y"] for d in self.data.values()] for val in sublist]

        if all_x and all_y:
            xmin, xmax = min(all_x), max(all_x)
            ymin, ymax = min(all_y), max(all_y)
            x_range = xmax - xmin
            y_range = ymax - ymin
            self.ax.set_xlim(xmin - 0.1 * x_range, xmax + 0.1 * x_range)
            self.ax.set_ylim(ymin - 0.1 * y_range, ymax + 0.1 * y_range)

        self.time += 1
        return list(self.lines.values())

    def start_animation(self):
        anim = animation.FuncAnimation(
            self.fig,
            self.update_plot,
            frames=self.generate_data,
            init_func=self.init_animation,
            save_count=100,
            interval=100,
            blit=True,
        )  # Update every 100ms
        plt.show()

    def generate_data(self):
        x_val = 0
        while True:
            yield {"sin": math.sin(x_val), "cos": math.cos(x_val)}
            x_val += 0.1
            time.sleep(0.01)  # Simulate data generation time


if __name__ == "__main__":
    plotter = GenericPlotter(title="Real-time Plot", xlabel="Time (s)", ylabel="Value")
    plotter.add_plot("sin", "ro-")
    plotter.add_plot("cos", "bo-")
    plotter.start_animation()
