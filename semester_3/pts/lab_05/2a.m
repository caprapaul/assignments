pkg load statistics;
X1 = [22.4, 24.5, 21.6, 22.4, 24.8, 21.7, 23.4, 23.3, 21.6, 20.0];
X2 = [17.7, 19.6, 12.1, 15.4, 14.0, 14.8, 19.6, 14.8, 12.6, 12.2]

n1 = length(X1);
n2 = length(X2);
confidence_level = 0.95 % 1 - alpha
alpha = 1 - confidence_level;  % significance level

s12 = var(X1);  % variance
s22 = var(X2);
sp2 = ((n1 - 1) * s12 + (n2 - 1) * s22) / (n1 + n2 - 2);
sp = sqrt(sp2);

t = tinv(1 - alpha / 2, n1 + n2 - 2);

mean_x1 = mean(X1);
mean_x2 = mean(X2);

left = mean_x1 - mean_x2 - t * sp * sqrt(1 / n1 + 1 / n2);
right = mean_x1 - mean_x2 + t * sp * sqrt(1 / n1 + 1 / n2);

fprintf("The confidence interval for the variance is (%.3f, %.3f)\n", left, right);
