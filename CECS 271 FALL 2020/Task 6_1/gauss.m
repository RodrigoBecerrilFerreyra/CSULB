% Returns the solution (column) vector of the system
% of equations modeled as Ax = b
% In other words, x = A \ b;
% By Rodrigo Becerril Ferreyra
function x = gauss(A, b)

    aug = [A b];
    [n, m] = size(aug);
    x = zeros(size(b));

    % Check for unique solutions
    rank_A = rank(A);
    rank_aug = rank(aug);
    if(rank_A ~= rank_aug) || (rank_A ~= n)
        warning("NO UNIQUE SOLUTIONS");
        return;
    end

    for col = 1:n-1
        % if the largest value is not on the main diagonal,
        % switch it with the row that does
        index_of_largest_abs_value = (col-1) + find(abs(aug(col:end, col)) == max(abs(aug(col:end, col))));
        if index_of_largest_abs_value ~= col
            temprow = aug(col, :);
            aug(col, :) = aug(index_of_largest_abs_value, :);
            aug(index_of_largest_abs_value, :) = temprow;
        end

        %disp(aug);

        % begin gaussian elimination for one column
        pivot = aug(col, col);
        for row = (col+1):n
            value = aug(row, col);
            aug(row, :) = aug(row, :) - (value/pivot)*aug(col, :);
        end
        %disp(aug);
    end

    % back substitution
    x(n) = aug(n, m) / aug(n, n);
    for i = (n-1):-1:1
        total = 0;
        for j = n:-1:1
            total = total + aug(i, j)*x(j);
        end
        x(i) = (aug(i, m) - total)/aug(i, i);
    end
end
