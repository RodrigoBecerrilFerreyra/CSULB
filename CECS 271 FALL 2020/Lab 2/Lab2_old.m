%% Problem 1

f = @(x) cos(x) - x .* exp(x);
g = @(x) cos(x)/exp(x);
x = 2; tol = f(x); maxiters = 100;

while(abs(tol) >= 1e-4 && maxiters > 0)

    x = g(x);
    tol = f(x);
    maxiters = maxiters - 1;

end

fprintf("Final value of x (zero of f): %f\n", x);
fprintf("Final value of f(x): %f\n", tol);
fprintf("Total iterations: %d\n", 100-maxiters);

%% Problem 2
f = @(x) x^4 - x - 10;
g = @(x) (x+10)^0.25;
x = 4; tol = f(x); maxiters = 100;

while(abs(tol) >= 1e-4 && maxiters > 0)

    x = g(x);
    tol = f(x);
    maxiters = maxiters - 1;

end

fprintf("Final value of x (zero of f): %f\n", x);
fprintf("Final value of f(x): %f\n", tol);
fprintf("Total iterations: %d\n", 100-maxiters);
