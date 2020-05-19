from train import train
import numpy as np 
from scipy import ndimage 
from skimage.color import rgb2gray
from skimage import data, filters 
from sklearn.preprocessing import FunctionTransformer 
from sklearn.pipeline import Pipeline 

def test(X_train, X_test, Y_train, Y_test): 
    img_pipeline=train(X_train, Y_train)
    predicted_y=img_pipeline.predict(X=X_test)
    scores=img_pipeline.score(X=X_test, y=Y_test)
    return predicted_y, scores 