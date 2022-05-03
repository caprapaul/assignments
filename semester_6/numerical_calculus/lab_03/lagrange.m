function Y = lagrange (x, f, X)
  Y = arrayfun(@(XX) lagrange_inner(x, f, XX), X);
end
function Y = lagrange_inner (x, f, X)
  n = length(x);
  i = 1 : n;
  A = @(i) 1 / prod(x(i) - x([1 : i - 1, i + 1 : n]));

  a = arrayfun(A, i);
  Y = sum((a .* f(i)) ./ (X - x(i))) / sum(a ./ (X - x(i)));
end
