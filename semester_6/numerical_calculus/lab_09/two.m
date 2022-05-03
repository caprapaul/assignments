f = @(x) 2 ./ (1 + x .^ 2);

e = 10 ^(-4);

ro = romberg(f, 1, 1.5, e)
ro_a = romberg_aitken(f, 1, 1.5, e)
