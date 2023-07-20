%% Exercise 1
a = zeros(1, 5) % This creates a row vector of 5 zeros, saves it to variable a, and prints the result to the console. [0 0 0 0 0]
a = zeros(1, 5); % Same as Line 1, but supresses the printing of the result to the console. [0 0 0 0 0]
b = ones(3, 2) % Creates a 3x2 matrix of ones and saves result to variable b. b = [1 1; 1 1; 1 1]
c = size(a) % Gets the size of a and saves it into c. c = [1, 5]
abs([-5.2, 3]) % Takes the absolute value of the row vector. [5.2, 3]
floor(3.6) % Takes the floor of 3.6. [3]
d = 1 : -3.5 : -9 % Creates a row vector and saves it into d. d = [1, -2.5, -6]
e = d % Copies the value of d into e. e = [1, -2.5, -6]
f = d(2) % f is the second value of row vector d. f = -2.5
g = sin(pi/2) % Computes the sine of pi/2. g = 1
h = exp(1.0) % Computes the exponential of 1. h is approximately 2.718 (h = \lim_{t \to 0} (1 + t)^{1/t}).
K = [1.4, 2.3; 5.1, 7.8] % Defines K to be a 2x2 matrix.
m = K(1, 2) % m is the value in the first row and second column of K. m = 2.3
n = K(:, 2) % n is a column vector equal to the second column of K. n = [2.3; 7.8]
comp = 3 + 4i % comp is a complex number
real(comp) % Returns the real part of the complex number. 3
imag(comp) % Returns the imaginary part of the complex number. 4
abs(comp) % Returns the magnitude of the complex number, as given by sqrt(real(comp)^2 + imag(comp)^2). 5
angle(comp) % Returns the argument of the complex number, as given by atan2(imag(comp), real(comp)). 0.9273 
disp("haha, MATLAB is fun") % Prints "haha, MATLAB is fun" on the console.
% The following six commands print their results to the console (because printing is not suppressed by a semicolon).
3^2 % 9
4 == 4 % 1
2 == 8 % 0
3 ~= 5 % 1
x = 1 : 1 : 5 % x = [1 2 3 4 5]
y = [3 5 7 6 8] % Saves  row vector into y.
figure(); % Opens new figure window.
plot(x, y) % Plots x and y with default settings (blue, linear).
figure(); % Opens new figure window.
stem(x, y) % Plots a stem plot with the same data.
figure(); % Opens new figure window.
plot(x, y, '+r') % Plots same sata with red cross symbols instead of connecting them with lines.

%% Exercise 4
figure(); subplot(3, 1, 1);
n = -5:15; x1 = 3*delta(n, -2) + 2*delta(n, 0) - delta(n, 3) + 5*delta(n, 7);
stem(n, x1, 'filled'); title("P2.2.1", "Interpreter", "latex"); xlabel("$$n$$", "Interpreter", "latex"); ylabel("$$x_1$$", "Interpreter", "latex"); grid on;

subplot(3, 1, 2);
x3 = 10*unit(n, 0) - 5*unit(n, 5) - 10*unit(n, 10) + 5*unit(n, 15);
stem(n, x3, 'filled'); title("P2.2.3", "Interpreter", "latex"); xlabel("$$n$$", "Interpreter", "latex"); ylabel("$$x_3$$", "Interpreter", "latex"); grid on;

subplot(3, 1, 3);
n = linspace(-200, 200, 51); x5 = 5 * (cos(0.49*pi*n) + cos(0.51*pi*n));
stem(n, x5, 'filled'); title("P2.2.5: $$x_5 = \cos(0.49\pi n) + \cos(0.51 \pi n)$$", "Interpreter", "latex"); xlabel("$$n$$", "Interpreter", "latex"); ylabel("$$x_5$$", "Interpreter", "latex"); grid on;
