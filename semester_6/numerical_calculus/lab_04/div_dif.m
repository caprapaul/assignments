function A = div_dif(x, f)
  n = length(x);
  A = [f', nan(n, n-1)];
  for j = [2:n]
    A0 = A(2 : n - j + 2, j - 1) - A(1 : n - j + 1, j - 1);
    x0 = x(j : n) - x(1 : n - j + 1);
    A(1 : n - j + 1, j) = A0 ./ x0';
  endfor
endfunction