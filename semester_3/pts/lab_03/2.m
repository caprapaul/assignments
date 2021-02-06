pkg load statistics;

#p = input("p: ")
p = 0.2

for n = 100:100:1000
  x = 1:0.01:n;
  y1 = binocdf(x, n, p);
  y2 = normcdf(x, n * p, sqrt(n * p * (1 - p)));
  y3 = poisscdf(x, n * p);
  
  subplot(3, 1, 1)
  plot(x, y1)
  title("BINO")

  subplot(3, 1, 2)
  plot(x, y2)
  title("NORM")
  
  subplot(3, 1, 3)
  plot(x, y3)
  title("POISS")
  
  pause(0.5);
endfor