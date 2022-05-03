x = [0 3 5 8 13];
f = [0 225 383 623 993];
df = [75 77 80 74 72];

X = 1 : 0.1 : 13;

[H, dH] = hermite(x, f, df, X);

clf;

subplot(1, 3, 1);
plot(X, H, ";Pos;");
xlabel("time");
ylabel("pos");

subplot(1, 3, 2);
plot(X, dH, ";Speed;");
xlabel("time");
ylabel("speed");

subplot(1, 3, 3);
plot(H, dH, ";Speed;");
xlabel("pos");
ylabel("speed");

