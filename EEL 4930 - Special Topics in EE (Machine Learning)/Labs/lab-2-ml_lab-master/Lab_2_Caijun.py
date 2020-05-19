
#creating .npy files for extra training data (Xtrain_extra) and its respective targets (ytrain_extra) 
import matplotlib.pyplot as plt 
import numpy as np 
from PIL import Image 

%matplotlib inline 

#labels or classes over the data 
labels=['A','B','C','D','E','F','G','H','I']

#extra training and target set 
Xtrain_extra=np.empty(shape=(27000, 100, 100, 3))
ytrain_extra=np.repeat(a=labels, repeats=3000).reshape(27000, 1)

#testing for correct shape 
print(Xtrain_extra.shape, ytrain_extra.shape)

#extracting (r, g, b) triples per pixel 
filepath='asl_alphabet_train/'
for letter in labels: 
    for i in range(1, 3001): 
        img=Image.open(fp=filepath+letter+'/'+letter+str(i)+'.jpg', mode='r') 
        img.load()
        img=img.resize(size=(100, 100))
        Xtrain_extra=np.append(arr=Xtrain_extra, values=np.asarray(a=list(img.getdata())).reshape(1,100, 100, 3), axis=0)

#check contents of Xtrain_extra 
print(Xtrain_extra)

#saving as .npy files 
np.save('Xtrain_extra.npy', Xtrain_extra_train_extra)
np.save('ytrain_extra.npy', ytrain_extra)

#replotting using pyplot.imshow 
for j in range(len(labels)): #for each letter in labels 
    idx = list(np.where(ytrain_extra == labels[j])[0]) #get indices in ytrain_extra corresponding to letter 
    random.shuffle(idx) 
    # Only displaying 10 random samples for each letter 
    for k in range(10): 
        plt.imshow(Xtrain_extra[idx[k],:,:,:], cmap='gray'); 
        plt.title(ytrain_extra[idx[k]][0])
        plt.show();
