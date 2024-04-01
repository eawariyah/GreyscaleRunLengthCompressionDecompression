import numpy as np
import csv
a = []

# with open('OriginalImage.csv', newline='') as csvfile:
# with open('QuantizedImage16.csv', newline='') as csvfile:
with open('QuantizedImage32.csv', newline='') as csvfile:


    reader = csv.reader(csvfile)
    for row in reader:
        a.append(row)

a = np.array(a)

# print(a.shape)

def run_length_encoding(image):
    rle = []
    for row in image:
        current_value = row[0]
        count = 1
        for pixel in row[1:]:
            if pixel == current_value:
                count += 1
            else:
                rle.append((current_value, count))
                current_value = pixel
                count = 1
        rle.append((current_value, count))
    return rle
# image = np.array([
#                     [0, 0, 0, 0, 0, 0, 0, 0, 0,],
#                     [0, 0, 1, 1, 1, 1, 1, 0, 0,],
#                     [0, 0, 1, 0, 0, 0, 0, 0, 0,],
#                     [0, 0, 1, 1, 1, 1, 0, 0, 0,],
#                     [0, 0, 0, 0, 0, 0, 1, 0, 0,],
#                     [0, 0, 0, 0, 0, 0, 1, 0, 0,],
#                     [0, 0, 1, 0, 0, 0, 1, 0, 0,],
#                     [0, 0, 0, 1, 1, 1, 0, 0, 0,],
#                     [0, 0, 0, 0, 0, 0, 0, 0, 0,],
#                 ])
image = a

rle_encoded = run_length_encoding(image)
print(image.shape)

print("Run-Length Encoding:")
# print(rle_encoded)

np.savetxt('rle_encoded.csv', rle_encoded, fmt='%s', delimiter=',')