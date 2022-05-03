function retval = two_b_T (n, x)
  if (n == 0)
    retval = ones(size(x));
  elseif (n == 1)
    retval = x;
  else
    retval = 2 .* x .* two_b_T(n - 1, x) -  two_b_T(n - 2, x);
  endif
endfunction