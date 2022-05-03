n = 50;

clear p;

clf;
hold on;
grid on;

axis([0 1 0 1]);

[x, y] = ginput(1);

X = [x];
Y = [y];
n = 1;

while ~isempty([x, y])
  plot(x, y, 'ok');
  text(x+0.02, y+0.02, num2str(n), 'fontsize', 15);
  
  n = n+1;
  t = linspace(0, 1, 1000);
  nodes_t = linspace(0, 1, n);
  [x, y] = ginput(1);
  X = [X x];
  Y = [Y y];

  
  if exist("p", "var") == 0
    p = plot(spline(nodes_t, X, t), spline(nodes_t, Y, t));
  endif
  
  set(p, 'XData', spline(nodes_t, X, t));
  set(p, 'YData', spline(nodes_t, Y, t));
  
endwhile

hold off;

