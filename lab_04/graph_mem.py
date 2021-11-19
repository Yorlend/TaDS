import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

N_max = 25

def calc_eff(max_size, size):
    arr_mem = 32 + max_size * 8
    lst_mem = 24 + size * 16
    p = (arr_mem - lst_mem) / (arr_mem + lst_mem)
    return 50 * p + 50

data = [[calc_eff(i, j) for j in range(1, N_max + 1)] for i in range(1, N_max + 1)]
mask = np.ones_like(data)
mask[np.triu_indices_from(mask)] = False

ax = sns.heatmap(data, mask=mask, cmap="viridis")
ax.set_xticklabels([str(i) for i in range(1, N_max + 1)])
ax.set_yticklabels([str(i) for i in range(1, N_max + 1)])

plt.title("Сравнение эффективности по памяти двух реализаций стека")
plt.xlabel("Максимальный размер стека")
plt.ylabel("Актуальный размер стека")

plt.gca().invert_yaxis()
plt.show()
