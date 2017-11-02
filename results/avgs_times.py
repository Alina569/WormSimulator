total_num_machines = 16225


def get_info(file_name):

    data = [line.rstrip().split(" ") for line in open(file_name, "r")]
    total_time = 0

    times = []

    for i in range(1, len(data)):
        start_time = float(data[i-1][0])
        end_time = float(data[i][0])

        difference = (end_time - start_time)
        times.append(difference)

        total_time += difference

    avg_time = total_time / total_num_machines

    min_time = min(times)
    max_time = max(times)

    return [avg_time, min_time, max_time]

# all the files
files = ["data_lcg.dat", "data_phys.dat", "data_unix_rand.dat", "data_vn.dat"]

for file_name in files:
    print()
    print(file_name)
    print(get_info(file_name))
    print()
