library(glmnet)
library(genlasso)
library(mvtnorm)

## This code will re-create many of the plots found in week 10 lecture notes

set.seed(1)
n = 250

## Generate data from a nonlinear function
x <- runif(n, 0, 10)
ftrue <- function(x){
  5*sin(x) + x + .2*x^2 - .05*x^3
}
y = ftrue(x) + rnorm(n, sd=1.5)

## Create a data frame
dat = data.frame(x=x, y=y)

## Create a grid of data points to predict at
gridData = data.frame(x = seq(-0.5, 10.5, length=1000))

## fit linear curve and polynomial curve through it
linMod = lm(y ~ x, data=dat)
polyMod5 = lm(y ~ poly(x, 5), data=dat)
polyMod25 = lm(y ~ poly(x, 25), data=dat)

## Predict for each model at the grid of points
predictLinear = predict(linMod, newdata=gridData, se.fit=TRUE)
predictPoly5 = predict(polyMod5, newdata=gridData, se.fit=TRUE)
predictPoly25 = predict(polyMod25, newdata=gridData, se.fit=TRUE)

## Plot the fits from the linear and 5 df models
plot(x, y, xlim=range(gridData), main="5 degree polynomial")
lines(gridData$x, predictLinear$fit, lwd=2)
lines(gridData$x, predictLinear$fit + 1.96*predictLinear$se.fit, lwd=2, lty=2)
lines(gridData$x, predictLinear$fit - 1.96*predictLinear$se.fit, lwd=2, lty=2)
legend("bottom", c("Linear", "Polynomial"), col=1:2, lwd=2, lty=1)

lines(gridData$x, predictPoly5$fit, lwd=2, col=2)
lines(gridData$x, predictPoly5$fit + 1.96*predictPoly5$se.fit, lwd=2, lty=2, col=2)
lines(gridData$x, predictPoly5$fit - 1.96*predictPoly5$se.fit, lwd=2, lty=2, col=2)

## Plot the fits from the linear and 25 df models
plot(x, y, xlim=range(gridData), main="25 degree polynomial")
lines(gridData$x, predictLinear$fit, lwd=2)
lines(gridData$x, predictLinear$fit + 1.96*predictLinear$se.fit, lwd=2, lty=2)
lines(gridData$x, predictLinear$fit - 1.96*predictLinear$se.fit, lwd=2, lty=2)
legend("bottom", c("Linear", "Polynomial"), col=1:2, lwd=2, lty=1)

lines(gridData$x, predictPoly25$fit, lwd=2, col=2)
lines(gridData$x, predictPoly25$fit + 1.96*predictPoly25$se.fit, lwd=2, lty=2, col=2)
lines(gridData$x, predictPoly25$fit - 1.96*predictPoly25$se.fit, lwd=2, lty=2, col=2)

## couple with ridge regression and lasso regression

## First create matrices we can use for glmnet
polyMat = matrix(NA, n, 25)
gridMat = matrix(NA, length(gridData$x), 25)

## Standardize the predictors as well
for (jj in 1 : 25) {
  polyMat[,jj] = x^jj
  gridMat[,jj] = gridData$x^jj
  
  gridMat[,jj] = (gridMat[,jj] - mean(polyMat[,jj])) / sd(polyMat[,jj])
  polyMat[,jj] = (polyMat[,jj] - mean(polyMat[,jj])) / sd(polyMat[,jj])
}

## Now fit ridge. Note that we have added an input called penalty.factor
## Which ensures that the linear term is not penalized
cvRidge = cv.glmnet(x = polyMat, y = y, alpha = 0, 
                    penalty.factor=c(0, rep(1, dim(polyMat)[2]-1)))
fitRidge = glmnet(x = polyMat, y = y, alpha = 0, lambda=cvRidge$lambda.min,
                  penalty.factor=c(0, rep(1, dim(polyMat)[2]-1)))

## Predict at the grid
predictRidge = predict.glmnet(fitRidge, newx=gridMat)

## Do the same but for lasso
cvLasso = cv.glmnet(x = polyMat, y = y, alpha = 1,
                    penalty.factor=c(0, rep(1, dim(polyMat)[2]-1)))
fitLasso = glmnet(x = polyMat, y = y, alpha = 1, lambda=cvLasso$lambda.min,
                  penalty.factor=c(0, rep(1, dim(polyMat)[2]-1)))

predictLasso = predict.glmnet(fitLasso, newx=gridMat)

