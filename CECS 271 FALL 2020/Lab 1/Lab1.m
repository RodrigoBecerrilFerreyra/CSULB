%% Copyright

close all; format compact; clc;
fprintf("Engineer: Rodrigo Becerril Ferreyra\n");
fprintf("Company: California State University, Long Beach\n");
fprintf("Project Name: Task 2\n");
fprintf("Start Date: 08 September 2020\n");

%% Quadrilateral Building

clear variables;
z = [rand_val_0_10(1, 1) + 1j*rand_val_0_10(1, 1), -rand_val_0_10(1, 1) + 1j*rand_val_0_10(1, 1),...
    -rand_val_0_10(1, 1) - 1j*rand_val_0_10(1, 1),  rand_val_0_10(1, 1) - 1j*rand_val_0_10(1, 1)];
outline = [z(2) - z(1), z(3) - z(2), z(4) - z(3), z(1) - z(4)];

%% Plotting Using my_arrow

figure(); hold on;
arrow1 = my_arrow([0, 0], [real(z(1)), imag(z(1))], 'Color', 'b');
my_arrow([0, 0], [real(z(2)), imag(z(2))], 'Color', 'b');
my_arrow([0, 0], [real(z(3)), imag(z(3))], 'Color', 'b');
my_arrow([0, 0], [real(z(4)), imag(z(4))], 'Color', 'b');
arrow2 = my_arrow([real(z(1)), imag(z(1))], [real(z(2)), imag(z(2))], 'Color', 'r');
my_arrow([real(z(2)), imag(z(2))], [real(z(3)), imag(z(3))], 'Color', 'r');
my_arrow([real(z(3)), imag(z(3))], [real(z(4)), imag(z(4))], 'Color', 'r');
my_arrow([real(z(4)), imag(z(4))], [real(z(1)), imag(z(1))], 'Color', 'r');

set(get(gca, 'XLabel'), 'String', "Real Axis");
set(get(gca, 'YLabel'), 'String', "Imaginary Axis");
set(get(gca, 'Title'), 'String', "Quadrilateral");
legend([arrow1, arrow2], ["Random vectors", "Outline"]);
axis([-10, 10, -10, 10]); grid on;

%% Math

crossproducts =...
 [real(outline(4))*imag(outline(1)) - real(outline(1))*imag(outline(4)),... %(z1 - z4) x (z2 - z1)
  real(outline(1))*imag(outline(2)) - real(outline(2))*imag(outline(1)),... %(z2 - z1) x (z3 - z2)
  real(outline(2))*imag(outline(3)) - real(outline(3))*imag(outline(2)),... %(z3 - z2) x (z4 - z3)
  real(outline(3))*imag(outline(4)) - real(outline(4))*imag(outline(3))];   %(z4 - z3) x (z1 - z4)

fprintf("The quadrilateral is "); triangle_flag = 0;
for i = 1:4
    if crossproducts(i) == 0 % triangle case
        outline = nonzeros(outline)';
        area_ = area_of_triangle(outline);
        fprintf("actually a triangle ");
        triangle_flag = 1;
    else
        if crossproducts(i) < 0
            fprintf("concave ");
            break;
        else
            if i == 4
                fprintf("convex ");
            end
        end
    end
end
if triangle_flag ~= 1
    [~, index1] = max(crossproducts);
    [~, index2] = min(crossproducts);
    diagonal = z(index1) - z(index2);
    if index1 == 2 || index1 == 4
        area_ = area_of_triangle([outline(1), outline(4), diagonal]) + ...
        area_of_triangle([outline(2), outline(3), diagonal]);
    else
        area_ = area_of_triangle([outline(1), outline(2), diagonal]) + ...
        area_of_triangle([outline(3), outline(4), diagonal]);
    end
end

fprintf("whose area is %f.\n", area_);
