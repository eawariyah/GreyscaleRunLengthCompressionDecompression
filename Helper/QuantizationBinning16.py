import cv2
import numpy as np

# Read the original grayscale image
image = cv2.imread('./Resources/OriginalImage.jpg', cv2.IMREAD_GRAYSCALE)

# Define the quantization levels
quantization_levels = np.arange(0, 256, 16)  # Grouping values every 16 units

# Apply quantization
quantized_image = np.digitize(image, quantization_levels) * 16 - 8  # Adjusting to mid-point of each bin

# Save the quantized image
cv2.imwrite('./Resources/QuantizedImage16.jpg', quantized_image)

print("Quantized image saved as QuantizedImage.jpg")
