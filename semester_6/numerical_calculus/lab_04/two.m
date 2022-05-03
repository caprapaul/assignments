x = [1 2 3 4 5]
y = [22 23 25 30 28]

newton(x, y, 2.5);

X = 0 : 0.1 : 6;

clf;
hold on;

scatter(x, y);
plot(X, newton(x, y, X), ";N;");

hold off;
