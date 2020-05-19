# Homework 3

This is an individual assignment.

**Due: Thursday, February 20, 11:59 PM**

## Grading Rubric

1. **Problem 1 (40 pts)** 
    * Problem 1.1 (2 points)
    * Problem 1.2 (2 points)
    * Problem 1.3 (3 points)
    * Problem 1.4 (3 points)
    * Problem 1.5 (7 points)
    * Problem 1.6 (6 points)
    * Problem 1.7 (3 points)
    * Problem 1.8 (7 points)
    * Problem 1.9 (6 points)
    * Problem 1.10 (1 point)

2. **Problem 2 (40 pts)** 
    * Problem 2.1 (2 points)
    * Problem 2.2 (3 points)
    * Problem 2.3 (3 points)
    * Problem 2.4 (10 points)
    * Problem 2.5 (5 points)
    * Problem 2.6 (12 points)
    * Problem 2.7 (5 points)

3. **Problem 3 (30 pts)** 
    * Problem 3.1 (5 points)
    * Problem 3.2 (5 points)
    * Problem 3.3 (5 points)
    * Problem 3.4 (5 points)

**Total: 100 pts**

# Feature Selection/Extraction, Classification & Evalution Metrics

In this assignment, you will experiment with different techniques for feature selection/extraction, perform classification using k-Nearest Neighbors algorithm and evaluate results using different evaluation metrics.

**You are allowed to use ```scikit-learn``` modules.**

You will be working with 3 data sets:

