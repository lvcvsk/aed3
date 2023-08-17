import random
import numpy as np
import os

np.random.seed(420)

x = []

directory = input("Enter the directory to save the test case: ")
if not os.path.exists(directory):
    os.makedirs(directory)

for power in range(14,22):
    x.append(2**power)

for n in x :
    def generate_test_case(n):
        activities = []
        for i in range(n):
            start = random.randint(1, 2*n)
            end = random.randint(start, 2*n)
            activities.append((start, end))
        sorted_activities = sorted(activities, key=lambda x: x[1])
        start_times = [a[0] for a in sorted_activities]
        end_times = [a[1] for a in sorted_activities]
        return start_times, end_times

    start_times, end_times = generate_test_case(n)

    filename = f"testcase_{n}.txt"
    filepath = os.path.join(directory, filename)
    with open(filepath, "w") as f:
        f.write(f"{n}\n")
        for start, end in zip(start_times, end_times):
            f.write(f"{start} {end}\n")

    print(f"Test case written to {filepath}")