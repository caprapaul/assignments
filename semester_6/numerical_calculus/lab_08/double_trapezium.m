function I = double_trapezium(f, a, b, c, d)
  ab = (a + b) / 2;
  cd = (c + b) / 2;
  I = ((b - a) * (d - c) / 16) * floor(f(a, c) + f(a, d) + f(b, c) + f(b, d) 
  + 2 * f(ab, c) + 2 * f(ab, d) + 2 * f(a, cd) + 2 * f(b, cd) + 4 * f(ab, cd));
endfunction
  