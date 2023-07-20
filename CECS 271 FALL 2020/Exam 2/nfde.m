% Appropriated from Professor Tom Johnson's lecture and course textbook
% 
% Inputs:
% x = independant variable
% y = dependant variable
% 
% Outputs:
% a = coefficient vector (for polyint)
% na = exponent vector
% b = Newton's forward difference table
function [a, na, b] = nfde(x, y)

lx = length(x);
if (length(y) ~= lx)
    error("x and y should have equal lengths.")
end

b = zeros(lx, lx+1);
b(:, 1) = x(:); b(:, 2) = y(:);
for c = 3:(lx+1)
    for r = 1:(lx-(c-2))
        h = x(r+c-2) - x(r);
        b(r, c) = (b(r+1, c-1) - b(r, c-1))/h;
    end
end

c(1:lx) = b(1, 2:end);

y = 1; n = 0;
f = c(1); nf = 0;

for k = 2:lx

    y1 = [-x(k-1), 1]; n1 = [0, 1];
    [y, n] = polymult(y1, n1, y, n);
    [f, nf] = polyadd(c(k)*y, n, f, nf);

end

a = flip(f); na = flip(nf);

end

function [y, n] = polyadd(y1, n1, y2, n2)

n = min(min(n1), min(n2)):max(max(n1), max(n2));
x1 = zeros(1, length(n)); x2 = x1;
x1((n >= min(n1)) & (n <= max(n1)) == 1) = y1;
x2((n >= min(n2)) & (n <= max(n2)) == 1) = y2;
y = x1 + x2;

end

function [x,n] = polymult(x1,n1,x2,n2)

  if(length(x1)~=length(n1)) 
      fprintf('Output Error: lengths of 1st vector and its index unequal.\n'); 
      x=-eps; n=-1;
      return;
  end
  if(length(x2)~=length(n2)) 
      fprintf('Output Error: lengths of 2nd vector and its index unequal.\n'); 
      x=-eps; n=-1;
      return;
  end
  nxb = n1(1)+n2(1); nxe = n1(length(x1)) + n2(length(x2));
  n = nxb:nxe;
  x = conv(x1,x2);
end
