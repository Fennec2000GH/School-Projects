# PlantGrowth data
head(PlantGrowth)
tail(PlantGrowth)

# Box-plots to compare groups
library(ggplot2)

ggplot(PlantGrowth, aes(x=group, y=weight, fill=group)) +
  geom_boxplot() +
     stat_summary(fun=mean, colour="darkred", geom="point", 
                           shape=18, size=3)

# group means
means <- aggregate(weight ~  group, PlantGrowth, mean)

# group standard deviation
sdv <- aggregate(weight ~  group, PlantGrowth, sd)

# summary of data by group
tapply(PlantGrowth$weight, PlantGrowth$group, summary)

# analysis of variance
growth_aov <- aov(weight~group, data=PlantGrowth)

summary(growth_aov)

# Computation of sum of squares within
varv <- aggregate(weight ~  group, PlantGrowth, var)
ssw <- sum(9*varv$weight)
ssw

# Checking for normality of the data

# Note that residuals are y_ij - bar(y_i.)
gmeans <- rep(means$weight, each=10) #create bar(y_i.), 10 is the number of observations per group
res <- PlantGrowth$weight - gmeans #residuals

# Formal normality test, H0: The population is normally distributed
shapiro.test(res)

# Histogram of residual
hist(res, col='steelblue')

# Q-Q plot
qqnorm(res, pch=16)
qqline(res)


# Multiple comparisons

tukey.test <- TukeyHSD(growth_aov)
tukey.test
plot(tukey.test)


##########################################
# Example of small within sample variation
# and large between sample variation
##########################################

sam1 <- c(5.9,5.92,5.91,5.89,5.88)

sam2 <- c(5.51,5.50,5.50,5.49,5.50)

sam3 <- c(5.01,5.00,4.99,4.98,5.02)

treatment <- as.factor(c(rep(1,5), rep(2,5), rep(3,5)))

df_ex <- data.frame(y=c(sam1,sam2,sam3),treatment)

ggplot(df_ex, aes(x=treatment, y=y, fill=treatment)) +
  geom_boxplot() +
     stat_summary(fun=mean, colour="darkred", geom="point", shape=18, size=3)

##########################################
# Example TukeyHSD with unbalanced data
##########################################

sam1 <- c(5.9,5.92,5.91,5.89,5.88)

sam2 <- c(5.51,5.50,5.50,5.49,5.50)

sam3 <- c(5.01,5.00,4.99,5.02)

treatment <- as.factor(c(rep(1,5), rep(2,5), rep(3,4)))

df_ex <- data.frame(y=c(sam1,sam2,sam3),treatment)

ex_aov <- aov(y~treatment, data=df_ex)
summary(ex_aov)

TukeyHSD(ex_aov)


