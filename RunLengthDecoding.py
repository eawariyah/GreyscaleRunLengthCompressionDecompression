import numpy as np
import csv

rle_encoded = []

with open('./CSV/rle_encoded.csv', newline='') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        rle_encoded.append([int(val) for val in row])  # Convert strings to integers

# print(rle_encoded)

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

# Assuming the shape of the decoded image is the same as the original image
decoded_image = decode_rle(rle_encoded, (1080, 1600))
print("\nDecoded Image:")
# print(decoded_image)

np.savetxt('./CSV/rle_decoded.csv', decoded_image, fmt='%d', delimiter=',')
