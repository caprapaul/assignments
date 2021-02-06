pkg load statistics;
X = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];

n = length(X);
confidence_level = 0.95 % 1 - alpha
alpha = 1 - confidence_level;  % significance level
sigma = 5;  % std deviation
mean_x = mean(X);
z1 = norminv(1 - alpha / 2);
z2 = norminv(alpha / 2);

left = mean_x - (sigma / sqrt(n)) * z1;
right = mean_x - (sigma / sqrt(n)) * z2;

fprintf("The confidence interval for the mean is (%.3f, %.3f)\n", left, right);
