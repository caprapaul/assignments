f = @(x) 1 ./ (4 + sin(20 .* x));

0.8111579
repeated_simpson(f, 0, pi, 10)
repeated_simpson(f, 0, pi, 30)
