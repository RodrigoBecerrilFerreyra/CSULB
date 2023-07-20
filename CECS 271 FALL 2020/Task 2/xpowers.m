function [s, c, s2pc2] = xpowers(x)
    s = sin(x); c = cos(x);
    s2pc2 = (sin(x)).^2 + (cos(x)).^2;
end