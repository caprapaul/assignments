f = @(x) sin(x);
df = @(x) cos(x);

x = [0 pi/2 pi 3*pi/2 2*pi];
y = f(x);

X = pi / 4;

# a
fx = f(X)
s_nat = spline(x, y, X)
s_clamp = spline(x, [df(x(1)) y df(x(end))], X)

# b
clf;
hold on;

X = 0 : 0.1 : 2 * pi;

plot(X, f(X), ";f;");
plot(X, spline(x, y, X), ";natural spline;");
plot(X, spline(x, [df(x(1)) y df(x(end))], X), ";clamped spline;");

hold off;
