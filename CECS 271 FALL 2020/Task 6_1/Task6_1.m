%% Copyright

close all; format compact; clc;
fprintf("Engineer: Rodrigo Becerril Ferreyra\n");
fprintf("Company: California State University, Long Beach\n");
fprintf("Project Name: Task 6.1\n");
fprintf("Start Date: 04 November 2020\n");

%% Problem 2
fprintf("\nProblem 2\n");
clear variables;

coefs = [1 -2; 3 2]; answers = [-2; 1];
x = gauss(coefs, answers);
fprintf("(a), x = \n"); disp(x);

coefs = [4 -2 1; 2 5 2; 1 2 4]; answers = [8; 3; 11];
x = gauss(coefs, answers);
fprintf("(b), x = \n"); disp(x);

coefs = [1 1 0 1; 2 1 -1 1; 4 -1 -2 2; 3 -1 -1 2]; answers = [2; 1; 0; -3];
x = gauss(coefs, answers);
fprintf("(c), x = \n"); disp(x);

%% Problem 3
fprintf("\nProblem 3\n");
clear variables;

rank_coefs = @(S) rank([1 -1 S; -1 2 -S; S 1 1]);
rank_aug = @(S) rank([1 -1 S -2; -1 2 -S 3; S 1 1 2]);
num_arguments = 3;

fprintf("(a)  No solutions: S = 1, rank(A(S)) = %d, rank(augmented(S)) = %d, number of arguments = %d\n", rank_coefs(1), rank_aug(1), num_arguments);
fprintf("(b) Inf solutions: S = -1, rank(A(S)) = %d, rank(augmented(S)) = %d, number of arguments = %d\n", rank_coefs(-1), rank_aug(-1), num_arguments);

S = 3;
x = gauss([1 -1 S; -1 2 -S; S 1 1], [-2; 3; 2]);
fprintf("(c) Solution for S = 3:\nx = \n"); disp(x);

%% Problem 4
fprintf("\nProblem 4\n");
clear variables;

format rat;
var = 1./(1:9);
coefs = [var(1:4); var(2:5); var(3:6); var(4:7)]; answers = transpose(var(6:9));
x = gauss(coefs, answers);
fprintf("x = \n"); disp(x);
format;

%% Problem 5
fprintf("\nProblem 5\n");
clear variables;

a = [1 2 0 3; 1 0 2 2; 0 0 1 1]; x = [1000; 500; 350; 400]; b = [3500; 2700; 900];
for column = 1:4
    a(:, column) = a(:, column).*x(column);
end

answer = gauss(a, b);

fprintf("(a) Yes, there is enough food for the species because the system of linear equations\n");
fprintf("has a definite solution.\n");
fprintf("(b) No other species could be added without breaking\n");
fprintf("the system.\n");

a = a(:, 1:3);
answer2 = gauss(a, b);
final = answer2 - answer;
fprintf("(c) No more would increase.\n");
