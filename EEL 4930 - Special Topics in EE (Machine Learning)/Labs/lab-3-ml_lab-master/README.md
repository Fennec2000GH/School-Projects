# Lab 3 - Classification of ASL Data Set

This is a project group assignment.

**Due: Monday, March 23, 11:59 PM**

## Grading Rubric

1. **Problem 1 (10 pts):** you have included a screenshot of your Zoom meeting/s.
    
2. **Problem 2 (90 pts):** you have implemented all classifiers listed and reported the results in a summary table. You have also included a discussion of the results.

**Total: 100 pts**

# Comparison of Classifiers on ASL Data Set

The objective of Lab 3 is to compile an initial end-to-end machine learning pipeline that includes pre-processing, classification and evaluation on the ASL project data set. You will compare classifiers implemented and provide discussion as to why some out-perform others given the properties of the data set and the classifiers used.

**You can use ```scikit-learn``` modules.**

**Objectives**

By completing this assignment you will practice and master the following skills:

Implementation and performance comparison:
* Linear Discriminant Analysis (LDA) Classifier
* $k$-Nearest Neighbor classifier
* Decision Tree
* Random Forests
* Support Vector Machines
* Multi-Layer Perceptron
* Comparison Summary of Supervised Models

**Create your Repo**

You can create the repo for this assignment by visiting the following link: https://classroom.github.com/g/z4FUTzu1

# Training Data Set

The training data set was collected from the entire class of EEL 4930. The training set contains 1844 samples of $100\times 100$ RGB images. 
* You can download both the training data set (**"train_data.npy"**) and training labels (**"train_labels.npy"**) from our Canvas page [here](https://ufl.instructure.com/courses/395133/files/folder/Project%20Data).

# Problem 1 Description

As we have moved to a virtual environment communication, I am recommending that each team meet via Zoom.

You can schedule meetings that best work for your team here: https://ufl.zoom.us/

* Attach a screenshot proof that you have created a meeting and attended the meeting via Zoom.

* To facilitate collaborative coding while you are communicating via Zoom, I recommend that you use [Google Colab](https://colab.research.google.com/). 
    * You can edit all your Jupter Notebooks in this platform. The updates are live so your teammates can view and participate in real time.
    
 # Problem 2 Description

In this lab you will carry out an end-to-end machine learning pipeline whichs includes pre-processing, classification and evaluation of the results. You will implement several classifiers on the ASL data set, they include: (1) LDA, (2) $k$-Nearest Neighbors, (3) Decision Tree, (4) Random Forests, (5) Support Vector Machines, and (7) Multi-Layer Perceptron.

* For each classifier, you should experiment with different parameter values and report the results.
    * Include the set of parameters that you have experimented. State any reasoning behind those choices.

* For the best set of parameters of each classifier, provide a summary table that compares performance between all classifiers on the provided data set.
    * You should common learning strategies such as cross-validation, data scaling, etc.

* Include a discussion as to why some out-perform others given the properties of the data set and the classifier parameters used.


## Submit your Solution

Along with your Jupyter Notebook answers, create a PDF of the notebook with your solutions.

As always, `add` and `commit` the final version of your work, and `push` your code to your GitHub repository.

* Submit the **URL** of your GitHub Repository as your assignment submission on Canvas (only one team member needs to do so).
