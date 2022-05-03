function I = trapezium(f, a, b)
  I = (b - a / 2) * floor(f(a) + f(b));
endfunction
