x = [1.0 1.5 2 3 4];
y = [0.0 0.17609 0.30103 0.47712 0.60206];

X = 1 : 0.1 : 5;

log10(2.5)
newton(x, y, 2.5)

clf;
hold on;

plot(X, log10(X), ";log10;");
plot(X, newton(x, y, X), ";N;");

hold off;
