library(ggplot2)

perf <-read.table("impulseNoiseMedian3.dat", header=TRUE, fill=TRUE)


png("MSE.png")
i<-qplot(p, mse , data=perf, main="MSE entre original et bruit impulsionnel variant filtre median 3", geom="point", method="loess") + labs(x="probabilité de bruitage impulsionnel", y="valeur du MSE")
print(i)
dev.off()

