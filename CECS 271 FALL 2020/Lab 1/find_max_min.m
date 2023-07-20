% Returns a vector like this: [0, 1, 0, 0, 0, -1, 0]
function [output] = find_max_min(in_vec)

    max_val = max(abs(in_vec)); min_val = min(abs(in_vec));

    output = zeros(1, length(in_vec));

    for i = 1 : length(in_vec)
        if abs(in_vec(i)) == max_val
            output(i) = 1;
        elseif abs(in_vec(i)) == min_val
            output(i) = -1;
        end
    end

    % Just in case two items have the same magnitude
    % https://math.aalto.fi/opetus/Mattie/Blogi/Matlab/html/countoccurrences.html
    [a, b] = histc(output, unique(output));
    y = a(b);
    while length(y(output==1)) > 1
        temp_vec = output(output == 1);
        output(temp_vec(1)) = 0;
    end
    while length(y(output==-1)) > 1
        temp_vec = output(output == -1);
        output(temp_vec(1)) = 0;
    end

end