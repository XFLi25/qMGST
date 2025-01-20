#!/usr/bin/env python
# Migrated to Ocean SDK from old SAPI code

import sys
import traceback
import dimod
from dwave.system import LeapHybridSampler
from dwave.cloud import Client
import time




client = Client.from_config(token='yourtoken')


solvers = client.get_solvers()

print("Available solvers:")
for solver in solvers:
    print(f"- {solver.id}")


s, s2 = 1.0, 1.0
print('Embed scale=', s, s2)
assert 0 <= s <= 1


n = 45


file_path = '/Users/PycharmProjects/Dwave/9/qubo.txt'


Q = {}
with open(file_path, 'r') as file:
    lines = file.readlines()
    n = len(lines)
    for i in range(n):
        line = lines[i].strip().split()  #
        for j in range(n):
            t = float(line[j])
            if j > i and t != 0:
                Q[(i, j)] = t


(H, J, ising_offset) = dimod.utilities.qubo_to_ising(Q)

maxH = 0.0
if len(H):
    maxH = max(abs(min(H)), abs(max(H)))
maxJ = 0.0
if len(J.values()) > 0:
    maxJ = max(abs(min(J.values())), abs(max(J.values())))

maxV = max(maxH, maxJ) if maxH or maxJ else 1.0
if maxV == 0:
    maxV = 1.0


bqm = dimod.BinaryQuadraticModel.from_qubo(Q)


bqm.scale(s2 / maxV)


try:
    hybrid_sampler = LeapHybridSampler(
        token='yourtoken'
    )
    print('LeapHybridSampler successfully created.')
except Exception as e:
    print('Error creating LeapHybridSampler:', e)
    traceback.print_exc()
    sys.exit(1)


start_time = time.time()

try:
    result = hybrid_sampler.sample(
        bqm,

        time_limit = 3.0

    )

    samples = result.samples()
    newresult = [list(sample.values()) for sample in samples]

except Exception as e:
    print('Error during sampling:', e)
    traceback.print_exc()
    sys.exit(1)

end_time = time.time()
running_time = end_time - start_time
print(f"程序运行时间: {running_time:.4f} 秒")
print(result.info)