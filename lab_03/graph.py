from pandas import read_csv
from matplotlib import pyplot as plt

data = read_csv("data.csv")

plt.plot(data["dims"], data["time_std"])
plt.plot(data["dims"], data["time_sparse"])
plt.show()
