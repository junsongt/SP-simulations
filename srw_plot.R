# Simple Random Walk

source("D:/Practice Fields/R/function lib.R")
library("plot3D")
library("rgl")

data = read.table(file.choose(), header = TRUE, sep = ",")

# 1D SRW
plot(data$time, data$X_1D, xlab = "time", ylab = "Xt", type = "l")


# 2D SRW without time axis
plot(data$X_2D, data$Y_2D, xlab = "Xt", ylab = "Yt", type = "l")


# 2D SRW with time progress(3D plot)

# we can't rotate the plot in different perspectives in this one below
# plot3D::lines3D(x = data$time, y = data$X_2D, z = data$Y_2D, xlab = "time", ylab = "x", zlab = "y", theta = 35, phi = 0)

# using rgl package to create interactive 3D plot
plot3d(data$time, data$X_2D, data$Y_2D, xlab = "time", ylab = "x", zlab = "y")
