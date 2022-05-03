f = @(x) 1 ./ (1 + x .* x);
x = @(i, n) i .* (10 / n) - 5;
y = @(i) i ./ 10 - 5;

n = 2 : 2 : 8;

xi = @(N) x(0 : N, N);

yi = y(0 : 100);

fyi = f(yi);

E = @(N) abs(f(yi) - lagrange(xi(N), f(xi(N)), yi))
Emax = @(N) max(E(N));
En = arrayfun(Emax, n);
clf;
hold on;
plot(yi, f(yi), ";f;");
arrayfun(@(N) plot(yi, lagrange(xi(N), f(xi(N)), yi), sprintf(";P%d;", N)), n)
hold off;
