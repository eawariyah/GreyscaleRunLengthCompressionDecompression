import cv2
import numpy as np

# Read the image data from the CSV file
image_data = np.loadtxt('./CSV/rle_decoded.csv', dtype=np.uint8, delimiter=',')

# Reshape the image data into the original shape (assuming grayscale image)
height, width = image_data.shape
image = image_data.reshape((height, width, 1))

# Save the image
cv2.imwrite('./Resources/OriginalImage_reconstructed.jpg', image)

print("Image reconstructed as OriginalImage_reconstructed.jpg")
