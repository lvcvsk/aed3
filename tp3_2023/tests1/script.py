import random

def generate_testcase(n):
    # Generate random graph with 'n' vertices and random number of edges
    #num_edges = random.randint(n-1, n*(n-1)//2)
    num_edges = round(n*(n-1)//2)
    #num_edges = random.randint(n-1,2*n)
    edges = set()
    while len(edges) < num_edges:
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u != v:
            edges.add((u, v))

    # Select a random source and target vertex
    source = random.randint(1, n)
    target = random.randint(1, n)
    while target == source:
        target = random.randint(1, n)

    # Generate random costs for the edges
    costs = {}
    for edge in edges:
        u, v = edge
        cost = random.randint(1, 1000)  # Modify the range as per your requirements
        costs[(u, v)] = cost

    return n, num_edges - 1, 1, source, target, costs


filename = "testcase_denso.txt"

x = []
for power in range(2,12):
    x.append(2**power)

tam_testcase = len(x)
with open(filename, "w") as f:
    f.write(f"{tam_testcase}\n")
# Generate and print test cases
    for i in x:  # Adjust the range based on the desired size of test cases
            n, m, k, s, t, costs = generate_testcase(i)
            f.write(f"{n} {m} {k} {s} {t}\n")
            for edge, cost in costs.items():
                u, v = edge
                f.write(f"{u} {v} {cost}\n")
f.close
            
