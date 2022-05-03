function I = repeated_simpson(f, a, b, n)
  h = (b - a) / n;
  k1 = 1 : n;
  k2 = 1 : n - 1;
  x = @(K) a .+ K .* h;
  I = ((b - a) / (6 * n)) * (f(a) + f(b) + 4 * sum(f((x(k1 .- 1) + x(k1)) ./ 2)) + 2 * sum(f(x(k2))));
endfunction
