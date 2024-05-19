import matplotlib.pyplot as plt
import csv
import os
# Read data from CSV file
initial_points = []
sorted_points = []

with open("tsp_results.csv", "r") as csvfile:
    reader = csv.reader(csvfile, delimiter=",")
    for row in reader:
        if not row:
            continue

        if len(row) == 1:  # Check for blank line
            continue
        
        x = float(row[0])
        y = float(row[1])
        
        sorted_points.append([x, y])

# Extract x and y coordinates for each set of points
sorted_x = [point[0] for point in sorted_points]
sorted_y = [point[1] for point in sorted_points]

# Plot initial points and sorted path with connections
plt.scatter(sorted_x, sorted_y, label="Sorted Path", color='red', marker='o')
for i in range(len(sorted_points) - 1):
    plt.plot([sorted_x[i], sorted_x[i + 1]], [sorted_y[i], sorted_y[i + 1]], color="gray", linestyle="-")

#plot initial point and final point
plt.plot([sorted_x[0], sorted_x[-1]], [sorted_y[0], sorted_y[-1]], color="gray", linestyle="-")
# Add labels and title
plt.xlabel("X-Coordinate")
plt.ylabel("Y-Coordinate")
plt.title("Visualization of Shortest Distance (TSP)")
plt.legend()
# Show the plot
plt.grid(True)
# Save the plot as a png file
plt.savefig("Graficas/Grafica10p.png")
os.remove("tsp_results.csv")

