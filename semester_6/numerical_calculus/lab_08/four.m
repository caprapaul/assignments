f = @(x) x .* log(x);

d = 3;
n = ceil(sqrt(10 ^ d * (4 / 3)));

0.636294368858383

repeated_trapezium(f, 1, 2, n)

n2 = ceil((96 * 10 ^ d / 2880) ^ (1/4))

repeated_simpson(f, 1, 2, n2)