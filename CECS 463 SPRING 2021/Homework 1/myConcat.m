function output = myConcat(input)

    % checking number of columns
    [~, shouldbeone] = size(input);
    if shouldbeone ~= 1
        output = -1;
        warning("This function works only for column vectors"); % can't use error() because that doesn't output -1
        return % kicks back to call if reached
    end

    output = [input; input];
end
