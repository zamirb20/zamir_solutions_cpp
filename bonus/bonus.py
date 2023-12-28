import matplotlib.pyplot as plt
import numpy as np
from scipy.ndimage import convolve

# reading the image
img = plt.imread('img_signed_16bpp.png')
# converting to uint8
img = np.uint8(np.round(img * 255))

laplacian_filter = np.array([[0, 1, 0],
                             [1, -4, 1],
                             [0, 1, 0]])

# convolution between the image and the laplacian filter
filtered_img = convolve(img, laplacian_filter)

plt.imshow(filtered_img, cmap='gray')
plt.show()

# 0xE0F8E1EC