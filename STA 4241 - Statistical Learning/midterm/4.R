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
