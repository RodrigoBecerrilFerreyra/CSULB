function [a, b] = multi(x, y)
    a = mod(x + y, 1);
    b = mod(x + 2*y, 1);
end