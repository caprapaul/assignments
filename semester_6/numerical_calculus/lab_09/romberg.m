function Q = romberg(f, a, b, e)
  h = (b - a);  
  Q = romberg_inner(f, a, b, h, 0);
  k = 1;
  
  do
    newQ = romberg_inner(f, a, b, h, k);
    err = abs(newQ - Q);
    Q = newQ;
    k = k + 1;
  until err <= e
endfunction

function Q = romberg_inner(f, a, b, h, k)
  if k == 0
    Q = h / 2 * (f(a) + f(b));
  else
    j = [1 : 2 ^ (k - 1)];
    x = a + ((2 * j - 1) / (2 ^ k)) * h;
    Q = 1 / 2 * romberg_inner(f, a, b, h, k - 1) + (h / (2 ^ k)) * sum(f(x));
  endif
endfunction
