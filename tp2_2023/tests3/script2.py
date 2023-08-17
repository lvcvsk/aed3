import random 

def generate_testcase(n):
    x = []
    y = []

    for i in range(n):
        x.append(0)
        y. append(2**i)
    return x, y


filename = "completo.txt"

m = []
#for i in range(3000,4000,100):
#    m.append(i)
for power in range(2,13):
    m.append(2**power)

tam_testcase = len(m)

with open(filename, "w") as f:
    f.write(f"{tam_testcase}\n")

    for i in m:

        w = random.randint(0, i)
        u = 1
        v = 1
        r = 1
        x, y = generate_testcase(i)
        f.write(f"{i} {r} {w} {u} {v}\n")
        for start, end in zip(x, y):
            f.write(f"{start} {end}\n")
