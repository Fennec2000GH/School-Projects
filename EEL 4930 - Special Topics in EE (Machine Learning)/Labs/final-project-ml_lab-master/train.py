import numpy as np 
from scipy import ndimage 
from skimage.color import rgb2gray
from skimage import data, filters 
from sklearn.preprocessing import FunctionTransformer 
from sklearn.pipeline import Pipeline 

def grayscale_img(X): 
    """Convert RGB image to grayscale image"""
    if(X.shape[1:] != (100, 100, 3)): 
        raise ValueError('Grayscale: shape must be (k, 100, 100, 3)!')
    output=np.asarray(a=[rgb2gray(X[k,:,:,:]) for k in range(len(X))]).reshape(X.shape[0], 100, 100, 1)
    print('Grayscale: X.shape:\t{}\n'.format(output.shape))
    return output
    
    
def vectorize_img(X): 
    """Flatten image into a 1D vector"""
    if(X.shape[1:] != (100, 100, 1)): 
        raise ValueError('Vectorize: shape must be (k, 100, 100, 1)!')
    output=np.asarray(a=[X[k].flatten() for k in range(len(X))])
    print('Vectorize: X.shape:\t{}\n'.format(output.shape))
    return output 
    
# testing only
def vectorize_img_inv(X):
    """Inverse of vectorize_img by converting flattened image into 100x100 grayscale image"""
    if(X.ndim != 2): 
        raise ValueError('Vectorize_Inv: each image must be 1D!')
    output=X.reshape(X.shape[0], 100, 100, 1)
    print('Vectorize_Inv: X.shape:\t{}\n'.format(output.shape))
    return output 

def normalize_img(X_vector):
    """Normalize each pixel intensity value in vectorized image"""
    if(X_vector.ndim != 2): 
        raise ValueError('Normalize: each image must be 1D!')
    output=X_vector/255
    print('Normalize: X.shape:\t{}\n'.format(output.shape))
    return output 

# testing only 
def normalize_img_inv(X_vector):
    """Inverse of normalize_img by scaling intensity of each pixel by 255"""
    if(X_vector.ndim != 2): 
        raise ValueError('Normalize_Inv: each image must be 1D!')
    output=X_vector*255 
    print('Normalize_Inv: X.shape:\t{}\n'.format(output.shape))
    return output 

def train(X, Y): 
    # converting each function to FunctionTransformer type to be compatible in Pipeline 
    grayscale_img_func=FunctionTransformer(func=grayscale_img)
    vectorize_img_func=FunctionTransformer(func=vectorize_img, inverse_func=vectorize_img_inv)
    normalize_img_func=FunctionTransformer(func=normalize_img, inverse_func=normalize_img_inv)

    from sklearn.neighbors import KNeighborsClassifier
    estimators = [
        ('Grayscale', grayscale_img_func),
        ('Vectorize', vectorize_img_func),
        ('Normalize', normalize_img_func), 
        ('KNN', KNeighborsClassifier(n_neighbors=1, weights='uniform', metric='minkowski', p=2))
    ] 
    img_pipeline=Pipeline(estimators)
    img_pipeline.fit(X=X, y=Y)
    return img_pipeline