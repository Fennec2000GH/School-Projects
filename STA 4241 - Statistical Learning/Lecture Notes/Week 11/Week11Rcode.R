library(splines)
library(FNN)
library(fields)

set.seed(1)
n = 50

## Generate data from a nonlinear function
x <- runif(n, 0, 10)
ftrue <- function(x){
  5*sin(x) + x + .2*x^2 - .05*x^3
}
y = ftrue(x) + rnorm(n, sd=1.5)

## Order the data for the linear interpolator
ord = order(x)

## Plot linear interpolator
plot(x[ord], y[ord], type='l', lwd=3, main="Function with RSS = 0",
     xlab="X", ylab="Y")
points(x,y, pch=16, cex=1.5)

## fit a flexible model that goes through all of the data points
lmOverfit = lm(y ~ ns(x, 49))
predOverfit = predict(lmOverfit, newdata = data.frame(x=seq(0, 10, length=1000)))

## Plot the predicted fit
plot(seq(0, 10, length=1000), predOverfit, type='l', 
     ylim=range(y) + c(-4,4), lwd=3, ylab="",
     xlab="X")
points(x, y, pch=16, cex=1.5)

## Find a different model with RSS = 0
lmOverfit = lm(y ~ bs(x, 49))
predOverfit = predict(lmOverfit, newdata = data.frame(x=seq(0, 10, length=1000)))

plot(seq(0, 10, length=1000), predOverfit, type='l', 
     ylim=range(y) + c(-4,4), lwd=3, ylab="", xlab="X")
points(x, y, pch=16, cex=1.5)


## now fit smoothing spline for multiple values of df
fitSmooth40 = smooth.spline(x, y, df=40)
fitSmooth20 = smooth.spline(x, y, df=20)
fitSmooth3 = smooth.spline(x, y, df=3)
fitSmoothCV = smooth.spline(x, y, cv=TRUE)

gridData = data.frame(x=seq(0, 10, length=1000))

predGrid40 = predict(fitSmooth40, gridData)$y$x
predGrid20 = predict(fitSmooth20, gridData)$y$x
predGrid3 = predict(fitSmooth3, gridData)$y$x
predGridCV = predict(fitSmoothCV, gridData)$y$x

## Plot the smoothing spline fits
plot(gridData$x, predGrid40, type='l', lwd=3,
     xlab="X", ylab="Y")
lines(gridData$x, predGrid20, col=2, lwd=3)
lines(gridData$x, predGrid3, col=3, lwd=3)
lines(gridData$x, predGridCV, col=4, lwd=3)
points(x, y, pch=16)
legend("bottomleft", c("Df = 40", "Df = 20", "Df = 3", "Cross validation"),
       lwd=3, col=1:4, lty=1)


## Illustrate weight and kernel functions
x0 = 1
s = seq(-2, 4, length=1000)

## Radial and KNN kernel functions
radial = function(x, x0=1, d = 0.3) {
  return(exp((-(x - x0)^2) / d))
}

knnKern = function(x, x0=1, d = 0.3, k=10) {
  return(1*(abs(x - x0) < d)/k)
}

## Plot kernels on a grid around x0=1
plot(s, radial(s, x0=1, d=0.5), type='l', lwd=4,
     main="Radial kernel, d=0.5", xlab="", ylab="")
plot(s, knnKern(s, x0=1, d=0.5, k=10), type='l', lwd=4,
     main="KNN kernel", xlab="", ylab="")


## Generate data from a nonlinear function
set.seed(1)
n = 150

x <- runif(n, 0, 10)
ftrue <- function(x){
  5*sin(x) + x + .2*x^2 - .05*x^3
}
y = ftrue(x) + rnorm(n, sd=1.5)
plot(x, y)

## Create sequence of points to predict at
gridData = seq(0, 10, length=1000)

## keep track of function estimates at each grid point and
## each value of d
estimates = matrix(NA, length(gridData), 4)

for (i in 1 : length(gridData)) {
  weight1 = radial(x, x0=gridData[i], d=0.05)
  weight2 = radial(x, x0=gridData[i], d=1)
  weight3 = radial(x, x0=gridData[i], d=3)
  weight4 = radial(x, x0=gridData[i], d=100)
  
  estimates[i,1] = sum(weight1*y) / sum(weight1)
  estimates[i,2] = sum(weight2*y) / sum(weight2)
  estimates[i,3] = sum(weight3*y) / sum(weight3)
  estimates[i,4] = sum(weight4*y) / sum(weight4)
}

## Plot the resulting estimates
plot(gridData, estimates[,1], type='l', lwd=3, ylab="Estimates",
     main="Kernel regression", xlab="X")
points(x,y, pch=16, cex=0.7)
lines(gridData, estimates[,2], col=2, lwd=3)
lines(gridData, estimates[,3], col=3, lwd=3)
lines(gridData, estimates[,4], col=4, lwd=3)
legend("bottomleft", paste("d =", c(0.05, 1, 3, 100)), lwd=3, col=1:4, lty=1)


## KNN regression with k=20
kn = knn.reg(train=data.frame(x=x), test=data.frame(x=gridData), y=y, k=20)

## Local regression with a chosen span
local = loess(y ~ x, span=0.6)
predLocal = predict(local, gridData)

plot(gridData, estimates[,2], type='l', lwd=3, ylab="Estimates",
     main="Local approaches", xlab="")
lines(gridData, kn$pred, col=2, lwd=3)
lines(gridData, predLocal, col=3, lwd=3)
points(x,y, pch=16, cex=0.7)
legend("bottomleft", c("Kernel regression", "KNN", "Local linear"), lwd=3, col=1:3, lty=1)

## Plot spline functions
splineMod = ns(x, 5)
splineGrid = predict(splineMod, gridData)

plot(gridData, splineGrid[,1], type='l', lwd=3,
     main="Natural cubic splines with 5 knots", ylim=range(splineGrid),
     xlab="X")
lines(gridData, splineGrid[,2], lwd=3, col=2)
lines(gridData, splineGrid[,3], lwd=3, col=3)
lines(gridData, splineGrid[,4], lwd=3, col=4)
lines(gridData, splineGrid[,5], lwd=3, col=5)

## Plot 2d step functions
twoDgrid = matrix(0, 100, 100)
twoDgrid[76:100,76:100] = 1
image.plot(twoDgrid)

twoDgrid = matrix(0, 100, 100)
twoDgrid[26:50,26:50] = 1
image.plot(twoDgrid)

## Create tensor products of splines
x1 = runif(100)
x2 = runif(100)

splineMod1 = ns(x1, 5)
splineMod2 = ns(x2, 5)

gridd = seq(0, 1, length=100)

splineGrid1 = predict(splineMod1, gridd)
splineGrid2 = predict(splineMod2, gridd)

twoDgrid = matrix(NA, 100, 100)
for (i in 1 : 100) {
  for (j in 1 : 100) {
    twoDgrid[i,j] = splineGrid1[i,3]*splineGrid2[j,2]
  }
}

image.plot(twoDgrid)

twoDgrid = matrix(NA, 100, 100)
for (i in 1 : 100) {
  for (j in 1 : 100) {
    twoDgrid[i,j] = splineGrid1[i,2]*splineGrid2[j,5]
  }
}

image.plot(twoDgrid)


