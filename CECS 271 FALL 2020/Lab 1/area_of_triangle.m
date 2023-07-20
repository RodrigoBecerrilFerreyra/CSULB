function [area_] = area_of_triangle(outline)

    first_ = outline(find_max_min(outline) == 1);
    second_ = outline(find_max_min(outline) == -1);
    area_ = 0.5 * (real(first_)*imag(second_) - imag(first_)*real(second_));

end