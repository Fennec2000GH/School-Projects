# Homework 2

This is an individual assignment.

**Due: Friday, January 31, 11:59 PM**

## Grading Rubric

1. **Problem 1 (60 pts)**
    * **Jupyter Notebook (2 pts):** You have created your Jupyter Notebook using the provided instructions.

    * **Pandas (3 pts):** You've successfully imported the data using the ```pandas``` library.

    * **Exploratory Data Analysis (15 pts):** You have include the auto-correlation plot, one plot for each feature vs the count of total bike rentals and a paragraph discussion about the predictive value of each feature (total of 16).

    * **Pre-processing (10 pts):** You have included paragraph discussion addressing which features you have decided to not use and why OR which features are not in "ready-to-use" mode and your proposed transformation and subsequent usage.

    * **Model Selection and Prediction (20):** You have coded up the implementation of linear regression with and without a regularization term for the selected features and desired target values.

    * **Model Performance (10):** You have included all summary statistics and the required plots for both estimations.

2. **Problem 2 (40 pts)**
    * **Pandas (5 pts):** You've successfully imported the data using the ```pandas``` library.
    
    * **Data Visualization (5 pts):** Reproduce the requested plots.
    
    * **Model Selection and Prediction (15 pts):** Implement model and produce the requested prediction values.
    
    * **Regularization (15 pts):** Add regularization term and assess the validity of the prediction.

**Total: 100 pts**

# Regression, Generalization & Regularization

In this assignment, you will implement a linear regression model based on (1) polynomial features, and (2) collected features while using a regularization term. You will perform exploratory data analysis and discuss model fitting by assessing several statistical measures.

You have been provided with 2 data sets:

1. Bike Sharing data set: make sure you download the files **"hour.csv"** and **"Readme.txt"**.

2. Beer Foam data set: make sure you download the files **"beer_foam.csv"**

**Objectives**

By completing this assignment you will practice and master the following skills:

* Understand and discuss a typical supervised learning workflow
* Linear Regression with computed (polynomial) and provided features
* Model selection
* Effects of adding a penalty term to the model parameters
* Identify and implement techniques to avoid overfitting
* Goodness of fit

**Create your Repo**

You can create the repo for this assignment by visiting the following link: https://classroom.github.com/a/h1NazeFo

# Problem 1: Bike Sharing Data Set

