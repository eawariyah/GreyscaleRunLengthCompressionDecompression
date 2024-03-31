import numpy as np
import csv

a = []

with open('rle_encoded.csv', newline='') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        a.append(row)

print(a)

def decode_rle(rle_encoded, image_shape):
    decoded_image = np.zeros(image_shape)
    row_index = 0
    col_index = 0
    for value, count in rle_encoded:
        decoded_image[row_index, col_index:col_index+count] = value
        col_index += count
        if col_index >= image_shape[1]:
            row_index += 1
            col_index = 0
    return decoded_image.astype(int)

image = np.array([
                    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                    [0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0],
                    [0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
                    [0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0],
                    [0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0],
                    [0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0],
                    [0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0],
                    [0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0],
                    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                ])


decoded_image = decode_rle(rle_encoded, image.shape)
print("\nDecoded Image:")
print(decoded_image)

np.savetxt('rle_decoded.csv', decoded_image, fmt='%d', delimiter=',')

