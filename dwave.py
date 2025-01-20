#!/usr/bin/env python
# Migrated to Ocean SDK from old SAPI code

import numpy as np
import sys
import traceback
import dimod
from dwave.system import DWaveSampler, FixedEmbeddingComposite, EmbeddingComposite

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

file_path = '/Users/PycharmProjects/Dwave/12/qubo.txt'
matrix = np.loadtxt(file_path)
rows, cols = matrix.shape
n = rows

Q = {}
with open(file_path, 'r') as file:
    lines = file.readlines()
    n = len(lines)
    for i in range(n):
        line = lines[i].strip().split()
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
    dwave_sampler = DWaveSampler(
        token='yourtoken',
        endpoint='https://cloud.dwavesys.com/sapi',
        solver={'name': 'Advantage2_prototype2.6'}
    )
except:
    print('Error creating DWaveSampler')
    traceback.print_exc()
    sys.exit(1)

sampler = EmbeddingComposite(dwave_sampler)

annealT, progT, readT = 160, 100, 100
print('annealT=', annealT, 'progT=', progT, 'readT=', readT)
start_time = time.time()

result = sampler.sample(
    bqm,
    num_reads=1000,
    annealing_time=annealT,
    programming_thermalization=progT,
    readout_thermalization=readT,
)

samples = result.samples()
newresult = [list(sample.values()) for sample in samples]
end_time = time.time()
running_time = end_time - start_time
print(f"程序运行时间: {running_time:.4f} 秒")

print(result.info)

