% USAGE:
%     sample = delta(indexes, n0)
% Returns a vector sample the same size as indexes such that
% sample(n) = 1 if indexes(n) == n0
% sample(n) = 0 otherwise
function sample = delta(indexes, n0)

    sample = (indexes == n0);

end
