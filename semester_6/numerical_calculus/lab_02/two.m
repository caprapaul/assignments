T = @(n, t) cos(n .* acos(t));

t = [-1:0.1:1];

clf;  
hold on;

for i = [1:3]
  plot(t, T(i, t), sprintf(";T %d;", i))
endfor

hold off;
