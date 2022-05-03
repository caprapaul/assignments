clear p;
clf;
hold on;
grid on;

deg = 2;

axis([0 3 0 5]);

[x, y] = ginput(1);

X = [x];
Y = [y];


XX = [0 : 0.1 : 100];

while ~isempty([x, y])
  plot(x, y, 'xk');
  
  [x, y] = ginput(1);
  
  poly = polyfit(X, Y, deg);
  val = polyval(poly, XX);
  
  E = max(abs(Y - polyval(poly, X)))
  
  if E > 0.1
    deg = deg + 1
  endif
  
  X = [X x];
  Y = [Y y];
  
  if exist("p", "var") == 0
    p = plot(XX, val);
  endif
  
  set(p, 'YData', val);
endwhile

hold off;
  