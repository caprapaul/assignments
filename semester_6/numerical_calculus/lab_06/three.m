x = [0 3 5 8 13];
y = [0 225 383 623 993];
dy = [75 77 80 74 72];

t = 10;

pos = spline(x, [dy(1) y dy(end)], t)
speed = spline(x, dy, t)

X = 1 : 0.1 : 13;

subplot(1, 2, 1);
hold on;
plot(X, spline(x, [dy(1) y dy(end)], X), ";Pos;");
scatter(x, y);
xlabel("time");
ylabel("pos");
hold off;

subplot(1, 2, 2);
hold on;
plot(X, spline(x, dy, X), ";Speed;");
scatter(x, dy);
xlabel("time");
ylabel("speed");
hold off;
