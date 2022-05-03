f = @(x) (100 ./ (x .^ 2)) .* sin(10 ./ x);

a = 1;
b = 3;

e = 10 ^ (-4);
-1.4260247818
ad = adaptive(f, a, b, e)
rs50 = repeated_simpson(f, a, b, 50);
rs100 = repeated_simpson(f, a, b, 100);

fplot(f, [a,b])
