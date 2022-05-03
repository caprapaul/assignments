x = [-1:0.1:1];
n = 4;

clf;  
hold on;

for i = [1:n]
  plot(x, two_b_T(i, x), sprintf(";T %d;", i))
endfor

hold off;
