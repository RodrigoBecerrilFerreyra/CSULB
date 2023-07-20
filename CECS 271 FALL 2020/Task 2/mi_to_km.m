% Takes a value in miles and turns it into kilometers.
function [km] = mi_to_km(mi)

    % 1 mi * 1760 yd/mi * 36 in/yd * 2.54 cm/in * 0.1 m/cm * 0.001 km/m = 1.609344 km
    km = mi .* 1.609344;

end