import numpy as np

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

rle_encoded = run_length_encoding(image)
print("Run-Length Encoding:")
print(rle_encoded)
