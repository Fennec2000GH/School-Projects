
packages <- c('FNN', 'fields',  'mgcv', 'rstudioapi',  'splines')
install.packages(packages)
lapply(packages, library, character.only = TRUE)

# configuring working directory path
path <- rstudioapi::getSourceEditorContext()$path
split.index <- dplyr::last(x = unlist(gregexpr(pattern = '/', text = path)))
path.wd <- substr(x = path, start = 1, stop = split.index)
setwd(dir = path.wd)

# reading data
data <- read.csv(file = 'TrainingData.csv', header = TRUE)
x = data$x
y = data$y
df <- data.frame(x = x, y = y)
plot(x = x, y = y)

# data for predictions
xnew <- seq(-10, 10, by = 0.01)

# KNN regression
knn.model <- FNN::knn.reg(
  train = data.frame(x = x),
  test = data.frame(x = xnew),
  y = y,
  k = 10,
  algorithm = c('kd_tree', 'cover_tree', 'brute')
)

as.vector(knn.model)

# local regression
local.model <- stats::loess(
  formula = y ~ x,
  model = TRUE,
  span = 0.75, 
  degree = 5,
  family = c('gaussian', 'symmetric'),
  method = 'loess'
)

local.model
local.pred <- predict(object = local.model, newdata = xnew)

# generalized additive model regression
gam.model <- mgcv::gam(formula = y ~ x)
mgcv::predict.gam(gam.model, xnew)

finalPredictions <- data.frame(prediction1 = knn.model$pred,
                               prediction2 = local.pred)

finalPredictions
write.csv(finalPredictions, file="Qin_Caijun.csv")



