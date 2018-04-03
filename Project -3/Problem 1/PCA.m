function [T] = PCA()
X = Txt('Result.txt');
sum=zeros(25,1);
ZX = zeros(25,270000);
ZX1 = zeros(25,600);
T1 = zeros(9,600);
UR = zeros(25,9);
RX = zeros(9,600);
T = zeros(9,270000);
for i =1:600
for j=1:450
for k=1:25
sum(k)=sum(k)+X(k,i,j);
end
end
end
for k=1:25
sum(k)=sum(k)/600/450;
end
for i =1:600
for j=1:450
for k=1:25
ZX(k,(j-1)*600+i)=X(k,i,j)-sum(k);
end
end
end
for i=1:450
for j=1:600
ZX1(:,j)=ZX(:,(i-1)*600+j);
end
[U,~,~]=svd(ZX1);
UR(:,:)=U(:,1:9);
RX = UR'*ZX1;
for j=1:600
T(:,(i-1)*600+j)=RX(:,j);
end
end
end

