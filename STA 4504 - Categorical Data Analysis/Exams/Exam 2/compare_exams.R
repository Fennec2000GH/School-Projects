library(ggplot2)
library(reshape2)
library(plyr)
library(DescTools)
library(car)

Input="
Exam1 Exam2
104	83
101	86
99	95
97	75
95	92
94	85
94	87
94	71
91	89
90	60
88	58
87	72
85	83
83	65
81	85
80	96
80	66
80	79
79	72
77	70
75	52
75	72
75	69
74	60
73	77
72	73
72	65
70	62
67	68
66	65
66	74
64	48
61	50
60	64
59	76
57	64
56	71
56	70
56	63
54	50
54	33
48	71
41	43
40	68
"

exams=read.table(textConnection(Input),header=TRUE)
exams_lf=melt(exams) #put data in long format

######################
#### DESCRIPTIVE #####
######################

summary(exams)
mu=ddply(exams_lf,~variable,summarise,means=mean(value),sds=sd(value));mu
ddply(exams_lf,~variable,summarise,means=mean(value,trim=0.05),sds=sd(Trim(value,trim=0.05)))

# boxplots
ggplot(exams_lf,aes(x=variable, y=value)) +
  geom_boxplot() +
  geom_jitter(width=0.15, alpha=0.4)

# histograms
ggplot(exams_lf, aes(x=value, fill=variable))+
  geom_histogram(binwidth=5,center=2.5,color="grey80")+
  facet_grid(variable~.)+
  geom_vline(data=mu, aes(xintercept=means),
             linetype="solid")

#ggplot(exams_lf, aes(x=value, fill=variable, color=variable)) +
#  geom_histogram(alpha=0.5,position="identity",
#                 binwidth=10,
#                 center=5)+
#  geom_vline(data=mu, aes(xintercept=means, color=variable),
#             linetype="dashed")+
#  theme(legend.position="top")

######################
##### INFERENCE ######
######################

### Test for difference between paired data
with(exams,t.test(Exam1,Exam2,paired=TRUE))
with(exams,wilcox.test(Exam1,Exam2,paired=TRUE))

###############################################################################################################

### For 3 exams we will use 1-way ANOVA or distribution free Kruskal-Wallis
# IF WE CAN ASSUME EQUAL VARIANCE
with(exams_lf,leveneTest(value,variable))

## use Iterative Weighted Least Squares, does not require homogeneity of variance
# Method 1
library(MASS)
reg.iwls=rlm(value~variable,data=exams_lf,wt.method="inv.var",method="M")
summary(reg.iwls)

# Method 2
glm.reg=glm(value~variable,data=exams_lf,method="glm.fit")
summary(reg.iwls)

### could try box-cox power transformation
