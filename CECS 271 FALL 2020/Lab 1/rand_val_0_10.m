% Gives a matrix with random values in the interval [0, 10].
% Params: m, n -> m x n matrix
function [rand_vars] = rand_val_0_10(m, n)

    rand_vars = zeros(m, n);
    for i = 1 : m * n
        rand_vars(i) = round((rand() * 11) - 0.5);
    end
end