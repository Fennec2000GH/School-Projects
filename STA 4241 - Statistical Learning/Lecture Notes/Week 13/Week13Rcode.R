## Load libraries
library(tree)
library(randomForest)
library(gbm)
library(mvtnorm)

## Simulate simple additive model
set.seed(2)

## sample size
n = 100

## Generate covariates for training and testing samples
x = rmvnorm(n, sigma=diag(10))
xnew = rmvnorm(500, sigma=diag(10))

## Generate outcomes for both samples
y = 1*(x[,1] > 0) + 1*(x[,2] > 0) + 1*(x[,3] > 0) + rnorm(n)
ynew = 1*(xnew[,1] > 0) + 1*(xnew[,2] > 0) + 1*(xnew[,3] > 0) + rnorm(500)

## Store data frames
data = data.frame(y=y, x=x)
dataNew = data.frame(y=ynew, x=xnew)

## Fit a full tree
fit = tree(y ~ ., data=data)
summary(fit)

## Plot the fit
plot(fit)
text(fit, digits=2)

## Now do CV to find tree depth
cv.fit = cv.tree(fit)
plot(cv.fit$size, cv.fit$dev, type='b')

## Pruning tree to have the size chosen by CV
prune.fit = prune.tree(fit, best=7)

## Plot the final, pruned tree
plot(prune.fit)
text(prune.fit, digits=2)

## Out of sample prediction
predictFit = predict(fit, newdata=dataNew)

## MSE
mean((ynew - predictFit)^2)

## Let's try random forests with m=5
fitRF = randomForest(y ~ ., data=data, mtry=5)
predictRF = predict(fitRF, newdata=dataNew)

## MSE for random forests
mean((ynew - predictRF)^2)

## Variable importance plot
varImpPlot(fitRF, main="Variable importance measure", pch=15)

## Plot the bagging and RF results as a function of the number of trees
results = matrix(NA, 500, 4)

## Try values of b from 1-500
for (bb in 1 : 500) {
  if (bb %% 10 == 0) print(bb)
  
  ## m=3
  fitRF1 = randomForest(y ~ ., data=data, mtry=3, ntree = bb)
  predictRF1 = predict(fitRF1, newdata=dataNew)
  results[bb,1] = mean((ynew - predictRF1)^2)
  
  ## m=5
  fitRF2 = randomForest(y ~ ., data=data, mtry=5, ntree = bb)
  predictRF2 = predict(fitRF2, newdata=dataNew)
  results[bb,2] = mean((ynew - predictRF2)^2)
  
  ## m=7
  fitRF3 = randomForest(y ~ ., data=data, mtry=7, ntree = bb)
  predictRF3 = predict(fitRF3, newdata=dataNew)
  results[bb,3] = mean((ynew - predictRF3)^2)
  
  ## m=10, i.e. bagging
  fitRF4 = randomForest(y ~ ., data=data, mtry=10, ntree = bb)
  predictRF4 = predict(fitRF4, newdata=dataNew)
  results[bb,4] = mean((ynew - predictRF4)^2)
}

## Plot the MSE as a function of B
plot(1:500, results[,1], type='l', lwd=1, ylim=c(1.25,3),
     xlab="# of trees", ylab="MSE", main="Performance of RF")
lines(1:500, results[,2], col=2, lwd=1)
lines(1:500, results[,3], col=3, lwd=1)
lines(1:500, results[,4], col=4, lwd=1)
abline(h = mean((ynew - predictFit)^2), lty=2, lwd=1)
legend("topright", paste("m =", c(3,5,7,10)), lwd=1, lty=1, col=1:4)
text(250,1.95, "Single tree error")

## Boosting
fitGBM = gbm(y ~ ., data=data, distribution="gaussian",
             n.trees=5000, interaction.depth=1, shrinkage=0.001)
predictGBM = predict(fitGBM, newdata=dataNew, n.trees=5000)

## MSE for boosting
mean((ynew - predictGBM)^2)

## Compare approaches for different tuning parameters

## RF m=3
fitRF3 = randomForest(y ~ ., data=data, mtry=3)
predictRF3 = predict(fitRF3, newdata=dataNew)

## Bagging
fitRF10 = randomForest(y ~ ., data=data, mtry=10)
predictRF10 = predict(fitRF10, newdata=dataNew)

## GBM with one set of tuning parameters
fitGBM = gbm(y ~ ., data=data, distribution="gaussian",
             n.trees=5000, interaction.depth=1, shrinkage=0.001)
predictGBM = predict(fitGBM, newdata=dataNew, n.trees=5000)

## GBM with a different set
fitGBM2 = gbm(y ~ ., data=data, distribution="gaussian",
              n.trees=2000, interaction.depth=2, shrinkage=0.005)
predictGBM2 = predict(fitGBM2, newdata=dataNew, n.trees=2000)

mean((ynew - predictFit)^2)
mean((ynew - predictRF3)^2)
mean((ynew - predictRF10)^2)
mean((ynew - predictGBM)^2)
mean((ynew - predictGBM2)^2)



## Generate data from a nonlinear function to evaluate boosting on
rm(list=ls())
set.seed(1)
n = 150
x <- runif(n, 0, 10)
ftrue <- function(x){
  5*sin(x) + x + .2*x^2 - .05*x^3
}
y = ftrue(x) + rnorm(n, sd=1.5)

## Plot the data
plot(x, y)

## Create relevant data frames
data = data.frame(y=y, x=x)
gridData = data.frame(x=seq(0, 10, length=1000))

## Try a different set of B values
nTreeVec = c(3,30,300,3000,30000)
gridSave = matrix(NA, 1000, 5)

## Try predicting function after each number of trees
for (nt in 1 : length(nTreeVec)) {
  nTrees = nTreeVec[nt]
  fitGBM = gbm(y ~ ., data=data, distribution="gaussian",
               n.trees=nTrees, interaction.depth=2, shrinkage=0.001)
  gridSave[,nt] = predict(fitGBM, newdata=gridData, n.trees=nTrees)
}

## Plot these estimates
plot(x, y, main="Boosting estimates")
lines(gridData$x, gridSave[,1], lwd=2)
lines(gridData$x, gridSave[,2], lwd=2, col=2)
lines(gridData$x, gridSave[,3], lwd=2, col=3)
lines(gridData$x, gridSave[,4], lwd=2, col=4)
lines(gridData$x, gridSave[,5], lwd=2, col=5)
legend("bottomleft", paste(nTreeVec, "Trees"), col=1:5, lwd=2)

## Can also try using random forests to estimate this curve
fitRF = randomForest(y ~ ., data=data)
predictRF = predict(fitRF, newdata=gridData)

## Compare to boosting
plot(x, y, main="Boosting and RF estimates")
lines(gridData$x, gridSave[,5], lwd=2)
lines(gridData$x, predictRF, col=2, lwd=2)
legend("bottomleft", c("Boosting", "Random forest"), 
       lwd=2, lty=1, col=1:2)
