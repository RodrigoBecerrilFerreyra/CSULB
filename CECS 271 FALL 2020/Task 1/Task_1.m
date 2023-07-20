%% Copyright

close all; format compact; clc;
fprintf("Engineer: Rodrigo Becerril Ferreyra\n");
fprintf("Company: California State University, Long Beach\n");
fprintf("Project Name: Task 1\n");
fprintf("Start Date: 30 August 2020\n");
fprintf("End date: 30 August 2020\n");

%% Task 1.1
fprintf("\nTask 1.1\n");
clear variables;

y = polyval([1, 3, 1], 1.3);
fprintf("(1.3)^2 + 3(1.3) + 1   = %6.3f.\n", y);

y = sin(30 * pi/180);
fprintf("sin(30 deg)            = %6.3f.\n", y);

y = atan(1);
fprintf("arctan(1)              = %6.3f.\n", y);

y = sin(acos(sqrt(3)/2));
fprintf("sin(arccos(sqrt(3)/2)) = %6.3f.\n", y);

%% Task 1.2
fprintf("\nTask 1.2\n");
clear variables;

x = [pi/3, pi/6];
y = abs(x).*sin(x.^2);
fprintf("x              = {"); fprintf("%6.3f ", x); fprintf("}\n");
fprintf("abs(x)sin(x^2) = {"); fprintf("%6.3f ", y); fprintf("}\n");

%% Task 1.3
fprintf("\nTask 1.3\n");
clear variables;

fprintf("sin(pi/2)   = %6.3f.\n", sin(pi/2));
fprintf("cos(pi/3)   = %6.3f.\n", cos(pi/3));
fprintf("tan(60 deg) = %6.3f.\n", tan(60 * pi/180));
fprintf("\n");

x = [1/2, 1];
y = log(x + sqrt(x.^2 + 1));
fprintf("x                     = {"); fprintf("%6.3f ", x); fprintf("}\n");
fprintf("ln(x + sqrt(x^2 + 1)) = {"); fprintf("%6.3f ", y); fprintf("}\n");
fprintf("\n");

x = [pi/4, pi/2];
y = x./((x.^2 + 1).*sin(x));
fprintf("x                   = {"); fprintf("%6.3f ", x); fprintf("}\n");
fprintf("x/((x^2 + 1)sin(x)) = {"); fprintf("%6.3f ", y); fprintf("}\n");

%% Task 1.4
fprintf("\nTask 1.4\n");
clear variables;

x = [0.3, 1/3, 0.5, 1/2, 1.65, -1.34];
fprintf("x        = {"); fprintf("%6.3f ", x); fprintf("}\n");
fprintf("round(x) = {"); fprintf("%6.3f ", round(x)); fprintf("}\n");
fprintf("ceil(x)  = {"); fprintf("%6.3f ", ceil(x)); fprintf("}\n");
fprintf("floor(x) = {"); fprintf("%6.3f ", floor(x)); fprintf("}\n");
fprintf("fix(x)   = {"); fprintf("%6.3f ", fix(x)); fprintf("}\n");

%% Task 1.5
fprintf("\nTask 1.5\n");
clear variables;

x = [3, 4, 5];
y = [3, 4, -4, 6];

for yval = 1:1:4
    for xval = 1:1:3
        a = x(xval); b = y(yval);
        fprintf("%2d rem %2d = %2d\t%2d mod %2d = %2d\n",...
        a, b, rem(a, b), a, b, mod(a, b));
    end
end

%% Task 1.6
fprintf("\nTask 1.6\n");
clear variables;

x = 1 : 0.1 : 2;
fprintf("x                         = {"); fprintf("%6.3f ", x); fprintf("}\n");

y = polyval([1, 3, 0, 1], x);
fprintf("x^3 + 3x^2 + 1            = {"); fprintf("%6.3f ", y); fprintf("}\n");

y = sin(x.^2);
fprintf("sin(x^2)                  = {"); fprintf("%6.3f ", y); fprintf("}\n");

y = (sin(x)).^2;
fprintf("sin^2(x)                  = {"); fprintf("%6.3f ", y); fprintf("}\n");

y = sin(2.*x) + x.*cos(4.*x);
fprintf("sin(2x) + xcos(4x)        = {"); fprintf("%6.3f ", y); fprintf("}\n");

y = x./(x.^2 + 1);
fprintf("x/(x^2 + 1)               = {"); fprintf("%6.3f ", y); fprintf("}\n");

y = cos(x)./(1 + sin(x));
fprintf("cos(x)/(1 + sin(x))       = {"); fprintf("%6.3f ", y); fprintf("}\n");

y = 1./x + x.^3./(x.^4 + 5.*sin(x));
fprintf("1/x + x^3/(x^4 + 5sin(x)) = {"); fprintf("%6.3f ", y); fprintf("}\n");

%% Task 1.7
fprintf("\nTask 1.7\n");
clear variables;

x = 3 : 0.01 : 5;
y = x./(x + (1./x.^2));
fprintf("x             = {"); fprintf("%7.5f ", x); fprintf("}\n");
fprintf("x/(x + x^-2)) = {"); fprintf("%7.5f ", y); fprintf("}\n");

%% Task 1.8
fprintf("\nTask 1.8\n");
clear variables;

x = -2 : 0.1 : -1;
y = 1./x.^3 + 1./x.^2 + 3./x;
fprintf("x                 = {"); fprintf("%6.3f ", x); fprintf("}\n");
fprintf("x^-3 + x^-2 + 3/x = {"); fprintf("%6.3f ", y); fprintf("}\n");

%% Task 1.9
fprintf("\nTask 1.9\n");
clear variables;

x = linspace(0, 1, 200);
g = x.^3 + 1;
h = x + 2;
z = x.^2;
y = cos(pi.*x);
f = (y.*z)./(g.*h);

fprintf("f(200) = %6.3f\n", f(x==1));

%% Task 1.10
fprintf("\nTask 1.10\n");
clear variables;

x = linspace(-2, 2, 20);
y = polyval([1, 0, 0, 0, -1], x);
plot(x, y);

%% Task 1.11
fprintf("\nTask 1.11\n");
clear variables;

x = 0 : 0.1 : 3;
f = x.^3 .* cos(x + 1);
fprintf("f(2) = %6.3f\n", f(x==2));
fprintf("f(3) = %6.3f\n", f(x==3));
