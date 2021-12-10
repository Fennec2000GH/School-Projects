
X <- rep(x = c('Seat belt', 'None'), each = 4)
Y <- rep(x = c('Yes', 'No'), each = 2)
Z <- rep(x = c('Nonfatal', 'Fatal'), times = 4)
count <- c(1105, 14, 411111, 483, 4624, 497, 157342, 1008)

df <- data.frame(
  X = as.factor(x = X),
  Y = as.factor(x = Y),
  Z = as.factor(x = Z),
  count = count
)

stats::glm(formula = count ~ X + Y + Z + X:Y + X:Z + Y:Z, data = df, family = poisson)