## Plot unpenalized, ridge, and lasso fits
plot(x, y, xlim=range(gridData), main="25 degree polynomial with ridge/lasso")
lines(gridData$x, predictPoly25$fit, lwd=2, col=1)
lines(gridData$x, predictRidge, col=2)
lines(gridData$x, predictLasso, col=3)
legend("bottom", c("No penalty","Ridge", "Lasso"), col=1:3, lwd=2, lty=1)


## Create a grid of data points to predict at
gridData = data.frame(x = seq(0.0001, 9.9999, length=1000))

## Fit the piecewise constant models
modCut5 = lm(y ~ cut(x, breaks = seq(0, 10, length=6)))
modCut30 = lm(y ~ cut(x, breaks = seq(0, 10, length=31)))

plot(x, y, main="Piecewise constant f(X)")
lines(gridData$x, predict(modCut5, gridData), lwd=7, col=2)
lines(gridData$x, predict(modCut30, gridData), lwd=7, col=3)
legend("bottomleft", c("K=5", "K=30"), col=2:3, lty=1, lwd=7)

## Again create matrices to be used for penalized approaches
mat = model.matrix(~ -1 + cut(x, breaks = seq(0, 10, length=31)))
matGrid = model.matrix(~ -1 + cut(gridData$x, breaks = seq(0, 10, length=31)))

## Fit lasso on these piecewise constant functions
cvLasso = cv.glmnet(x = mat, y = y, alpha = 1)
fitLasso = glmnet(x = mat, y = y, alpha = 1, lambda=cvLasso$lambda.min)

## CV curve of lasso
plot(cvLasso)

## Lasso predictions on the grid
predictLasso = predict.glmnet(fitLasso, newx=matGrid)

plot(x, y, main="Lasso penalty")
lines(gridData$x, predictLasso, lwd=7, col=2)
lines(gridData$x, predict(modCut30, gridData), lwd=7, col=3)
legend("bottomleft", c("Lasso", "No lasso"), col=2:3, lty=1, lwd=7)

## Now try the fused lasso
## D represents a matrix of contrasts we want to penalize
D = matrix(0, dim(mat)[2], dim(mat)[2])
for (ii in 1 : (dim(mat)[2] - 1)) {
  D[ii,ii] = -1
  D[ii,ii+1] = 1
}
test = fusedlasso(y=y, X=mat, D=D)

## Get coefficients from two different lambda values
## And obtain their predictions
beta = test$beta[,10]
pred10 = matGrid %*% beta

beta = test$beta[,20]
pred20 = matGrid %*% beta

plot(x, y)
lines(gridData$x, predictLasso, col=2)
lines(gridData$x, pred10, lwd=2, col=3)
lines(gridData$x, pred20, lwd=2, col=4)
legend("bottomleft", c("Lasso", "Fused lasso, lambda=28", "Fused lasso, lambda=12"), col=2:4, lty=1, lwd=7)


## piecewise linear function
rm(list=ls())
set.seed(3)

## Generate data and grid of locations to predict at
n = 50
x = runif(n, 0, 3)
gridData = data.frame(x = seq(0.0001, 2.9999, length=1000))

## Create a piecewise linear function
y = rep(NA, n)
y[x < 1.5] = 1 + 2*x[x<1.5] + rnorm(sum(x<1.5))
y[x >= 1.5] = -14 + 12*x[x>=1.5] + rnorm(sum(x>=1.5))

data = data.frame(x=x, y=y)

## data with X < 1.5
dataLow = data.frame(x = x[x < 1.5],
                     y = y[x < 1.5])

## Data with X > 1.5
dataHigh = data.frame(x = x[x >= 1.5],
                      y = y[x >= 1.5])

modLow = lm(y ~ x, data=dataLow)
modHigh = lm(y ~ x, data=dataHigh)

## Predict on the grid using the corresponding model
gridPred = rep(NA, length(gridData$x))
gridPred[gridData$x < 1.5] = predict(modLow, newdata=gridData)[gridData$x < 1.5]
gridPred[gridData$x >= 1.5] = predict(modHigh, newdata=gridData)[gridData$x >= 1.5]

plot(x, y, xlim=c(0,3), ylim=range(gridPred))
lines(gridData$x, gridPred, lwd=7)

## Now fit the model constrained to line up
data$maxX = (data$x - 1.5)*(data$x > 1.5)
gridData$maxX = (gridData$x - 1.5)*(gridData$x > 1.5)

## Fit model with the correct predictors
linModPieceCons = lm(y ~ x + maxX, data=data)

