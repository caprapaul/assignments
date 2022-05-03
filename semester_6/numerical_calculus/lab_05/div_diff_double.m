function A = div_diff_double(x, f, df)
  n = length(x);
  z = repelem(x, 2);
  m = length(z);
  A = nan(m);
  A(:, 1) = repelem(f, 2);
  A(1 : 2 : m - 1, 2) = df;
  A0 = A(3 : 2 : m - 1, 1) - A(2 : 2 : m - 2, 1);
  x0 = z(3 : 2 : m - 1) - z(2 : 2 : m - 2);
  A(2 : 2 : m - 2, 2) = A0 ./ x0';
  
  for j = 3 : m
    A0 = A(2 : m - j + 2, j - 1) - A(1 : m - j + 1, j - 1);
    z0 = z(j : m) - z(1 : m - j + 1);
    A(1 : m - j + 1, j) = A0 ./ z0';
  endfor
endfunction