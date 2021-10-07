from sys import argv, stdout
from itertools import product
from random import choice, randint, random


genders = {0: "M", 1: "F"}

surnames_m = "Ivanov Petrov Sidorov Maksimov Vitus Gofrik Cherno".split()
surnames_f = "Ivanova Petrova Sidorova Maksimova Serova Shelia".split()
surnames = {"M": surnames_m, "F": surnames_f}

names_m = "Ivan Petya Sidor Maksim Vitya Vlad".split()
names_f = "Masha Sonya Tanya Eva Nadya".split()
names = {"M": names_m, "F": names_f}

groups = [f"IU7-{i}{j}B" for i, j in product(range(1, 9), range(1, 7))]

streets = "Ladozhskaya Parkovaya Olenevskaya Kostritskaya Krasnaya Izmaylovskaya Tverskaya".split()


def gen_entry(file):
    gender = choice(["F", "M"])
    surname = choice(surnames[gender])
    name = choice(names[gender])
    age = randint(18, 25)
    group = choice(groups)
    score = round(2 + random() * 3, 2)
    date = "{:02d}.{:02d}.{:04d}".format(randint(1, 28), randint(1, 12), randint(2018, 2021))
    housing = choice(["dorm", "appartment"])
    if housing == "dorm":
        house = f"{randint(1, 10)},{randint(1,899)}"
    elif housing == "appartment":
        street = choice(streets)
        house = f"{street},{randint(1,89)},{randint(1,999)}"


    print(surname, name, group, gender, age, score,
        date, housing, house,
        sep=";", end=";\n", file=file)


def gen_data(file, N: int):
    for i in range(N):
        gen_entry(file)


if __name__ == "__main__":
    if len(argv) == 1:
        print("usage: python3 datagen.py N > datafile.txt")
        exit(0)
    
    N = int(argv[1])
    gen_data(stdout, N)