plot(x, y, xlim=c(0,3), ylim=range(gridPred))
lines(gridData$x, gridPred, lwd=2, col=2)
lines(gridData$x, predict(linModPieceCons, gridData), lwd=2, col=3)
legend("topleft", c("Unconstrained", "Constrained"), col=2:4, lty=1, lwd=7)


rm(list=ls())

## Generate from a nonlinear curve again
n = 250

X <- runif(n, 0, 10)
ftrue <- function(x){
  5*sin(x) + x + .2*x^2 - .05*x^3
}
y = ftrue(X) + rnorm(n, sd=1.5)

## Knot locations
kappa <- seq(0.3, 9.7, length=30)

## Create design matrix using piecewise linear basis functions
B <- cbind(1, X, Reduce(cbind, lapply(kappa, function(x){pmax(X - x, 0)})))

# lambda = 0, i.e linear regression solution
B0 <- solve(crossprod(B), crossprod(B, y))

## ridge penalty matrix that does not penalize the linear component or intercept
D <- diag(c(0,0, rep(1, dim(B)[2] - 2)))

# Ridge solution for various lambda values
B1 <- solve(crossprod(B) + 1*D, crossprod(B, y))
B2 <- solve(crossprod(B) + 5*D, crossprod(B, y))
B3 <- solve(crossprod(B) + 3000*D, crossprod(B, y))

## New locations to predict at
Xnew <- seq(0, 10, length=1e3)

## Evaluate basis functions at new data points
Bnew <- cbind(1, Xnew, Reduce(cbind, lapply(kappa, function(x){pmax(Xnew - x, 0)})))

## Plot results for different lambda values
par(mar=c(3,3,3,2))
plot(X, y,  pch=20, main=expression(paste("Ridge: Varying ", lambda)), col= grey(0.2, alpha=0.8), bty="l", xlab="", ylab="")
points(Xnew, Bnew%*%B0, col=2, type="l", lwd=2)
points(Xnew, Bnew%*%B1, col=3, type="l", lwd=2)
points(Xnew, Bnew%*%B2, col=4, type="l", lwd=2)
points(Xnew, Bnew%*%B3, col=5, type="l", lwd=2)
legend("bottom", c(expression(paste(lambda, "= 0")),
                   expression(paste(lambda, "= 1")),
                   expression(paste(lambda, "= 5")),
                   expression(paste(lambda, "= 3000"))), col=2:5, lwd=7, lty=1)


## Do the same thing, but for lasso
lasso.fit <- glmnet(x = B[,-1], y = y, lambda = c(0.01, 0.1, 0.5, 5), 
                    standardize = FALSE, penalty.factor = c(0, rep(1, dim(B)[2]-2)))

plot(X, y,  pch=20, main=expression(paste("Lasso: Varying ", lambda)), col= grey(0.2, alpha=0.8), bty="l", xlab="", ylab="")
points(Xnew, Bnew%*%coefficients(lasso.fit, s = lasso.fit$lambda[4]), col=2, type="l", lwd=2)
points(Xnew, Bnew%*%coefficients(lasso.fit, s = lasso.fit$lambda[3]), col=3, type="l", lwd=2)
points(Xnew, Bnew%*%coefficients(lasso.fit, s = lasso.fit$lambda[2]), col=4, type="l", lwd=2)
points(Xnew, Bnew%*%coefficients(lasso.fit, s = lasso.fit$lambda[1]), col=5, type="l", lwd=2)
legend("bottom", c(expression(paste(lambda, "= 0.01")),
                   expression(paste(lambda, "= 0.1")),
                   expression(paste(lambda, "= 0.5")),
                   expression(paste(lambda, "= 5"))), col=2:5, lwd=4, lty=1)

## Fit this with cubic splines

## Choose knot locations
kappa <- c(2, 4, 6, 8)

## Create design matrix with truncated basis expansion
B <- cbind(1, X, X^2, X^3, 
           Reduce(cbind, lapply(kappa, function(x){pmax((X - x)^3, 0)})))
Bnew <- cbind(1, Xnew, Xnew^2, Xnew^3, 
              Reduce(cbind, lapply(kappa, function(x){pmax((Xnew - x)^3, 0)})))

## Get coefficients from least squares
coefs = lm(y ~ -1 + B)$coefficients

## Plot the fit
plot(X, y,  pch=20, main="Cubic spline fit", 
     col= grey(0.2, alpha=0.8), bty="l", xlab="", ylab="")
points(Xnew, Bnew%*%coefs, col="red", type="l", lwd=2)


