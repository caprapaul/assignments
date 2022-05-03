r = 110;
p = 75;

f = @(x) (1 - ((p / r) ^ 2) .* sin(x)) .^ (1 / 2);

6.3131
H3 = ((60 * r) / (r ^ 2 - p ^ 2)) * repeated_trapezium(f, 0, 2 * pi, 3)
H10 = ((60 * r) / (r ^ 2 - p ^ 2)) * repeated_trapezium(f, 0, 2 * pi, 10)
 