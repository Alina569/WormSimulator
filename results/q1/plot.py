import matplotlib.pyplot as plt


def get_data(file_name):

    data = [line.rstrip().split(" ") for line in open(file_name, "r")]

    times = []
    infected_machines = []

    for time, infected_machine in data:

        times.append(time)
        infected_machines.append(infected_machine)

    return times, infected_machines

# all the files
files = ["data_lcg.dat", "data_phys.dat", "data_unix_rand.dat", "data_vn.dat"]

# data
times1, infected1 = get_data(files[0])
times2, infected2 = get_data(files[1])
times3, infected3 = get_data(files[2])
times4, infected4 = get_data(files[3])

# plot the results
plt.plot(times1, infected1, 'r--', label="LCG")
plt.plot(times2, infected2, 'g:', label="Physical")
plt.plot(times3, infected3, 'b-.', label="Unix")
plt.plot(times4, infected4, 'y-', label="Von Neumann")

plt.ylabel("Infected Machines")
plt.xlabel("Time")
plt.legend()
plt.show()
