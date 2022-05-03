function [H, dH] = hermite(x, f, df, X)
  z = repelem(x, 2);
  n = length(z);
  table = div_diff_double(x, f, df);
  [H, dH] = arrayfun(@(XX) hermite_inner(x, f, df, XX, table, z, n), X);
endfunction
function [H, dH] = hermite_inner(x, f, df, X, table, z, n)
  c = table(1, :);
  
  H = c(1);
  dH = 0;
  P = X - z(1);
  dP = 1;
  
  for k = 2 : n
    H = H + c(k) * P;
    dH = dH + c(k) * dP;
    dP = dP * (X - z(k)) + P;
    P = P * (X - z(k));
  endfor
endfunction