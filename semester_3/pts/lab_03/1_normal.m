pkg load statistics;

mu = input("mu: ");
sigma = input("sigma: ");
alpha = input("alpha: ");
beta = input("beta: ");

# a)
# P(x <= a) = cdf(a)
a1 = normcdf(0, mu, sigma)

# P(x >= a) = 1 - P(x < a) = 1 - (cdf(a) - pdf(a))
a2 = 1 - (normcdf(0, mu, sigma) - normpdf(0, mu, sigma))


# b)
# P(a <= X <= b) = P(x <= b) - P(x < a) = cdf(b) - (cdf(a) - pdf(a))
b1 = normcdf(1, mu, sigma) - (normcdf(-1, mu, sigma) - normpdf(-1, mu, sigma))

# P(X <= a or X >= b) = P(X <= a) + P(X >= b) = cdf(a) + (1 - (cdf(b) - pdf(b)))
b2 = normcdf(-1, mu, sigma) + (1 - (normcdf(1, mu, sigma) - normpdf(1, mu, sigma)))


# c)
c = norminv(alpha, mu, sigma)


# d)
d = norminv(1 - beta, mu, sigma)