A [bicycle-sharing system](https://en.wikipedia.org/wiki/Bicycle-sharing_system) is a service in which users can rent/use bicycles available for shared use on a short term basis for a price or free. Currently, there are over 500 bike-sharing programs around the world. Such systems usually aim to reduce congestion, noise, and air pollution by providing free/affordable access to bicycles for short-distance trips in an urban area as opposed to motorized vehicles. The number of users on any given day can vary greatly for such systems. The ability to predict the number of hourly users can allow the entities (businesses/governments) that oversee these systems to manage them in a more efficient and cost-effective manner. 

Our goal is to use and optimize a linear regression model that effectively *predicts* the number of ride-sharing bikes that will be used in any given 1 hour time-period, using available information about that time/day.

## Data Set Description

Bike-sharing rental process is highly correlated to the environmental and seasonal settings. For instance, weather conditions,
precipitation, day of week, season, hour of the day, etc. can affect the rental behaviors. The data set we are using is from [University of Porto’s Machine Learning Repository](https://archive.ics.uci.edu/ml/datasets/bike+sharing+dataset#). The core data set is related to the two-year historical log corresponding to years 2011 and 2012 from Capital Bikeshare system, Washington D.C., USA which is publicly available in http://capitalbikeshare.com/system-data.

* I have attached the data set files to this assignment for your convenience. Please make sure you download the files: **"hour.csv"** and **"Readme.txt"**.

The data set is a csv file (**"hour.csv"**) with information from 17,379 hours over 731 days with 16 features (information categories) for each hour. The features are:
* **instant** - Record index
* **dteday** - Date
* **season** - Season (1:spring, 2:summer, 3:fall, 4:winter)
* **yr** Year (0: 2011, 1:2012)
* **mnth** - Month (1 to 12)
* **hr** - Hour (0 to 23)
* **holiday** - Holiday : whether that day is holiday or not
* **weekday** - Weekday : day of the week
* **workingday** - Working-day : if day is neither weekend nor holiday , value is 1. Otherwise 0
* **weathersit** - Weather situation :
    * 1: Clear, Few clouds, Partly cloudy, Partly cloudy
    * 2: Mist + Cloudy, Mist + Broken clouds, Mist + Few clouds, Mist
    * 3: Light Snow, Light Rain + Thunderstorm + Scattered clouds, Light Rain + Scattered clouds
    * 4: Heavy Rain + Ice Pallets + Thunderstorm + Mist, Snow + Fog
* **temp** - Normalized temperature in Celsius. Values are divided to 41 (max)
* **atemp** - Normalized feeling temperature in Celsius. Values are divided to 50 (max)
* **hum** - Normalized humidity. The values are divided to 100 (max)
* **windspeed** - Normalized wind speed. The values are divided to 67 (max)
* **casual** - Count of casual users
* **registered** - Count of registered users
* **cnt** - Count of total rental bikes including both casual and registered

Note that some features have continuous values whereas others have discrete values.

Our goal is to use and optimize Machine Learning models that effectively *predict* the number of ride-sharing bikes (variable **cnt**) that will be used in any given 1 hour time-period, using the available feature information.

## Problem 1 Questions

To receive full marks in this assignment, please address the following directions and questions:

1. **Jupyter Notebook.** Create a Jupyter Notebook with a Python 3+ kernel.
    * Name it "Homework03_[FirstName LastName]"
    * Add a markdown cell with a 1st-level Heading titled "Homework 03"
    * As necessary, create new markdown cells to include comments and reasoning comments.

2. **Pandas.** Use the library ```pandas``` to import the file "hour.csv". You may use the function ```read_csv``` from the ```pandas``` library.
    * Suppose you loaded your dataframe to a variable called *data*. If you want to access one column of that matrix (say feature *hum* - normlized humidity), then you can write ```data['hum']```. This will also be a dataframe. If you want to do operations and plotting this variable, you will have to transform it to an array first: ```np.array(data['hum'])```.
    * If you want to access more than one column in the dataframe *data*, you can do: ```data[['temp','hum','cnt']]```.

3. **Exploratory Data Analysis.** Compute and plot the auto-correlation matrix of the provided features and provide a discussion of your observations. Perform further exploratory data analysis in order to understand the predictive power that each feature has to predict the target variable **cnt**. You should comment on the predictive value of each feature.
    * From the library ```seaborn``` you can utilize the function ```heatmap``` (info [here](https://seaborn.pydata.org/generated/seaborn.heatmap.html)) to plot the auto-correlation matrix.
    * The library ```seaborn``` has great plotting tools, you may find these usefuls: ```pairplot``` and ```jointplot```.

4. **Pre-processing.** Are there any features that can be discarded? Which features would you throw out and why? Could you transform that feature into something useful? 

5. **Model Selection and Prediction.** Find the linear regression coefficients **with and without** a regularization term. Consider the L2-norm penalty on the parameter coefficients.
    * Code up a functions for linear regression model. I suggest to make this function as general as possible (add a input parameter that allows to compute regression with provided features vs computed polynomial features).
    * Provide any justification comments in a markdown cell for your choice of parameter values.

6. **Model Performance.** Include a scatter plot of the predicted count of total rental bikes using linear regression **without** regularization and the true count of total rental bikes. Include *another* scatter plot using linear regression **with** regularization. For both estimators compute:
    * Mean prediction error
    * Median prediction error
    * Q-Q plot
    * r-squared value (using function ```r2_score```)
    * Which model performs best and why?
    
 # Problem 2: Beer Foam data set

Were you ever sitting at a bar with your friends drinking a sparkling cold brew and started questioning *what's the rate that I should drink the beer so that at every sip there's still a nice line of foam?* Never? Perhaps a nice hot cappuccino coffee? Well, you get the idea...

The [beer foam data set](http://www.stat.ufl.edu/~winner/datasets.html) was collected by A. Leike and published in his work titled "Demonstration of the Exponential Decay Law Using Beer Froth" published in 2002 in the European Journal of Physics.

Our goal is to use and optimize a linear regression that effectively *predicts* the wet foam height from different brands of beer after time of pour, using available information about that beer's previous foam height level at different times.


## Data Set Description

The data contains measurements of wet foam height and beer height at various time points for 3 brands of beer. The author of this data set fit an *exponential decay model*.

The data set is a txt file (**"beer_foam.csv"**) with information about the foam height (in cm) from 3 brands of beer over 15 measurement times (in seconds) after the time of pour.

The file is organized in 4 columns:
1. Time from pour (in seconds)
2. Erdinger Weissbier foam height (in cm)
3. Augustinerbrau Munchen foam height (in cm)
4. Budweiser foam height (in cm)

## Problem 2 Questions

To receive full marks in this assignment, please address the following directions and questions:

1. **Pandas.** Use the library ```pandas``` to import the file "beer_foam.csv".

2. **Data Visualization.** Visualize an overlay plot with all data pairs (time of pour and foam height) from the 3 beers using the function ```scatter``` from ```matplotlib.pyplot```.
    * Make sure each pair (t,x) is plotted with a different color. Include labels for x-axis, y-axis and title. Include plot legend.

3. **Model Selection and Prediction.** Predict beer foam height at time t = 450 seconds for all beer brands using a linear regression model with polynomial features of order M = 3.
    * What did you observe? Explain your reasoning.
    
4. **Regularization.** For each beer brand model, add the L2-norm regularization term with a regularization parameter lambda = 0.4. How did this affect the height prediction at time $t=450$ seconds? Explain your reasoning.


## Submit your Solution

Along with your Jupyter Notebook answers, create a PDF of the notebook with your solutions.

As always, `add` and `commit` the final version of your work, and `push` your code to your GitHub repository.

* Submit the **URL** of your GitHub Repository as your assignment submission on Canvas.