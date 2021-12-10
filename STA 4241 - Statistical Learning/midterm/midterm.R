
# Question 3 
# Part i

# loading packages
packages <- c('foreach', 'ggplot2', 'glmnet', 'Metrics', 'MASS', 'pls')
install.packages(packages)
lapply(packages, library, character.only = TRUE)

n <- 100
p <- 200
mu <- rep(x = 0, times = p)
eye <- as.matrix(x = diag(x = p), nrow = p, byrow = TRUE)

generate.X <- function() {
  # correlation 
  correlation.matrix <- matrix(data = cor(x = MASS::mvrnorm(n = n, mu = mu, Sigma = eye)), nrow = 200, byrow = TRUE)
  
  # covariance matrix
  Sigma <- matrix(data = rep(x = 0, times = 200^2), nrow = 200, byrow = TRUE)
  Sigma.func <- function(i, j) correlation.matrix[i, j] ^ abs(x = i - j)
  
  for (i in 1:200) {
    for (j in 1:200) {
      Sigma[i, j] <- Sigma.func(i, j)
    }
  }
  
  # generated data
  MASS::mvrnorm(n = 100, mu = mu, Sigma = Sigma)
}

X <- generate.X()
df <- as.data.frame(x = X)
colnames(x = df) <- foreach::foreach(i = 1:p, .combine = 'c') %do% {
  sprintf('B%i', i)
}

# indexes of nonzero coefficients
beta.nonzero <- c(1, 2, 41, 42, 81, 82, 121, 122, 161, 162)

# initializing parameters based on contribution to variances in data
pca.components <- summary(prcomp(x = X[, beta.nonzero], center = TRUE, scale. = TRUE))
pca.prop.var <- unlist(pca.components$importance)[2, ]

# coefficient vector
beta <- rep(x = 0, times = p)
for (i in seq_along(along.with = beta.nonzero)) {
  # beta[beta.nonzero[i]] <- pca.prop.var[i] * 100
  beta[beta.nonzero[i]] <- 0.50
}

# generated y-values
sigma <- 1
generate.Y <- function(X) {
  as.matrix(x = X) %*% as.vector(x = t(x = beta)) + rnorm(n = n, mean = 0, sd = sqrt(x = sigma))
}

Y <- generate.Y(X = X)
df$Y <- Y


# simulation study
nsim <- 100 # number of simulations to run
set.seed(123)

# initializing models for testing
ridge.model <- glmnet::glmnet(x = X, y = Y, alpha = 0)
lasso.model <- glmnet::glmnet(x = X, y = Y, alpha = 1)
lasso.numcol <- dim(x = lasso.model$beta)[2]

# simulation data
ridge.cor.mean <- data.frame(placeholder = rep(x = 0, times = n))
lasso.cor.mean <- data.frame(placeholder = rep(x = 0, times = lasso.numcol))
ridge.mse.mean <- data.frame(placeholder = rep(x = 0, times = n))
lasso.mse.mean <- data.frame(placeholder = rep(x = 0, times = lasso.numcol))

for (i in 1:nsim) {
  # data preparation
  X <- generate.X()
  Y <- generate.Y(X = X)
  
  # creating models
  ridge.model <- glmnet::glmnet(x = X, y = Y, alpha = 0)
  lasso.model <- glmnet::glmnet(x = X, y = Y, alpha = 1)
  
  # correlation
  ridge.cor <- foreach::foreach(j = 1:n, .combine = 'c') %do% {
    cor(x = beta, y = as.numeric(x = ridge.model$beta[, j]))
  }
  ridge.cor.mean <- rowMeans(x = cbind(ridge.cor.mean, ridge.cor))
  
  lasso.cor <- foreach::foreach(j = 1:lasso.numcol, .combine = 'c') %do% {
    tryCatch(
      expr = {
        cor(x = beta, y = as.numeric(x = lasso.model$beta[, j]))
      }, 
      warning = function(w) { 0.0 }
    )
  }
  lasso.cor.mean <- rowMeans(x = cbind(lasso.cor.mean, lasso.cor))
  
  # computing MSE for this trial (ridge)
  ridge.mse <- foreach::foreach(j = 1:n, .combine = 'c') %do% {
    Metrics::mse(actual = beta, predicted = ridge.model$beta[, j])
  }
  ridge.mse.mean <- rowMeans(x = cbind(ridge.mse.mean, ridge.mse))
  
  lasso.mse <- foreach::foreach(j = 1:lasso.numcol, .combine = 'c') %do% {
    Metrics::mse(actual = beta, predicted = lasso.model$beta[, j])
  }
  
  lasso.mse.mean <- rowMeans(x = cbind(lasso.mse.mean, lasso.mse))
  
}

