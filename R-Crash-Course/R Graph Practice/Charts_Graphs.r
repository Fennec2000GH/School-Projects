#CHARTS AND GRAPHS
#PIE CHART
library(plotrix)

png(file = "Pie_Chart.jpg")
pie1 <- list(c("Mumbai", "Tianjin", "Manila", "Moscow", "Tokyo", "Dhaka", "Istanbul", "Karachi", "Beijing", "Shanghai"),
c(12.4, 12.8, 12.9, 13.2, 13.6, 14.5, 14.7, 18, 18.6, 24.1))
names(pie1) <- c("City", "Population")
pie(x = unlist(pie1[2]), labels = unlist(pie1[1]), col = rainbow(length(unlist(pie1[1]))), main = "World City Populations", clockwise = FALSE)
dev.off()

png(file = "Pie_Chart_2.jpg")
pie2 = list(c("China", "U.S.", "India", "Japan", "Germany"), c(25.270, 20.494, 10.505, 5.594, 4.356))
pie3D(x = unlist(pie2[2]), explode = 0.1, labels = unlist(pie2[1]))
dev.off()

#BAR GRAPH
png(file = "Bar_Graph.jpg")
bar1 = list(c("Burj Khalifa", "Shanghai Tower", "Abraj Al-Bait Clock Tower", "	Ping An Finance Centre", "Lotte World Tower"),
c(828, 632, 601, 599, 555))
barplot(unlist(bar1[2]), xlab = "Name of Structure", ylab = "Height (m)", main = "Top 5 Tallest Structures",
col = c("blue", "green", "red", "yellow", "purple"), border = "pink", names.arg = unlist(bar1[1]))
dev.off()

#BOXPLOT
png(file = "Boxplot.jpg")
prob_weights <- c(1, 1, 2, 4, 8, 8, 4, 2, 1, 1)
box1 <- data.frame (
    Exam_1 = sample(x = seq.int(from = 10, to = 100, by = 10), size = 20, replace = TRUE, prob = prob_weights),
    Exam_2 = sample(x = seq.int(from = 10, to = 100, by = 10), size = 20, replace = TRUE, prob = prob_weights),
    Exam_3 = sample(x = seq.int(from = 10, to = 100, by = 10), size = 20, replace = TRUE, prob = prob_weights),
    Final = sample(x = seq.int(from = 10, to = 100, by = 10), size = 20, replace = TRUE, prob = prob_weights)
)

print(box1)
boxplot(x = c(box1["Exam_1"], box1["Exam_2"], box1["Exam_3"], box1["Final"]), horizontal = TRUE, notch = TRUE, varwidth = TRUE, col = rainbow(length(box1)),
xlab = "Exam", ylab = "Scores", main = "Exam Statistics for MAC2313 (Spring 2019)", names = c("Exam 1", "Exam 2", "Exam 3", "Final Exam"))


dev.off()


#HISTOGRAM
png(file = "Histogram.jpg")
hist1 <- c()
for(i in 1:2000)
    hist1[i] = sample(x = 1:6, size = 1, replace = TRUE, prob = NULL)
hist(hist1, xlab = "2000 Dice Rolls", ylab = "Frequency", main = "Normal Distribution of Rolling a Die", col = "blue", border = "black",
xlim = c(0, 7))
dev.off()

#LINE GRAPH
png(file = "Line_Graph.jpg")
years <- c(2015, 2016, 2017, 2018, 2019, 2020)
line1 <- c(120, 140, 400, 320, 280, 260)
line2 <- c(160, 180, 220, 226, 218, 340)
line3 <- c(180, 190, 230, 280, 320, 360)

plot(x = years, y = line1, col = "red", xlab = "Year", ylab = "Count", main = "Frequency of Infected Persons by Year", type = 'o')
lines(x = years, y = line2, col = "green", type = 'o')
lines(x = years, y = line3, col = "blue", type = 'o')
colors <- c("red", "green", "blue")
legend("topleft", c("Line 1", "Line 2", "Line 3"), fill = colors, text.col = colors, border = "black", bg = "gray", title = "Legend", title.col = "black", trace = TRUE)
dev.off()

#SCATTERPLOT
png(file = "Scatterplot.jpg")
x1 <- c(1, 3, 3, 5, 6, 8, 8, 9, 12, 15, 15, 16)
y1 <- c(25, 29, 30, 25, 24, 28, 38, 40, 44, 42, 46, 48)
plot(x = x1, y = y1, col = "green", xlab = "Daily Water (mL)", ylab = "Height After 3 Months", main = "Plant Growth Due to Water Used", axes = TRUE)
model <- lm(formula = y1 ~ x1)
abline(model)
dev.off()