1. [MNIST Data Set](http://yann.lecun.com/exdb/mnist/) (download the files **"mnist_train.csv"** and **"mnist_test.csv"**)

2. [Iris Data Set](https://archive.ics.uci.edu/ml/datasets/iris)

3. [Breast Cancer Data Set](https://archive.ics.uci.edu/ml/datasets/Breast+Cancer)

**Objectives**

By completing this assignment you will practice and master the following skills:

* Feature extraction, in particular, PCA and LDA
* Feature selection, in particular, SBS
* k-Nearest Neighbors algorithm
* Evaluation Metrics

**Create your Repo**

You can create the repo for this assignment by visiting the following link: https://classroom.github.com/a/AHgcazMd

# Problem 1: MNIST Data Set

In this problem, you will be working with the [MNIST Data Set](http://yann.lecun.com/exdb/mnist/) to extract features, perform classification using the K-Nearest Neighbors algorithm and evaluate your results using metrics such as accuracy, ROC curve and confusion matrices.

The MNIST data set contains $28\times 28$ images of handwritten digits (class labels 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9). This data set has 60,000 images for training and 10,000 images for testing. Each image is a 8-bit grayscale image and so the intensity values per pixel range from 0-255.

* Make sure you download the files **"mnist_train.csv"** and **"mnist_test.csv"**.

## Problem 1 Questions

To receive full marks in this assignment, address the following questions and implementation steps:

1. How many samples are there per class in training and test sets? 
    * Create and print a list that counts the number of class samples in training and test sets.
    * Without changing the training and test sets, comment on the class distribution among training and test sets. 
    * In this question you should address the generalization ability based on the number of examples per class.


2. Normalize each image to have intensity values to range between 0 and 1.


3. Create a PCA structure using ```scikit-learn``` functions and plot the explained variance ratio.
    * How many principal components would you have to extract in order to preserve 90% of the explained variance in the data?


4. Using ```imshow```, plot the first 9 principal components.
    * What is each principal component representing?
    
    
5. Project the input space into a 6-dimensional feature space using **PCA**. Train a k-NN classifier on the projected feature space. 
    * To successfully train your model, you should: (1) choose an evaluation metric, (2) for a set of k values, train the k-NN and evaluate the results in the test set using your chosen metric, (3) pick the k value that maximizes/minimizes your metric (an example of metric is *accuracy*).
   
   
6. For your choice of k, do: (1) compute the accuracy in both training and test sets, (2) print the confusion matrix, (3) plot the ROC curve for each class including the AUC (area under the curve) in the plot title, (4) plot the ROC for the overall classifier including the AUC (area under the curve) in the plot title, and (5) comment the final results.
    * Comments on the final classification results should include things like: dimensionality of feature space, limitations of PCA, interpretation of the confusion matrix, AUC of each class and overall usability of the model.

7. Create an LDA structure using ```scikit-learn``` functions and plot the explained variance ratio.
    * How many LDA directions would you have to extract in order to explain 90% of the data?
    
8. Project the input space into a 6-dimensional feature space using **LDA**. Train a k-NN classifier on the projected feature space. 
    * To successfully train your model, you should: (1) choose an evaluation metric, (2) for a set of k values, train the k-NN and evaluate the results in  the test set using your chosen metric, (3) pick the k value that maximizes/minimizes your metric (an example of metric is *accuracy*).

9. For your choice of k, do: (1) compute the accuracy in both training and test sets, (2) print the confusion matrix, (3) plot the ROC curve for each class including the AUC (area under the curve) in the plot title, (4) plot the ROC for the overall classifier including the AUC (area under the curve) in the plot title, and (5) comment the final results.
    * Comments on the final classification results should include things like: dimensionality of feature space, limitations of LDA, interpretation of the confusion matrix, AUC of each class and overall usability of the model.
    
10. Briefly discuss and compare the performance of both PCA and LDA on the MNIST data set (given the set of experiments you've conducted - questions 1-9).

# Problem 2: Iris Data Set

In this problem, you will be working with the [Iris Data Set](https://archive.ics.uci.edu/ml/datasets/iris).

The IRIS data set contains 4 feature descriptors (sepal length in cm, sepal width in cm, petal length in cm, petal width in cm) to characterize 3 species of Iris plants (class labels 0 - [Iris setosa](https://en.wikipedia.org/wiki/Iris_setosa), 1 - [Iris Versicolor](https://en.wikipedia.org/wiki/Iris_versicolor), and 2- [Iris Virginica](https://en.wikipedia.org/wiki/Iris_virginica)). The IRIS data set contains 150 samples each with 4 attributes/features.

## Problem 2 Questions

To receive full marks in this assignment, address the following questions and implementation steps:

1. Split the data randomly into training and test sets in an 80/20 split.
    * You may use the ```train_test_split``` function from ```scikit-learn```.

2. Plot the explained variance ratio of PCA projections in the training set.
     * How many principal components would you have to extract in order to preserve 90% of the explained variance in the data?

3. Plot the explained variance ratio of LDA projections in the training set.
     * How many LDA rojections would you have to extract in order to explain 90% of the data?

4. Project the both training and test sets into a 1-dimensional space using both PCA and LDA. Plot each 1-D projection for both PCA and LDA in a separate plot. Each class should have a different color and marker symbol. Plot should contain axis labels and legend.
    * You may want to plot the y-axis at a constant value, for example 0 (use the function ```np.zeros```).
    
5. Comment on the observations between the 1-D projections for both PCA and LDA.
    * To aid your discussion, compute the mean and variance of each class in the 1-D space.
    
6. Train a k-Nearest Neighbor classifier with $K=5$ neighbors using features created with PCA and LDA. Compute the accuracy in training and test, print the confusion matrices and compute the precision and recall (you may use the function ```precision_recall_fscore_support``` from ```scikit-learn```).
    * Which model performed the best? And why?
    * Make sure to comment on all computed measures.
    
7. What happens as you increase the number of neighbors k? decrease the number of neighbors k?

# Problem 3 - Breast Cancer Data Set

In this problem, you will be working with the [Breast Cancer Data Set](https://archive.ics.uci.edu/ml/datasets/Breast+Cancer).

The Breast Cancer data set contains 30 feature descriptors (mean, standard error, and "worst" or largest of radius, texture, perimeter, area, smoothness, compactness, concavity, concave points, symmetry, fractal dimension) to characterize cell types as benign (class 1) or malignant (class 0). The Breast Cancer data set contains 569 samples each with 30 attributes/features.

## Problem 3 Questions

To receive full marks in this assignment, address the following questions and implementation steps:

1. Suppose you are performing classification using the k-NN algorithm. Would you be able to perform feature selection using L1-norm penalty? Why?

2. Run Sequential Backward Selection (SBS) on the provided data set. (You may use the code for SBS presented in lecture 7.)
    * How many (and which) features will you keep?
    
3. Run the k-NN classifier on the selected features. Report the results in the test set using accuracy measure and confusion matrix.
    * Split the data into training and test using a 80/20 split respectively.

4. Compare the results when using all 30 features versus the selected features. What do you observe?

## Submit your Solution

Along with your Jupyter Notebook answers, create a PDF of the notebook with your solutions.

As always, `add` and `commit` the final version of your work, and `push` your code to your GitHub repository.

* Submit the **URL** of your GitHub Repository as your assignment submission on Canvas.