ridge.df <- data.frame(cor = ridge.cor.mean, mse = ridge.mse.mean)
lasso.df <- data.frame(cor = lasso.cor.mean, mse = lasso.mse.mean)

# plotting mse vs. correlation
ggplot() + geom_point(data = ridge.df, aes(x = cor, y = mse, color = 'Ridge')) + geom_point(data = lasso.df, aes(x = cor, y = mse, color = 'Lasso'))

# plot(ridge.cv, label = TRUE)
# p * sigma^2 / (t(x = beta) %*% beta)

# Part iii
nonzero.counter <- data.frame(P1 = rep(x = 0, times = 200), 
                              P2 = rep(x = 0, times = 200), 
                              P3 = rep(x = 0, times = 200), 
                              P4 = rep(x = 0, times = 200))


# plot per selected correlation coefficient
for (i in 1:nsim) {
  # data preparation
  X <- generate.X()
  Y <- generate.Y(X = X)
  
  # creating models
  lasso.model <- glmnet::glmnet(x = X, y = Y, alpha = 1)
  lasso.cor  <- foreach::foreach(j = 1:lasso.numcol, .combine = 'c') %do% {
    tryCatch(
      expr = {
        cor(x = beta, y = as.numeric(x = lasso.model$beta[, j]))
      }, 
      warning = function(w) { 0.0 }
    )
  }
  
  # indexes of select correlations from glmnet that each align with some lambda
  p.index <- foreach::foreach(p = c(0.50, 0.75, 0.90, 0.99),  .combine = 'c') %do% { 
    findInterval(x = p, vec = sort(x = lasso.cor)) 
  }
  p.lambda <- lasso.model$lambda[p.index]
  
  # keeping count of nonzero coefficients that correspond to nonzero coefficients in question
  for (j in 1:4) {
    lasso.remodel <- glmnet::glmnet(x = X, y = Y, alpha = 1, lambda = p.lambda[j])
    outcomes <- as.integer(x = as.vector(x = !(lasso.remodel$beta == 0)))
    nonzero.counter[, j] <- nonzero.counter[, j] + outcomes
  }
  
}

# plots per correlation coefficient
ggplot(data = nonzero.counter) + geom_histogram(aes(x = c(1:200), y = P1 / nsim), stat = 'identity') + 
  xlab(label = 'Covariate Index') + 
  ylab(label = 'Nonzero Coefficient Probability at p = 0.50')

ggplot(data = nonzero.counter) + geom_histogram(aes(x = c(1:200), y = P2 / nsim), stat = 'identity') + 
  xlab(label = 'Covariate Index') + 
  ylab(label = 'Nonzero Coefficient Probability at p = 0.75')

ggplot(data = nonzero.counter) + geom_histogram(aes(x = c(1:200), y = P3 / nsim), stat = 'identity') + 
  xlab(label = 'Covariate Index') + 
  ylab(label = 'Nonzero Coefficient Probability at p = 0.90')

ggplot(data = nonzero.counter) + geom_histogram(aes(x = c(1:200), y = P4 / nsim), stat = 'identity') + 
  xlab(label = 'Covariate Index') + 
  ylab(label = 'Nonzero Coefficient Probability at p = 0.99')

# Question 4
# loading packages
packages <- c('car', 'caret', 'e1071', 'parallel', 'rstudioapi')
install.packages(packages)
lapply(packages, library, character.only = TRUE)
ncores <- parallel::detectCores()

