import cv2
import numpy as np

image = cv2.imread('./Resources/OriginalImage.jpg', cv2.IMREAD_GRAYSCALE)
# image = cv2.imread('./Resources/QuantizedImage16.jpg', cv2.IMREAD_GRAYSCALE)
# image = cv2.imread('./Resources/QuantizedImage32.jpg', cv2.IMREAD_GRAYSCALE)


# min_intensity = np.min(image)
# max_intensity = np.max(image)
print(image)

np.savetxt('./CSV/OriginalImage.csv', image, fmt='%d', delimiter=',')
# np.savetxt('./CSV/QuantizedImage16.csv', image, fmt='%d', delimiter=',')
# np.savetxt('./CSV/QuantizedImage32.csv', image, fmt='%d', delimiter=',')

print("Image exported as image.csv")
