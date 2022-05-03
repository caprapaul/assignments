function retval = three_P (n, x, x0, f)
  retval = zeros(size(x));
  for k = 0:n
    retval = retval + ((x - x0) .^ k / factorial(k)) .* f(x0);
  endfor
endfunction