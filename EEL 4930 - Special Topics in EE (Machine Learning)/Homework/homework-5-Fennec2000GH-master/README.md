# Homework 5

This is an individual assignment.

**Due: Wednesday, April 1 @ 11:59 PM**

## Grading Rubric

1. **Problem 1 (30 pts):** you've answered all 3 questions (10 points each).

2. **Problem 2 (30 pts):** you've answered this question and showed your work. 

3. **Problem 3 (40 pts):** you've answered all questions and provided the appropriate discussion comments.

**Total: 100 pts**

# Multi-Layer Perceptrons and Backpropagation

In this assignment, you will test your knowledge about all Multi-Layer Perceptrons (MLPs) and the backpropagation algorithm.

**You are allowed to use ```scikit-learn``` modules.**

**Objectives**

By completing this assignment you will practice and master the following skills:

* Multi-Layer Perceptron
* Backpropagation
* Online vs Batch Learning

**Create your Repo**

You can create the repo for this assignment by visiting the following link: https://classroom.github.com/a/E4a_1GaX

# Problem 1 - Decision Boundaries in MLP Layers

Suppose you want to create this mask with a two-hidden layer MLP with sigmoid units (threshold non-linearity). Assume that black pixels are 0 and white pixels are 1 (2 class problem).

<div><img src="mask.png", width="300"><!div>

Answer the following questions:

1. What is the smallest number of hidden units/neurons you will need in each layer?

2. Explain their role in creating the mask.

3. Can you achieve the same goal with a *single hidden layer network*? Why or why not?

# Problem 2 - Backpropagation

Consider the following network: 1 input layer, 1 hidden layer and 1 output layer, each layer with 2 neurons.

<div><img src="network.png", width="700"><!div>
    
All weights are initialized to the values shown (and there are no biases for simplicity). Consider the data point $x=[1,1]^T$ with desired output vector $d=[1,0]^T$. Complete one iteration of backpropagation by hand assuming a learning rate of $\eta=0.1$. 

What would all the weight values be after one backpropagation iteration? Show your work. 

Use the sigmoid activation function: $\phi(x) = \frac{1}{1 + e^{-x}}$. Note that $\frac{d\phi(x)}{dx}=\phi'(x) = \phi(x)(1-\phi(x))$.

# Problem 3 - Batch vs Online Learning

In this problem, you will be working with the [Optical recognition of handwritten digits dataset](https://archive.ics.uci.edu/ml/datasets/Optical+Recognition+of+Handwritten+Digits).

The Digits data set contains $8\times 8$ images of digits (class labels 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9). This data set has 60,000 images for training and 10,000 images for testing. Each image is a 8-bit grayscale image and so the intensity values per pixel range from 0-255.

In this problem you will be comparing the performance between (1) online and batch learning and (2) using different optimization algorithms (stochastic gradient descent or SGD, SGD with momentum, ADAM, etc.).

The ```MLPClassifier``` parameters you will need to consider for this question are:

* ```hidden_layer_sizes```, ```solver```, ```alpha```, ```batch_size```, ```learning_rate```, ```learning_rate_init```, ```momentum```, ```nesterovs_momentum``` and ```random_state```.

Answer the following questions:

1. **Online vs Batch learning** 

Create a fixed network architecture (for example, single hidden layer with 10 neurons), with a fixed learning rate (e.g. 0.001), consider 0 momentum and no Nesterov's momentum. I recommend you to fix the ```random_state``` to some seed so you can compare the results between runs.

Using this setup, experiment with different batch sizes (batch = 1 is the same as doing online learning). Plot the learning curves for all models (single plot) and evaluate the accuracy results in test set for all cases. Provide a discussion about differences and advantages of online vs batch learning.

(To plot learning curves, there's a method associated with ```sklearn``` functions called ```loss_curve_```. There is also another function called ```learning_curve``` from the ```model_selection``` module.)

2. **Optimization Algorithms**

Create a similar setup as in the previous step where now you will experiment with different learning algorithms, in particular: SGD with momentum, SGD with Nesterov's momentum and ADAM.

Include learning curves for all models (single plot) and comment on the results. Which one worked better? Using what we learned in class, does the result match your expectation?

3. **Comparison of Test Performance**

Compare the test set performance for all learning strategies you have experimented with. Provide an overall discussion that addresses your earlier comments on parts 2 and 3 and relate them to how successful each strategy is generalization for test set.

Provide any additional insightful comments on any particular of the network that would result in a significant impact in the test performance.

## Submit your Solution

Along with your Jupyter Notebook answers, create a PDF of the notebook with your solutions.

As always, `add` and `commit` the final version of your work, and `push` your code to your GitHub repository.

* Submit the **URL** of your GitHub Repository as your assignment submission on Canvas.
