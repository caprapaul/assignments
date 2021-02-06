pkg load statistics;

X = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];
sigma = 5;
m = 9;
alpha = 0.05;
% left-tailed test when sigma is known
[h, p, ci, zval] = ztest(X, m, sigma, "alpha", alpha, "tail", "left");
printf("The value of TS0 is %d\n", zval);
printf("The P-value is %d\n", p);
% left-tailed test quantile
tta = norminv(alpha);

printf('The rejection region is (%d, %d).\n', -Inf, tta)
printf('The value of h is %d.\n', h)

if h == 1
    printf('The null hypothesis IS rejected.\n') 
    printf('The data suggests that the standard IS NOT met.\n')
else
    printf('The null hypothesis IS NOT rejected.\n')
    printf('The data suggests that the standard IS met.\n')
end   
