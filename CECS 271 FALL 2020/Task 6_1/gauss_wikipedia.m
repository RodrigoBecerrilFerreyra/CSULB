% Returns the solution (column) vector of the system
% of equations modeled as Ax = b
% Algorithm copied from https://en.wikipedia.org/wiki/Gaussian_elimination#Pseudocode
function x = gauss(A, b)

    % set up variables
    aug = [A b];
    x = zeros(size(b));
    clear A b;
    %x = zeros(size(b));
    [m, n] = size(aug);
    h = 1; k = 1;

    while (h <= m) && (k <= n)
        % Start partial pivoting
        i_max = find(abs(aug(h:end, k)) == max(abs(aug(h:end, k))));
        if aug(i_max, k) == 0
            k = k + 1;
        else
            % swap rows
            temprow = aug(h, :);
            aug(h, :) = aug(i_max, :);
            aug(i_max, :) = temprow;

            % begin gaussian elimination
            for i = (k+1):m
                f = aug(i, k) / aug(h, k);
                aug(i, k) = 0;
                for j = (k+1):n
                    aug(i, j) = aug(i, j) - aug(h, j) * f;
                end
            end

            h = h + 1;
            k = k + 1;
        end
    end

    % substitution
    for i = 1:m
        x(end-(i-1)) = aug(i, end-i)/aug(i, end-(i-1));
    end
end
