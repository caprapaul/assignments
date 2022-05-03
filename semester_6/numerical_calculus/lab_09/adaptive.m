function I = adaptive(f, a, b, e)
  I1 = repeated_simpson(f, a, b, 1);
  I2 = repeated_simpson(f, a, b, 2);
  
  if abs(I1 - I2) < 15 * e
    I = I2;9
  else
    I = adaptive(f, a, (a + b) / 2, e / 2) + adaptive(f, (a + b) / 2, b, e / 2);
  endif
endfunction