figure(); hold on;

blueline = plot([0, 1e6], [193/2000, 4761/4000], 'b-'); %line through two test points
plot([0, 2582400/7], [0.5, 0.5], 'g--'); %y = 0.5
plot([2582400/7, 2582400/7], [0, 0.5], 'g--'); %x = 2582400/7
plot(2582400/7, 0.5, 'k.', 'MarkerSize', 15); %Intersection
plot([80000, 560000], [0.184, 0.709], 'r.', 'MarkerSize', 15); %two test points

axis([0, 1e6, 0, 1]);
legend(blueline, "y = (7/6.4E6)x + 193/2000", 'Location', 'southeast');
%legend(blueline, "$y = \frac{7}{6.4\times 10^6}x + \frac{193}{2000}$", 'Location', 'southeast');
xlabel("List size"); ylabel("Probability"); title("Line Between Two Test Points");
grid on;
hold off;