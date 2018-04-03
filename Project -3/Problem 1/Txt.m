function [I]=Txt(filename)
G = textread(filename,'%f');
I = reshape(G,25,600,450);
end
