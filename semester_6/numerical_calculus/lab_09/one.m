xi = @(a, b, n, i) a + ((b - a) / (2 * n)) + (i  - 1) .* ((b - a) / n);
rectangle_ = @(f, a, b, n) ((b - a) / n) * sum(f(xi(a, b, n, [1 : n])));

F = @(x) exp(-(x .^ 2));

0.1094
A = 1;
B = 1.5;

r1 = rectangle_(F, A, B, 1)

r150 = rectangle_(F, A, B, 150)
r500 = rectangle_(F, A, B, 500)

X = [1 : 0.01 : 1.5];

clf;
hold on;

plot(X, F(X), ';f;');
#fill(vertices(:,1), vertices(:,2), "g");
rectangle("Position", [A 0 B-A F((A+B)/2)]);

hold off;
