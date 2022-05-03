f = @(x)(1 + cos(pi .* x)) ./ (1 + x);

x = linspace(0, 10, 21);
y = f(x);

X =[0:0.01:10];

clf;
hold on;
plot(X, f(X), ";f;");
plot(X, lagrange(x, y, X), ";Lagrange;");
hold off;
