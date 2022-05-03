f = @(x) exp(sin(x));

x = linspace(0, 6, 13);
y = f(x);

X = -0.3 : 0.1 : 6;

clf;
hold on;

scatter(x, y);
plot(X, f(X), "g;f;");
plot(X, newton(x, y, X), "m;N;");

hold off;
