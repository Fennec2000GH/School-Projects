#NEEDED FUNCTIONS
increment <- function(x){
    x <- x + 1
}

decrement <- function(x){
    x <- x - 1
}

#TYPES OF MATRICES
#ROW / COLUMN MATRIX
writeLines(text = "ROW MATRIX", sep = "\n")
l1 <- c(rep(2, times = 4))
m1 <- matrix(data = l1, nrow = 1, ncol = length(l1), byrow = TRUE, dimnames = list("r1", c("c1", "c2", "c3", "c4")))
print(m1)
writeLines(text = "", sep = "\n\n")

writeLines(text = "COLUMN MATRIX", sep = "\n")
l2 <- c(rep(c(1:3), each <- 2))
m2 <- matrix(data = l2, nrow = length(l2), ncol = 1, byrow = FALSE, dimnames = list(c("r1", "r2", "r3", "r4", "r5", "r6"), "c1"))
print(m2)
writeLines(text = "", sep = "\n")

#SQUARE MATRIX
writeLines(text = "SQUARE MATRIX", sep = "n")
l3 <- c(1:9)
size_3x3_dimnames <- list(c("r1", "r2", "r3"), c("c1", "c2", "c3"))
m3 <- matrix(data = l3, nrow = 3, ncol = 3, byrow = TRUE, dimnames = size_3x3_dimnames)
print(m3)
writeLines(text = "", sep = "\n")

#NULL (ZERO) MATRIX
writeLines(text = "NULL (ZERO) MATRIX", sep = "\n")
m4 <- matrix(data = c(rep(0, times = 9)), nrow = 3, ncol = 3, byrow = TRUE, dimnames = size_3x3_dimnames)
print(m4)
writeLines(text = "", sep = "\n")

#DIAGONAL MATRIX
writeLines(text = "DIAGONAL MATRIX", sep = "\n")
m5 <- matrix(data <- c(rep(0, length.out <- 9)), nrow = 3, ncol = 3, byrow = TRUE, dimnames = size_3x3_dimnames)
for(i in seq.int(from = 1, to = dim(m5)[c(1, 0)]))
    for(j in seq.int(from = 1, to = dim(m5)[c(0, 1)]))
        if(i == j)
            m5[i, j] = sample(x = 1:9, size = 1, replace = TRUE, prob = NULL)
print(m5)
writeLines(text = "", sep = "\n\n")

#IDENTITY MATRIX
writeLines(text = "IDENTITY MATRIX", sep = "\n")
m6 <- matrix(data = c(rep(0, times = 9)), nrow = 3, ncol = 3, byrow = TRUE, dimnames = size_3x3_dimnames)
for(i in seq.int(from = 1, to = dim(m6)[c(TRUE, FALSE)]))
    for(j in seq.int(from = 1, to = dim(m6)[c(FALSE, TRUE)]))
        if(i == j)
            m6[i, j] = 1
print(m6)
writeLines(text = "", sep = "\n\n")

#UPPER TRANGULAR MATRIX
writeLines(text = "UPPER TRANGULAR MATRIX", sep = "\n")
m7 <- m4
for(i in seq.int(from = 1, to = dim(m7)[c(1, 0)]))
    for(j in seq.int(from = 1, to = dim(m7)[c(0, 1)]))
        if(i <= j)
            m7[i, j] = sample(x = 1:9, size = 1, replace = TRUE, prob = NULL)
print(m7)
writeLines(text = "", sep = "\n\n")

#LOWER TRIANGULAR MATRIX
writeLines(text = "LOWER TRIANGULAR MATRIX", sep = "\n")
m8 <- m4
for(i in seq.int(from = 1, to = dim(m8)[c(1, 0)]))
    for(j in seq.int(from = 1, to = dim(m8)[c(0, 1)]))
        if(i >= j)
            m8[i, j] = sample(x = 1:9, size = 1, replace = TRUE, prob = NULL)
print(m8)
writeLines(text = "", sep = "\n\n")

#NILPOTENT MATRIX (A^2 = 0)
writeLines(text = "NILPOTENT MATRIX", sep = "\n")
m9 <- matrix(data = rep(0, times = 36), nrow = 6, ncol = 6, byrow = FALSE,
dimnames = list(c("r1", "r2", "r3", "r4", "r5", "r6"), c("c1", "c2", "c3", "c4", "c5", "c6")))

if(dim(m9)[c(FALSE, TRUE)] %% 2 == 0) {
    temp <- c()
    for(j in 1:dim(m9)[c(FALSE, TRUE)] / 2) {
        temp[j] = sample(x = 1:9, size = 1, replace = FALSE, prob = NULL)
        for(i in 1:dim(m9)[c(TRUE, FALSE)])
            m9[i, j] = temp[j]
    }
    index <- length(temp)
    for(j in (dim(m9)[c(FALSE, TRUE)] / 2 + 1):(dim(m9)[c(FALSE, TRUE)])) {
        for(i in 1:dim(m9)[c(TRUE, FALSE)])
            m9[i, j] = -temp[index]
        decrement(index)
    }
} else {
    temp <- c()
    for(j in 1:(dim(m9)[c(FALSE, TRUE)] - 1) / 2) {
        temp[j] = sample(x = 1:9, size = 1, replace = FALSE, prob = NULL)
        for(i in 1:dim(m9)[c(TRUE, FALSE)])
            m9[i, j] = temp[j]
    }
    for(i in 1:dim(m9)[c(TRUE, FALSE)])
        m9[i, (dim(m9) + 1) / 2] = 0
    index <- length(temp)
    for(j in 1:((dim(m9)[c(FALSE, TRUE)] + 3) / 2):(dim(m9)[c(FALSE, TRUE)])) {
        for(i in 1:dim(m9)[c(TRUE, FALSE)])
            m9[i, j] = -temp[index]
        decrement(index)
    }
}
print(m9)
#MATRIX OPERATIONS
A <- matrix(data = 1:9, nrow = 3, ncol = 3, byrow = TRUE, dimnames = size_3x3_dimnames)
B <- matrix(data = seq(from = 10, to = 90, by = 10), nrow = 3, ncol = 3, byrow = TRUE, dimnames = size_3x3_dimnames)
writeLines(text = "Matrix A", sep = "\n")
print(A)
writeLines("\n\nMatrix B", sep = "\n")
print(B)
writeLines(text = "\n\nA + B", sep = "\n")
print(A + B)
writeLines(text = "\n\nA - B", sep = "\n")
print(A - B)
writeLines(text = "\n\nA * B", sep = "\n")
print(A * B)
writeLines(text = "\n\nA / B", sep = "\n")
print(A / B)
