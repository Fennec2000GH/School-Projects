## Read in data for problem 1
data = read.csv("~/Documents/Teaching/Stat4241/F2021/Homeworks/Homework4/Data/Problem1.csv", header=TRUE)
x = as.matrix(data[,1:52])
y = as.numeric(data[,53])


## Read in data for problem 2
rm(list=ls())

load(file="~/Documents/Teaching/Stat4241/F2021/Homeworks/Homework4/Data/Problem2train.dat")
load(file="~/Documents/Teaching/Stat4241/F2021/Homeworks/Homework4/Data/Problem2test.dat")

x = as.matrix(dataTrain[,1:204])
y = as.numeric(dataTrain[,205])

xtest = as.matrix(dataTest[,1:204])
ytest = as.numeric(dataTest[,205])
