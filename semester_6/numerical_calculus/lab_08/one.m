f = @(x) 2 ./ (1 + x .^ 2);

X = 1 : 0.01 : 10;
n = ceil(sqrt(10 ^ 5 * (4 / 3)));
pi;
repeated_trapezium(f, 0, 1, 1)

clf;
hold on;

vertices = [
0 0
0 f(0)
1 f(1)
1 0
];

plot(X, f(X), ';f;');
fill(vertices(:,1), vertices(:,2), "g");

d = 5;
n2 = ceil((96 * 10 ^ d / 2880) ^ (1/4));

repeated_simpson(f, 0, 1, 1)
