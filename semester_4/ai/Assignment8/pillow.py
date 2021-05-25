from PIL import Image
from matplotlib import image as img
from matplotlib import pyplot

image = Image.open('f1.jpg')
print(image.format)
print(image.mode)
print(image.size)

image.thumbnail((100, 100))

image.show()

data = img.imread('f1.jpg')
print(data.dtype)
print(data.shape)
pyplot.imshow(data)
pyplot.show()
