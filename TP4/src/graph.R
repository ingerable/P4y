library(ggplot2)

perf <-read.table("dataGranulometry.dat", header=TRUE, fill=TRUE)
taille <- perf[,1]
volume <- perf[,2]

png("granulometry.png")
i<-qplot(taille, volume, data=perf, main="courbe granulométrique pour taille de disque variante", geom="smooth", method="loess") + labs(y="volume de l'image", x="taille de l'élément structurant")
print(i)
dev.off()


png("dérivé.png")
dY <- diff(taille)/diff(volume)
dX <- rowMeans(embed(taille,2))
derive <- plot(dX,dY,type="l",main="Derivative")
print(derive)
dev.off()
