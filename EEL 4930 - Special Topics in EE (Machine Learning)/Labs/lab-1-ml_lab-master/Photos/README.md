# Lab 1 - Experimental Design

This is a project group assignment. **No more than 4 individuals.**

**Due: Monday, February 10, 11:59 PM**

## Grading Rubric

1. **Problem 1 (10 pts)**
    * **Group Repository (10 pts):** Give your group a name and creta a group GitHub Project repository with your respective group name.
    
2. **Problem 2 (45 pts)** 
    * **Data folder (25 pts):** You've pushed your data folder with 20 pictures of each alphabet character.

    * **Numpy data object (10 pts):** You've pushed your Numpy data object.

    * **Numy labels object (10 pts):** You've pushed your Numpy labels object.
    
3. **Problem 3 (45 pts)**

    * **Experimental Design report (45 pts):** this report should be in a pdf format, should contain the names of all team members and should address the topics requested.

**Total: 100 pts**


# Experimental Design

In this lab assignment, you will collect your own data set and will conduct the experimental design for your project.

**Objectives**

By completing this assignment you will practice and master the following skills:

* Data acquisition protocol 

* Experimental design on an end-to-end machine learning system

**Create your Repo**

You can create the repo for this assignment by visiting the following link: https://classroom.github.com/g/Ht-I4vMu

# Problem 1

Create a group GitHub repository. **Only one student should create a repository and name. All the other team members should join the group once it is created.** Do not create more than one repository for each team.

In your group repository, push all the materials requested in problems 2 and 3.

# Problem 2

For this assignment you will be collecting data for your project. Here are some great resources:

* American Sign Language University (ASLU) [website](https://www.lifeprint.com/)

* The ASL Alphabet [YouTube video](https://www.youtube.com/watch?v=tkMg8g8vVUo)

You are to take pictures of you signing the American Sign Language (ASL) alphabet, **twenty times each** letter. Take pictures of your signing hand only, use the same background and maintain the same front-side view. Save the images as **.jpg** files.

* Take pictures of **only** the following letters: 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' and 'i' (20 times each).

After taking the pictures, you are to crop the images (this can either be done on your phone or computer). Try to center and focus on your signing hand as much as possible. 

After you have collected **20 images of each character**, create a data set folder and run the code provided below to: (1) resize your pictures, (2) save your images in a numpy array in a pre-defined format (file named *data.npy*), and (3) create your labels array (file named *labels.npy*).

To receive full credit for this question, you should push your full directory of images, your numpy image object and label vector. These files must be named and formatted correctly for full credit. Please ensure the data is properly pushed to the repository.

**Refer to the attached Jupyter Notebook for the code to help you create these files.**

Make sure you include in your group GitHub repository:

1. A folder with the images
2. The numpy data files "data.npy" and "labels.npy"

# Problem 3

In this problem you will conduct the experimental design of your project and delineate a project proposal.

In a team effort, your project proposal should include a discussion about the following stages of a machine learning system:

1. **Data set:** identification of a data set with a discussion as to whether the data is easily available, the amount of data available, whether ground truth is available or can be generated.

2. **Error Metrics:** discussion of appropriate error metrics, discussion of methods for cross-validation and discussion of a blind test set generation, all appropriate for the proposed problem.

3. Include a paragraph discussion stating a set of experiments to be conducted. Include any other comments, such as anticipated issues and remedies, you may see fit.

Make sure you include in your group GitHub repository:

1. A pdf file that addresses all of these topics of your experimental design.
    * The pdf file should contain the name of all team members
