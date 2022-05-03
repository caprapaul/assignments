a = @(x, f, m) ((m) * sum(x .* f) - sum(x) * sum(f)) / ((m) * sum(x .^ 2) - sum(x) ^ 2);
b = @(x, f, m) (sum(x .^ 2) * sum(f) - sum(x .* f) * sum(x)) / (m * sum(x .^ 2) - sum(x) ^ 2); 

x = [1 2 3 4 5 6 7];
f = [13 15 20 14  15 13 10];
n = length(x);

A = a(x, f, n)
B = b(x, f, n)

AB = polyfit(x, f, 1)

F = @(xx) A * xx + B; 

X = [0 : 0.1 : 10];

F(8)

clf;
hold on;

scatter(x, f, "x");
plot(X, F(X));

hold off;
