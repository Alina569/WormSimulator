total_num_machines = 65536
total_infected = 16225
def get_info(file_name):

    data = [line.rstrip().split(" ") for line in open(file_name, "r")]

    infection_times = []
    attempts = []

    total_time = 0
    total_attempts = 0

    for station_index, infect_time, attempt_num in data:
        infection_times.append(float(infect_time))
        attempts.append(int(attempt_num))

        total_time += float(infect_time)
        total_attempts += int(attempt_num)

    avg_time = total_time / total_infected
    avg_attempts = total_attempts // total_num_machines

    min_attempt = min(attempts)
    max_attempt = max(attempts)

    max_time = max(infection_times)

    return [avg_time, max_time, avg_attempts, min_attempt, max_attempt]

# all the files
files = ["infect.dat"] # , "infect_phys.dat", "infect_unix_rand.dat", "infect_vn.dat"]

for file_name in files:
    print()
    print(file_name)
    print(get_info(file_name))
    print()
