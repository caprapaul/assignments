% 1
A = [1 0 -2; 2 1 3; 0 1 0]
B = [2 1 1; 1 0 -1; 1 1 0]

C = A - B
D = A * B
E = A .* B

% 2
x = 0 : 0.1 : 3;
y1 = x .^ 5;
y2 = x .* sin(x);
y3 = cos(x);

subplot(3, 1, 1);
p1 = plot(x, y1)

title('Line Plot')
legend('x^5/10')
ylim([-2 2])
xlabel('x')
ylabel('y')

subplot(3, 1, 2);
p2 = plot(x, y2, 'g--')

title('Line Plot')
legend('x*sin(x)')
ylim([-2 2])
xlabel('x')
ylabel('y')

subplot(3, 1, 3);
p3 = plot(x, y3, 'o..')

title('Line Plot')
legend('cos(x)')
ylim([-2 2])
xlabel('x')
ylabel('y')

waitfor(p1 && p2 && p3)