# loading datasets
setwd(dir = dirname(path = rstudioapi::getActiveDocumentContext()$path)[1])
train.data <- read.csv(file = './Data/Problem4training.csv', header = TRUE)
train.df <- as.data.frame(x = train.data)
test.data <- read.csv(file = './Data/Problem4testing.csv', header = TRUE)
test.df <- as.data.frame(x = test.data)

# Part i
probit.model <- stats::glm(formula = Y ~ ., data = train.df, family = binomial(link = 'probit'))
probit.pred <- predict(object = probit.model, newdata = test.df)
Metrics::mse(actual = test.df$Y, predicted = probit.pred)

predict(object = probit.model, newdata = test.df)

# Part ii
# using bootstrap method to construct CI
boot.statistic <- function(data, index) {
  model <- stats::glm(formula = Y ~ ., data = data, family = binomial(link = 'probit'), subset = index)
  coefficients <- coef(object = model)
  return (coefficients['X.1'] + exp(x = coefficients['X.2']) + coefficients['X.3'] ^ 2)
}

for (R in rep(x = 10, times = 5)) {
  probit.boot <- boot::boot(data = train.df, statistic = boot.statistic, R = R, ncpus = ncores - 1)
  ci <- boot::boot.ci(boot.out = probit.boot, conf = 0.77, type = 'perc')
  print(ci)
}

# Part v
# caret::train(x = train.df[, 2:ncol(x = train.df)], y = train.df$Y, method = 'glmStepAIC')
MASS::stepAIC(object = probit.model, direction = 'forward')
summary(object = probit.model)

# Part vi
# check for high collinearity (e.g. >= 0.80 in absolute value)
sym.correlation <- cor(x = train.df[, 2:ncol(x = train.df)], use = 'pairwise.complete.obs')
length(x = which(abs(x = sym.correlation) >= 0.80))

# OR compute VIF for each covariate
car::vif(mod = probit.model)

# OR check p-values for all pairs of covariates as interaction terms (not recommneded due to computational load)
probit.pairwise.model <- stats::glm(Y ~ .^2, data = train.df, family = binomial(link = 'probit'))
summary(object =  probit.pairwise.model)

# Part vii
lda.model <- MASS::lda(formula = Y ~ ., data = train.df)
lda.pred <- as.numeric(x = predict(object = lda.model, newdata = test.df, type = 'response')$class) - 1
1 - Metrics::accuracy(actual = test.df$Y, predicted = lda.pred)

qda.model <- MASS::lda(formula = Y ~ ., data = train.df)
qda.pred <- as.numeric(x = predict(object = qda.model, newdata = test.df, type = 'response')$class) - 1
1 - Metrics::accuracy(actual = test.df$Y, predicted = qda.pred)

svm.radial.model <- e1071::tune.svm(
  x = train.df[, 2:ncol(x = train.df)],
  y = train.df$Y,
  kernel = 'radial',
  gamma = seq(0.1, 10.0, 0.1),
)
svm.radial.pred <- as.numeric(x = predict(object = svm, newdata = test.df, type = 'response')$class) - 1

# contains err
svm.radial.model

svm.poly.model <- e1071::tune.svm(
  x = train.df[, 2:ncol(x = train.df)],
  y = train.df$Y,
  kernel = 'polynomial',
  degree = c(1:10)
)

# contains err
svm.poly.model

# Part viii
train.plot.df <- train.df
train.plot.df[, 4:ncol(x = train.plot.df)] <- 0
true.index <- which(x = svm.radial.pred > 0.50)

decision.grid <- expand.grid(seq(-4, 4, 0.1), seq(-4, 4, 0.1))
decision.grid

lda.pred <- as.numeric(x = predict(lda.model, grid)$class) - 1


svm.radial.pred 

predict(object = svm.radial.model$best.model, newdata = decision.grid)

ggplot(data = decision.grid, aes(x = Var1, y = Var2)) + geom_point()

, color = as.factor(x = svm.radial.pred))) +
  geom_point() + 
  # scale_x_continuous(breaks = ticks) + 
  # scale_y_continuous(breaks = ticks) +
  ggtitle(label = 'LDA') + 
  scale_color_manual(values = c('green', 'blue'), guide = 'none')
