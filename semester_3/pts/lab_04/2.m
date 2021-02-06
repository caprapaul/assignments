pkg load statistics;

p = input("p: ");
N = input("N: ");

U = rand(1, N);
X = U < p;
unique_X = unique(X);

unique_X_frequencies = histc(X, unique_X);
unique_X_probabilities = unique_values_frequencies / N;
approx_p = sum(X) / N;
approx_1_minus_p = 1 - approx_p;

n = input("n: ");
