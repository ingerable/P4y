library(ggplot2)

perf <-read.table("thresholding.dat", header=TRUE, fill=TRUE)
taille <- perf[,1]
volume <- perf[,2]
pourcentage <- perf[,0]

png("granulometry.png")
i<-qplot(taille, p, data=perf, main="courbe granulométrique pour taille de disque variante", geom="smooth", method="loess", color=type) + labs(y="pourcentage de pixel restant", x="taille de l'élément structurant") +
  scale_x_continuous(breaks = seq(0, 10, 1))
print(i)
dev.off()



png("dérivé.png")
dY <- diff(taille)/diff(volume)
dX <- rowMeans(embed(taille,2))
derive <- plot(dX,dY,type="l",main="Derivative")
print(derive)
dev.off()
