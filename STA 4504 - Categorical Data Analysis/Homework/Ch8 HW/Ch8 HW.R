# Ch8 HW
# 11/13/2021

install.packages('psych')
library(psych)

mat.txt <- 
'
  394 17 81 38
  8 596 74 59
  29 32 769 35
  10 24 35 417
'

mat  <- matrix(data = scan(text = mat.txt), nrow = 4, byrow = TRUE)
mat

mat.kappa <- psych::cohen.kappa(x = mat)
mat.kappa$weight
mat.kappa
