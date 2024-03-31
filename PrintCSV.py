import csv

a = []

with open('image.csv', newline='') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        a.append(row)

print(a)