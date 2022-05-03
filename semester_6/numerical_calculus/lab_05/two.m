x = [1 2];
y = [0 0.6931];
dy = [1 0.5];

X = [1.5];

[H, dH] = hermite(x, y, dy, X)
E = abs(log(X) - H)
