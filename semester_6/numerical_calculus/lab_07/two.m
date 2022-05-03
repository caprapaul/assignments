x = [0 10 20 30 40 60 80 100];
f = [0.0061 0.0123 0.0234 0.0424 0.0738 0.1992 0.4736 1.0133];

poly1 = polyfit(x, f, 1);
poly2 = polyfit(x, f, 2);

val1 = polyval(poly1, 45)
val2 = polyval(poly2, 45)
E1 = abs(val1 - 0.095848)
E2 = abs(val2 - 0.095848)

X = [0 : 0.1 : 100];

clf;
hold on;

scatter(x, f, "x");
plot(X, polyval(poly1, X), ";Degree 1;");
plot(X, polyval(poly2, X), ";Degree 2;");
plot(X, polyval(polyfit(x, f, 4), X), ";Degree 4;");

hold off;
