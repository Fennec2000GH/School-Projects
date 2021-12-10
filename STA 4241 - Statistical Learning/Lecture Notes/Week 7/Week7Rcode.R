library(glmnet)
library(spls)
library(leaps)

## Load the mice data
data(mice)

## Only using covariates 11-20 for modeling this time
data = data.frame(y = mice$y[,1], x=mice$x[,11:20])

## Find the best set of models using best subset selection
## Note that nvmax controls the maximum number of covariates allowed
fit = regsubsets(y ~ ., data=data, nvmax=10)
fitSummary = summary(fit)

## Same thing, but with forward stepwise regression
fitFWD = regsubsets(y ~ ., data=data, nvmax=10, method="forward")
fitSummaryFWD = summary(fitFWD)

## Same thing, but with backward stepwise regression
fitBWD = regsubsets(y ~ ., data=data, nvmax=10, method="backward")
fitSummaryBWD = summary(fitBWD)

## Make a plot showing each of the three types of algorithms
## and the three evaluation criteria
par(mfrow=c(3,3), pty='s')

## Adjusted R2
plot(fitSummary$adjr2, type='l', lwd=3, main="Best subset",
     ylab="Adjusted R2", xlab="# covariates included", cex.main=1.6,
     cex.lab=1.4)
abline(v = which.max(fitSummary$adjr2))
plot(fitSummaryFWD$adjr2, type='l', lwd=3, main="Forward",
     ylab="Adjusted R2", xlab="# covariates included", cex.main=1.6,
     cex.lab=1.4)
abline(v = which.max(fitSummaryFWD$adjr2))
plot(fitSummaryBWD$adjr2, type='l', lwd=3, main="Backward",
     ylab="Adjusted R2", xlab="# covariates included", cex.main=1.6,
     cex.lab=1.4)
abline(v = which.max(fitSummaryBWD$adjr2))

## BIC
plot(fitSummary$bic, type='l', lwd=3, main="Best subset",
     ylab="BIC", xlab="# covariates included", cex.main=1.6,
     cex.lab=1.4)
abline(v = which.min(fitSummary$bic))
plot(fitSummaryFWD$bic, type='l', lwd=3, main="Forward",
     ylab="BIC", xlab="# covariates included", cex.main=1.6,
     cex.lab=1.4)
abline(v = which.min(fitSummaryFWD$bic))
plot(fitSummaryBWD$bic, type='l', lwd=3, main="Backward",
     ylab="BIC", xlab="# covariates included", cex.main=1.6,
     cex.lab=1.4)
abline(v = which.min(fitSummaryBWD$bic))

## AIC (cp and AIC are the same in this case)
plot(fitSummary$cp, type='l', lwd=3, main="Best subset",
     ylab="AIC", xlab="# covariates included", cex.main=1.6,
     cex.lab=1.4)
abline(v = which.min(fitSummary$cp))
plot(fitSummaryFWD$cp, type='l', lwd=3, main="Forward",
     ylab="AIC", xlab="# covariates included", cex.main=1.6,
     cex.lab=1.4)
abline(v = which.min(fitSummaryFWD$cp))
plot(fitSummaryBWD$cp, type='l', lwd=3, main="Backward",
     ylab="AIC", xlab="# covariates included", cex.main=1.6,
     cex.lab=1.4)
abline(v = which.min(fitSummaryBWD$cp))
dev.off()

## Fit ridge regression to the mice data
fit = glmnet(x = mice$x[,11:20], y = mice$y[,1], alpha = 0)

## Plot coefficients as a function of lambda
plot(fit, xvar="lambda", xlab="Log Lambda", main="Test")

## Use cross validation to estimate labmda
## Note if you run this multiple times, you'll
## Get different curves due to randomness in the CV estimates
fitCV = cv.glmnet(x = mice$x[,11:20], y = mice$y[,1], alpha = 0)

## Plot the CV curve
plot(fitCV)

