function Y = newton(x, f, X)
  Y = arrayfun(@(XX) newton_inner(x, f, XX), X);
endfunction
function Y = newton_inner(x, f, X)
  n = length(x);
  table = div_dif(x, f);
  c = table(1, :);
  prod = cumprod([1, X - x(1 : n - 1)]);
  Y = sum(c .* prod);
endfunction