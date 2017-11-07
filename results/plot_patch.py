import matplotlib.pyplot as plt


def get_data(file_name):

    data = [line.rstrip().split(" ") for line in open(file_name[0], "r")]
    data1 = [line.rstrip().split(" ") for line in open(file_name[1], "r")]

    times = []
    times1 = []
    infected_machines = []
    patched_machines = []
    
    for time, infected_machine in data:

        times.append(time)
        infected_machines.append(infected_machine)
    
    for time, patched_machine in data1:
        
        times1.append(time)
        patched_machines.append(patched_machine)

    return times, infected_machines, times1, patched_machines

# all the files
files = [("q5/data_vn.dat", "q5/patch_vn.dat")]

# data
times1, infected1, times11, patched1 = get_data(files[0])

# plot the results
plt.plot(times1, infected1, 'y--', label="Infected")
plt.plot(times11, patched1, 'g:', label="Patched")


plt.ylabel("Machines")
plt.xlabel("Time")
plt.legend()
plt.show()
