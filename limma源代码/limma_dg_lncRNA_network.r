#/home/R-3.2.1/bin/R

a1 = read.table(file="E:/mywork/diseasedata/T.txt",head=T,row.names=1); print(dim(a1))
b1 = read.table(file="E:/mywork/diseasedata/N.txt",head=T,row.names=1); print(dim(b1))



#print(hello)


library(limma);

gene_name = rownames(a1);

a1 =  data.matrix(a1) 
b1 =  data.matrix(b1) 

a1[is.na(a1)] = 0;
b1[is.na(b1)] = 0;

print(dim(a1))
print(dim(b1))
gene_expression_1 = cbind(a1,b1);
rownames(gene_expression_1) = gene_name;

dim(gene_expression_1)

temp1 = 95# samples
temp2 = 39# samples

#print(gene_expression_1[1:3,]);

#colnames(gene_expression_1) = c(rep(0,length(temp1)),rep(1,length(temp2)))
#y1 = cbind(t1=1,t1vst2=c(rep(0,length(temp1)),rep(1,length(temp2))));
#y1= model.matrix(~0+factor(c(rep(0,length(temp1)),rep(1,length(temp2)))));

#*************here constructing the design and constrast matrix **********


rownames(gene_expression_1)<- gene_name;
design = cbind(norm=c(rep(1,temp1),rep(0,temp2)),DM=c(rep(0,temp1),rep(1,temp2))); # design matrix; 
fit = lmFit(gene_expression_1,design);
cont.matrix = makeContrasts(DMvsNo=DM-norm,levels=design)
fit2 = contrasts.fit(fit,cont.matrix);
fit2 = eBayes(fit2)
 all=topTable(fit2,adjust="BH",n=dim(gene_expression_1)[1]);
options(digit=3)

dif_vector = array(0,dim=c(dim(a1)[1],1))

for(i in 1:dim(a1)[1])
{
dif_vector[i,1] = median(a1[i,],na.rm=T)-median(b1[i,],na.rm=T);

}

m_pvalue = cbind(all,dif_vector);

write.csv(m_pvalue,file="E:/mywork/diseasedata/Limma_result.csv");

#
save(m_pvalue,file="E:/mywork/diseasedata/limma_result.RData")


#print(all[1:5,])
#Bindex= which(all[,(dim(all)[2]-1)]<0.1)
#print(length(Bindex))

#output = all[Bindex,]
 
#write.csv(output,file="network_comparison_pvalue.csv");
 

#print(a[1:5,10:14])
 

