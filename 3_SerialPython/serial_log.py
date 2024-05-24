import serial, time
import matplotlib.pyplot as plt
import matplotlib.animation as animation

f = open("datos.csv", "w") # usar a
arduino = serial.Serial('COM8', 9600)

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys_x = []
ys_y = []
ys_z = []

count = 0
while count < 100:
    rawString = arduino.readline().decode("utf-8")
    print(rawString)
    f.write(rawString)
    count += 1

arduino.close()
f.close()

# def animate(i, xs, ys_x, ys_y, ys_z, arduino):
#     rawString = arduino.readline().decode("utf-8")
#     rawString = str(rawString).split(";")
#     # Add x and y to lists
#     xs.append(i)
#     ys_x.append(float(rawString[0]))
#     ys_y.append(float(rawString[1]))
#     ys_z.append(float(rawString[2]))

#     # Limit x and y lists to 20 items
#     xs = xs[-20:]
#     ys_x = ys_x[-20:]
#     ys_y = ys_y[-20:]
#     ys_z = ys_z[-20:]

#     # Draw x and y lists
#     ax.clear()
#     ax.plot(xs, ys_x)
#     ax.plot(xs, ys_y)
#     ax.plot(xs, ys_z)

#     # Format plot
#     plt.xticks(rotation=45, ha='right')
#     plt.subplots_adjust(bottom=0.30)
#     plt.title('Titulo')
#     plt.ylabel('Label')
#     plt.ylim(-2, 2)

#     if i >= 300:
#         arduino.close()
#         f.close()

# ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys_x, ys_y, ys_z, arduino), interval=10)
# plt.show()

# arduino.close()
# f.close()