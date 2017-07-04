data = read.csv(file="E:/mywork/diseasedata/HCC_gene_expression.txt",head=T,row.names=1);
row.names(data) <- data$Name;
data <- data[,2:length(data[1,])];
data <- data.matrix(data);

cname <- colnames(data);
cname <- cname[2:length(data[1,])];

color.map <- function(cname) { if (cname =="N") "#FF0000" else "#0000FF" };
patientcolors <- unlist(lapply(cname, color.map));
heatmap(data, col=topo.colors(100), ColSideColors=patientcolors)

lib