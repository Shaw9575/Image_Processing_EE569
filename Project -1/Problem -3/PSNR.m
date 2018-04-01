function p=PSNR(filename)
ima = readraw('Lena.raw');
nse = readraw(filename);
p = psnr(ima,nse,255)
end
