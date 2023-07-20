% USAGE:
%     [new_n, new_out] = signalsum(n1, x1, n2, x2)
% Used to add two discrete signals together.
% Useful for signals that are offset.
function [new_n, new_out] = signalsum(n1, x1, n2, x2)

    % Create the new index vector
    n1_min = min(n1); n2_min = min(n2);
    n1_max = max(n1); n2_max = max(n2);
    highest = max(n2_max, n1_max);
    lowest = min(n2_min, n1_min);
    new_n = lowest:highest;
    
    % Fill in the output vector.
    new_out = zeros(size(new_n));
    c_out = 1; c1 = 1; c2 = 1;
    for i = new_n
        if(ismember(i, n1))
            new_out(c_out) = new_out(c_out) + x1(c1);
            c1 = c1 + 1;
        end
        if(ismember(i, n2))
            new_out(c_out) = new_out(c_out) + x2(c2);
            c2 = c2 + 1;
        end
        c_out = c_out + 1;
    end

end