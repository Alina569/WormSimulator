
total_num_machines = 65536
def get_info(file_name):

    data = [line.rstrip().split(" ") for line in open(file_name, "r")]

    attempts = []
    total_attempts = 0

    for station_index, infect_time, attempt_num in data:
        attempts.append(int(attempt_num))
        total_attempts += int(attempt_num)

    avg_attempts = total_attempts // total_num_machines

    min_attempt = min(attempts)
    max_attempt = max(attempts)

    return [avg_attempts, min_attempt, max_attempt]

# all the files
files = ["infect_lcg.dat", "infect_phys.dat", "infect_unix_rand.dat", "infect_vn.dat"]

for file_name in files:
    print()
    print(file_name)
    print(get_info(file_name))
    print()
