function I = simpson(f, a, b)
  I = ((b - a) / 6) * floor(f(a) + 4 * f((a + b) / 2) + f(b));
endfunction
  