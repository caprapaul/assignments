pkg load statistics;

#n = input("Number of trials: ");
#p = input("Probability of success: ");

n = 20;
p = 0.5;

x = 0:1:n;
w = 0:0.001:n;

y1 = binopdf(x, n, p);
y2 = binocdf(w, n, p);

subplot(2, 1, 1)
plot(x, y1, "*")
title("PDF")

subplot(2, 1, 2)
plot(w, y2)
title("CDF")
