%% 3.1
domain = linspace(-pi, pi, 1001);

n = -10:10; signal = 0.6.^(abs(n));
X = numerical_dtft_2(signal, n, domain);
figure();
subplot(2, 1, 1); plot(domain, abs(X));
title("Magnitude of $$X$$", "interpreter", "latex");
xticks(-pi : pi/4 : pi);
xticklabels(["-\pi", "-3\pi/4", "-\pi/2", "-\pi/4", "0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
axis tight
subplot(2, 1, 2); plot(domain, angle(X));
title("Argument of $$X$$", "interpreter", "latex");
xticks(-pi : pi/4 : pi);
xticklabels(["-\pi", "-3\pi/4", "-\pi/2", "-\pi/4", "0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
axis tight

n = 0:50; signal = cos(0.5*pi*n) + 1i*sin(0.5*pi*n);
X = numerical_dtft_2(signal, n, domain);
figure();
subplot(2, 1, 1); plot(domain, abs(X));
title("Magnitude of $$X$$", "interpreter", "latex");
xticks(-pi : pi/4 : pi);
xticklabels(["-\pi", "-3\pi/4", "-\pi/2", "-\pi/4", "0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
axis tight
subplot(2, 1, 2); plot(domain, angle(X));
title("Argument of $$X$$", "interpreter", "latex");
xticks(-pi : pi/4 : pi);
xticklabels(["-\pi", "-3\pi/4", "-\pi/2", "-\pi/4", "0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
axis tight

%% 3.3
domain = linspace(0, pi, 1001);

n = -10:10;
signal = 0.6.^abs(n);
X_numeric = numerical_dtft_2(signal, n, domain);

X_formula = 0;
for dummy = n
    X_formula = X_formula + 0.6^abs(dummy) * exp(-1i*domain*dummy);
end

figure();
subplot(2, 2, 1); plot(domain, abs(X_numeric)); title("Magnitude (Numerical)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 2); plot(domain, abs(X_formula)); title("Magnitude (Formula)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 3); plot(domain, angle(X_numeric)); title("Argument (Numerical)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 4); plot(domain, angle(X_formula)); title("Argument (Formula)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);

n = 0:12;
signal = 4 .* (-0.7).^n .* cos(0.25 * pi .* n);
X_numeric = numerical_dtft_2(signal, n, domain);
X_formula = 2./(1 + 0.7.*exp(1i * 0.25 * pi).*exp(-1i * domain)) + 2./(1 + 0.7.*exp(-1i * 0.25 * pi).*exp(-1i * domain));

figure();
subplot(2, 2, 1); plot(domain, abs(X_numeric)); title("Magnitude (Numerical)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 2); plot(domain, abs(X_formula)); title("Magnitude (Formula)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 3); plot(domain, angle(X_numeric)); title("Argument (Numerical)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 4); plot(domain, angle(X_formula)); title("Argument (Formula)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);

%% 3.4
M = [10 25 50 101];
domain = linspace(-pi, pi, 1001);

% Plotting all the DTFTs for four rectangular windows
for m = M

    n = 0:(m-1);
    signal = ones(size(n));
    X = numerical_dtft_2(signal, n, domain);
    figure();
    subplot(3, 1, 1); stem(n, signal, 'filled');
    title(sprintf("Rectangular Window Function ($$M = %d$$)", m), "interpreter", "latex");
    axis tight

    subplot(3, 1, 2); plot(domain/pi, abs(X));
    title(sprintf("Magnitude of DTFT of Rectangular Window Function ($$M = %d$$)", m), "interpreter", "latex");
    xlabel("Frequency in $$\pi$$ units", "interpreter", "latex");
    axis tight

    subplot(3, 1, 3); plot(domain/pi, angle(X));
    title(sprintf("Magnitude of DTFT of Rectangular Window Function ($$M = %d$$)", m), "interpreter", "latex");
    xlabel("Frequency in $$\pi$$ units", "interpreter", "latex");
    axis tight

end

% Plotting all DTFTs for four Hamming windows
for m = M

    n = 0:(m-1);
    signal = 0.54 - 0.46.*cos((2*pi*n)./(m - 1));
    X = numerical_dtft_2(signal, n, domain);
    figure();

    subplot(3, 1, 1); stem(n, signal, 'filled');
    title(sprintf("Hamming Window Function ($$M = %d$$)", m), "interpreter", "latex");
    axis tight

    subplot(3, 1, 2); plot(domain/pi, abs(X));
    title(sprintf("Magnitude of DTFT of Hamming Window Function ($$M = %d$$)", m), "interpreter", "latex");
    xlabel("Frequency in $$\pi$$ units", "interpreter", "latex");
    axis tight

    subplot(3, 1, 3); plot(domain/pi, angle(X));
    title(sprintf("Magnitude of DTFT of Hamming Window Function ($$M = %d$$)", m), "interpreter", "latex");
    xlabel("Frequency in $$\pi$$ units", "interpreter", "latex");
    axis tight

end

%% 3.5
domain = linspace(0, pi, 1001);
X_given = 3 + 2.*cos(domain) + 4.*cos(2.*domain);
signal = [2 1 3 1 2]; n = -2:2;
X_calculated = numerical_dtft_2(signal, n, domain);

figure();
subplot(2, 2, 1); plot(domain, abs(X_calculated)); title("Magnitude (From Signal)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 2); plot(domain, abs(X_given)); title("Magnitude (Given)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 3); plot(domain, angle(X_calculated)); title("Argument (From Signal)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 4); plot(domain, angle(X_given)); title("Argument (Given)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);


X_given = (1 - 6*cos(3.*domain) + 8*cos(5.*domain)).*exp(-3i * domain);
signal = [4 0 -1 0 0 1 0 0 -3 0 4]; n = -2:8;
X_calculated = numerical_dtft_2(signal, n, domain);

figure();
subplot(2, 2, 1); plot(domain, abs(X_calculated)); title("Magnitude (From Signal)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 2); plot(domain, abs(X_given)); title("Magnitude (Given)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 3); plot(domain, angle(X_calculated)); title("Argument (From Signal)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 4); plot(domain, angle(X_given)); title("Argument (Given)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);

X_given = (1 + 2*cos(domain) + 3*cos(2.*domain)).*cos(domain./2).*exp((-5/2).*domain.*1i);
signal = [3/4 5/4 1 1 5/4 3/4]; n = 0:5;
X_calculated = numerical_dtft_2(signal, n, domain);

figure();
subplot(2, 2, 1); plot(domain, abs(X_calculated)); title("Magnitude (From Signal)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 2); plot(domain, abs(X_given)); title("Magnitude (Given)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 3); plot(domain, angle(X_calculated)); title("Argument (From Signal)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(2, 2, 4); plot(domain, angle(X_given)); title("Argument (Given)"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);

%% 3.11
domain = linspace(0, pi, 1001);

H = 0.19./(1.81-1.8.*cos(domain));
figure();
subplot(1, 2, 1); plot(domain, abs(H)); title("Magnitude"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(1, 2, 2); plot(domain, angle(H)); title("Argument"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);

H = 2./(1 - 0.5.*exp(1i.*(0.1*pi - domain))) + 2./(1 - 0.5.*exp(1i.*(-0.1*pi - domain))) - 1;
figure();
subplot(1, 2, 1); plot(domain, abs(H)); title("Magnitude"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
subplot(1, 2, 2); plot(domain, angle(H)); title("Argument"); grid on
xticks(0:pi/4:pi); xticklabels(["0", "\pi/4", "\pi/2", "3\pi/4", "\pi"]);
