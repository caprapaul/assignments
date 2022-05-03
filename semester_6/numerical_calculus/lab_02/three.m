f = @(x) exp(x);



x = [-1:0.1:3];
x0 = zeros(size(x));
n = 6;

clf;
hold on;

plot(x, f(x), ";EXP;")

for i = [1:n]
  plot(x, three_P(i, x, x0, f), sprintf(";P%d;", i))
endfor

hold off;
