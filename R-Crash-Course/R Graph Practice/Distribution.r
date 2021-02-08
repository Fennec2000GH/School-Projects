#DISTRIBUTION
png(file = "Dnorm.jpg")
x1 <- 1:200
y1 <- dnorm(x = x1, mean = 75, sd = 10)
data1 <- c()
num_trials <- 1000
for(x in 1:200) {
    count = round(num_trials * y1[x])
    for(index in (length(data1) + 1):(length(data1) + count))
        data1[index] = x
}
d1 <- hist(x = data1, breaks = seq(from = 1, to = 200, by = 1), border = "yellow", freq = TRUE, col = "purple", axes = TRUE, xlab = "X - value", ylab = "Frequency", main = "NormaL Distribution Histogram")
text(x = 140, y = 30, pos = 3, labels = c("mu = 75\n", "sigma = 10"))
dev.off()

png(file = "Pnorm.jpg")
x2 <- seq(from = 0, to = 40, by = 0.5)
y2 <- pnorm(q = x2, mean = 12, sd = 4)
p1 <- plot(x = x2, y = y2, xlab = "X - value", ylab = "Cumulative Probability", main = "Cumulative Probability Distribution Plot", sub = "Subtitle",
axes = TRUE, type = "h", col = "blue")
text(x = 2, y = 0.8, pos = 1, labels = c("mu = 12", "\nsigma = 4"))
dev.off()

png(file = "Qnorm.jpg")
x3 <- seq(from = 0, to = 1, by = 0.01)
y3 <- qnorm(p = x3, mean = 12, sd = 4)
q1 <- plot(x = x3, y = y3, xlab = "Cumulative Probability", ylab = "X - Value", main = "Value of Independent Variable with Cumulative Probability p", sub = "Subtitle",
axes = TRUE, col = "green", type = "l")
text(x = 0.2, y = 12, pos = 1, labels = c("mu = 12", "\nsigma = 4"))
dev.off()

png(file = "Rnorm.jpg")
x4 <- 1:100
y4 <- rnorm(n = x4, mean = 48, sd = 12)
r1 <- plot(x = x4, y = y4, xlab = "X - Value", ylab = "PDF - Value", main = "PDF of Random Distribution", sub = "Subtitle",
col = "red", type = 'h')
text(x = 10, y = 70, pos = 1, col = "green", labels = c("mu = 12", "\n\nsigma = 4"))
dev.off()
