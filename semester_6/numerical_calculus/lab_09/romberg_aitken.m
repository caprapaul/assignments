function res = romberg_aitken(f, a, b, e)
  i = 2;
  rt = repeated_trapezium(f, a, b, 1);
  T = [rt];
  
  do
    T = resize(T, [i, i]);
    rt = repeated_trapezium(f, a, b, 2 ^ (i - 1));
    T(i, 1) = rt;
    
    for j = 2 : i
      T(i, j) = ((4 ^ (-j + 1)) .* T(i - 1, j - 1) - T(i, j - 1)) / ((4 ^ (-j + 1)) - 1);
    endfor
    
    err = abs(T(i, i) - T(i - 1, i - 1));

    i = i + 1;
  until err <= e
  res = T(i - 1, i - 1);
endfunction

