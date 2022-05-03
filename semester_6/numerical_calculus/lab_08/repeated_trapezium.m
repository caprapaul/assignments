function I = repeated_trapezium(f, a, b, n)
  h = (b - a) / n;
  k = 1 : n - 1;
  x = a + k .* h;
  I = ((b - a) / (2 * n)) * (f(a) + f(b) + 2 * sum(f(x)));
endfunction
