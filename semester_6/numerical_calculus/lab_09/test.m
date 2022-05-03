f = @(x) 4 ./ (1 + x .^ 2);
e = 10 ^(-10);
pi
ra = romberg_aitken(f, 0, 1, e)
a = adaptive(f, 0, 1, e)

fplot(f, [0, 1]);
axis([0 1 0 4]);
