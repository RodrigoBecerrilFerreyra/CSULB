% Computes the numerical DTFT of a signal.
%     <X> is the Discrete-Time Fourier Transform in the specified domain.
%     The domain is [0, pi].
%     <signal> is the signal to transform in the domain <indexes>. <signal>
%         should be strictly real.
%     <num_points> is the resolution of <X>.
%     <omega> is the independant variable of the function X.
%
function DTFT = numerical_dtft_2(signal, indexes, omega)

    total = 0;
    for dummy = 1:length(signal)
        total = total + (signal(dummy) * exp(-1i * omega * indexes(dummy)));
        % From definition:
        % \mathcal{F}[x[n]] = X\left(e^{j\omega}\right) = \sum_{n = -\infty}^\infty x[n] e^{-j\omega n}
    end
    DTFT = total;

end
