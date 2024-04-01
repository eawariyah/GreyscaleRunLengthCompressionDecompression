import csv
import numpy as np

a = []

with open('./CSV/image.csv', newline='') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        a.append(row)

a = np.array(a)

print(a.shape)
