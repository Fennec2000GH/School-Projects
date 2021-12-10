## How to read in data for homework problems

## Question 2 
## Note you first must download the data file off of the course website
## and then save it on your computer
setwd(dir='D:/Users/qcaij/OneDrive - University of Florida/Files/College/Coursework/Fall 2021/STA4241 - Statistical Learning/Homework/HW 1/')
load(file.path(getwd(), 'Data/Problem2.dat'))

x1 = data$x1
x2 = data$x2
xrandom = data$xrandom
y = data$y

rm(list=ls())

## Question 3
## First install and download ISLR library
install.packages('ISLR')
library(ISLR)

## Now load data set
data(Smarket)

## look at data
head(Smarket)
