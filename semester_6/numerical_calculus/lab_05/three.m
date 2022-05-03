f = @(x) sin(2 * x);
df = @(x) 2 * cos(2 * x);

x = linspace(-5, 5, 15);
y = f(x);
dy = df(x);

X = -5 : 0.1 : 5;

clf;
hold on;

plot(X, f(X), ";f;");
plot(X, hermite(x, y, dy, X), ";H;");

hold off;
