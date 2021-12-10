library(reshape2)
library(splitstackshape)

# A for Alcohol
# C for Cigarettes
# M for Marijuana


Input="
alcohol cigarettes marijuana count  
yes yes yes 911
yes yes no 538
yes no yes 44
yes no no 456
no yes yes   3
no yes no 43
no no yes 2
no no no 279
"
sub=read.table(textConnection(Input),header=T)
n=sum(sub$count)

sub_melt=melt(sub,id.vars = "count")
sub_melt=as.data.frame(sub_melt)

long.sub=expandRows(sub_melt,"count")
long.sub$subject=rep(1:n,times=3)

# sort dataframe by subject rather than variable
long.sub=long.sub[order(long.sub$subject),]

dimnames(long.sub)[[2]]=c("Substance","Use","Student")

head(long.sub)
tail(long.sub)


####################################
# For part (e)
####################################
Input="
 A C M R G count
 1 1 1 1 1 405 
 1 1 2 1 1 268 
 1 1 1 1 2 453 
 1 1 2 1 2 228
 1 1 1 2 1  23 
 1 1 2 2 1  23 
 1 1 1 2 2  30 
 1 1 2 2 2  19
 1 2 1 1 1  13 
 1 2 2 1 1 218  
 1 2 1 1 2  28 
 1 2 2 1 2 201
 1 2 1 2 1   2 
 1 2 2 2 1  19 
 1 2 1 2 2   1 
 1 2 2 2 2  18
 2 1 1 1 1   1 
 2 1 2 1 1  17 
 2 1 1 1 2   1 
 2 1 2 1 2  17
 2 1 1 2 1   0 
 2 1 2 2 1   1 
 2 1 1 2 2   1 
 2 1 2 2 2   8
 2 2 1 1 1   1 
 2 2 2 1 1 117 
 2 2 1 1 2   1 
 2 2 2 1 2 133
 2 2 1 2 1   0 
 2 2 2 2 1  12 
 2 2 1 2 2   0 
 2 2 2 2 2  17
"

sub1=read.table(textConnection(Input),header=T)
sub1$A=factor(sub1$A,levels=1:2,labels=c("yes","no"))
sub1$C=factor(sub1$C,levels=1:2,labels=c("yes","no"))
sub1$M=factor(sub1$M,levels=1:2,labels=c("yes","no"))
sub1$R=factor(sub1$R,levels=1:2,labels=c("white","other"))
sub1$G=factor(sub1$G,levels=1:2,labels=c("female","male"))

sub1_melt=melt(sub1,id.vars = c("R","G","count"))
sub1_melt=as.data.frame(sub1_melt)

long.sub1=expandRows(sub1_melt,"count")
long.sub1$subject=rep(1:n,times=3)

# sort dataframe by subject rather than variable
long.sub1=long.sub1[order(long.sub1$subject),]

dimnames(long.sub1)[[2]]=c("Race","Gender","Substance","Use","Student")
levels(long.sub1$Substance)=c("alcohol","cigarettes","marijuana")

head(long.sub1)
tail(long.sub1)