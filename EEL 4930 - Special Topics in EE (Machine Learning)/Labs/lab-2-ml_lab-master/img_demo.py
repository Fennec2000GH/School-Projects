
import matplotlib.pyplot as plt 
import numpy as np 
import pandas as pd 
from PIL import Image
%matplotlib inline

# Xtrain_extra = pd.read_csv('sign_mnist_train.csv', delimiter=',')
labels=['A','B','C','D','E','F','G','H','I']

#extracting rgba by pixels first, resizing to 100x100, and then using imshow to display image 
x=Image.open(fp='asl_alphabet_test/A_test.jpg')
x=x.resize(size=(100, 100))
xrgb=np.asarray(a=list(x.getdata())).reshape(100, 100, 3)
print(type(xrgb), xrgb.shape)
print(xrgb)
plt.imshow(X=xrgb, cmap='gray')
plt.show()

#axis 0 = image index, axis 1 = row (out of 100), axis 2 - column (out of 100), axis 3 = [r, g, b, a] 
rgb_pixels=[] 

#using PIL library to load, resize to 100x100, and then use imshow to display 
for letter in labels: 
    pic=Image.open(fp='asl_alphabet_test/'+letter+'_test.jpg')
    pic.load()
    pic=pic.resize(size=(100, 100))
    rgb_pixels.append(np.asarray(a=list(pic.getdata())).reshape(100, 100, 3))
    plt.imshow(X=pic)
    plt.show()
