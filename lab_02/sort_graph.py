from sys import argv
import pandas as pd
from matplotlib import pyplot as plt

if len(argv) < 2:
    print("Bad argv")
else:
    data = pd.read_csv(argv[1])
    N = data[["N"]].values
    for col in data.columns:
        if col != "N":
            plt.plot(N, data[col].values, label=col)
    plt.legend()
    plt.show()
