from PIL import Image
import numpy as np

def convert_to_8_channels(image_path):
    # Open the grayscale image
    original_image = Image.open(image_path)

    # Convert the image to a numpy array
    image_array = np.array(original_image)

    # Normalize pixel values from 0 to 255 to 0 to 7
    image_array = np.floor_divide(image_array, 2)

    # Create an image from the numpy array with 8 channels
    eight_channel_image = Image.fromarray(image_array.astype('uint8'))

    return eight_channel_image

def main():
    # Input grayscale image path
    input_image_path = "OriginalImage.jpg"

    # Convert the image to 8 channels
    eight_channel_image = convert_to_8_channels(input_image_path)

    # Save the resulting image
    output_image_path = "EightChannelImage.jpg"
    eight_channel_image.save(output_image_path)

    print("Image converted to 8 channels and saved as 'EightChannelImage.jpg'.")

if __name__ == "__main__":
    main()
