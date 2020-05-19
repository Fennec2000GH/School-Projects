# Final Project

# Steps to train this pipeline model. 

1) Have train_data.npy, train_labels.npy, train.py, and test.py in the same directory. 
2) Open up Jupyter Notebook and go to this directory. 
3) Import numpy and every function found in train.py and test.py into a new cell. 
    
    The functions in train.py are: 
    train, grayscale_img, vectorize_img, vectorize_img_inv, normalize_img, normalize_img_inv
    
    The functions in test.py are: 
    test 
    
4) User numpy load function to load train_data.npy and test_data.npy. Let the data be represented by X and Y, respectively. 
5) Import train_test_split from sklearn and use it to split the loaded data into training and testing sets. 

Note: If user supplies previoulsy prepared training data and test data for X and Y, ignore Step 5. Use numpy load to load such data sets from .npy files. 

6) Call train function on X and Y. 
7) Call test function on the 4 partitions made by train_test_split (or user-supplied training and test sets for X and Y). 

# Running the code below illustrates the steps above. 

```
import numpy as np

from train import train, grayscale_img, vectorize_img, vectorize_img_inv, normalize_img, normalize_img_inv

from test import test

X=np.load('train_data.npy')

Y=np.load('train_labels.npy')

train(X=X, Y=Y)

from sklearn.model_selection import train_test_split

X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, shuffle=True)

pred, accuracy = test(X_train=X_train, X_test=X_test, Y_train=Y_train, Y_test=Y_test)

print('Predictions:\t{}\n'.format(pred))

print('Accuracy:\t{}\n'.format(accuracy))

```


