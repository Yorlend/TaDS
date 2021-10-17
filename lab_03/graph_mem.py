from matplotlib import pyplot as plt

P = [i for i in range(101)]

def mem_dmat(N, p):
    idSize = 4
    dataSize = 8
    ptrSize = 8
    dmatSize = 2 * idSize + ptrSize
    return dmatSize + N * ptrSize + N * N * dataSize

def mem_smat(N, p):
    M = round(N * p)
    idSize = 4
    dataSize = 8
    ptrSize = 8
    smatSize = 3 * idSize + 2 * ptrSize + 0
    return smatSize + M * (dataSize + idSize) + (N + 1) * idSize

N = 10
MD = [mem_dmat(N, p) for p in P]
MS = [mem_smat(N, p) for p in P]

plt.plot(P, MD, label="dense mem")
plt.plot(P, MS, label="sparse mem")
plt.legend()
plt.show()
