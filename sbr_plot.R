# Standard Brownian Motion

source("D:/Practice Fields/R/function lib.R")
library("plot3D")
library("rgl")


data = read.table(file.choose(), header = TRUE, sep = ",")


par(pty="s")

# 1D SBM
plot(data$time, data$X_1D, xlab = "time", ylab = "Xt", type = "l")


# 2D SBM without time axis
plot(data$X_2D, data$Y_2D, xlab = "Xt", ylab = "Yt", asp = 1)


# 2D SBM with time progress(3D plot)

# we can't rotate the plot in different perspectives in this one below
# plot3D::lines3D(x = data$time, y = data$X_2D, z = data$Y_2D, xlab = "time", ylab = "x", zlab = "y", theta = 35, phi = 0)

# using rgl package to create interactive 3D plot
plot3d(data$time, data$X_2D, data$Y_2D, xlab = "time", ylab = "Xt", zlab = "Yt", type = "l")
