import cv2
import numpy as np

# image = cv2.imread('OriginalImage.jpg', cv2.IMREAD_GRAYSCALE)
image = cv2.imread('./Resources/OriginalImage.jpg', cv2.IMREAD_GRAYSCALE)


# min_intensity = np.min(image)
# max_intensity = np.max(image)
print(image)

np.savetxt('OriginalImage.csv', image, fmt='%d', delimiter=',')

print("Image exported as image.csv")
