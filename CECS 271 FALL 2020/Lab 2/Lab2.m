%% Copyright

close all; format compact; clc;
fprintf("Engineer: Rodrigo Becerril Ferreyra\n");
fprintf("Company: California State University, Long Beach\n");
fprintf("Project Name: Lab 2\n");
fprintf("Date: 22 September 2020\n");

%% Problem 1
clear variables;
disp('Problem 1');
f=@(x) cos(x) - x.*exp(x);
g=@(x) cos(x)./exp(x);

tolerance=1e-4; maxits=100; %Initialize loop constraints
xinit = 2; %Initial guess
k=0; x0=xinit; %Initialize counter and point x0
x1=g(x0); %Get first iterate

while(k<maxits && abs(x0-x1)> tolerance)
    k=k+1;
    x0 = x1; xpts(k)=x0; %Save the old x values
    x1 = g(x0); ypts(k)=x1; %Save new x values (the y values)
end
root=x1; %Save answer as the root

%Display some fixed point iterationresults
disp('  Sequence of iterations:');
disp([xpts;ypts]);
disp(['  root=x1=',num2str(root),' after ',num2str(k),' iterations']);
disp(['  Check: y(x)=',num2str(root),' = ',num2str(f(root)),'(should be ~0)']);

% Plot results
x=linspace(-xinit,xinit,100); %Careful: not good if xinit=0!
figure(); hold on;
plot(x,f(x));
plot(root,f(root),'r*');
plot(xinit,f(xinit),'k*');
grid on;
str=sprintf('Fig. %d:  Root=%6.4f',1,root);
title(str); xlabel('x'); ylabel('f(x)= cos(x) - xe^x');
hold off;

%% Problem 2
clear variables;
disp('Problem 2');
f=@(x) x.^4 - x - 10;
g=@(x) (x + 10).^0.25;

tolerance=1e-4; maxits=100; %Initialize loop constraints
xinit = 4; %Initial guess
k=0; x0=xinit; %Initialize counter and point x0
x1=g(x0); %Get first iterate

while(k<maxits && abs(x0-x1)> tolerance)
    k=k+1;
    x0 = x1; xpts(k)=x0; %Save the old x values
    x1 = g(x0); ypts(k)=x1; %Save new x values (the y values)
end
root=x1; %Save answer as the root

%Display some fixed point iterationresults
disp('  Sequence of iterations:');
disp([xpts;ypts]);
disp(['  root=x1=',num2str(root),' after ',num2str(k),' iterations']);
disp(['  Check: y(x)=',num2str(root),' = ',num2str(f(root)),'(should be ~0)']);

% Plot results
x=linspace(-xinit,xinit,100); %Careful: not good if xinit=0!
figure(); hold on;
plot(x,f(x));
plot(root,f(root),'r*');
plot(xinit,f(xinit),'k*');
grid on;
str=sprintf('Fig. %d:  Root=%6.4f',2,root);
title(str); xlabel('x'); ylabel('f(x)= x^4-x-10');
hold off;

%% Problem 3
clear variables;
disp('Problem 3');
f=@(x) x - exp(-x);
g=@(x) exp(-x);

tolerance=1e-4; maxits=100; %Initialize loop constraints
xinit = 3; %Initial guess
k=0; x0=xinit; %Initialize counter and point x0
x1=g(x0); %Get first iterate

while(k<maxits && abs(x0-x1)> tolerance)
    k=k+1;
    x0 = x1; xpts(k)=x0; %Save the old x values
    x1 = g(x0); ypts(k)=x1; %Save new x values (the y values)
end
root=x1; %Save answer as the root

%Display some fixed point iterationresults
disp('  Sequence of iterations:');
disp([xpts;ypts]);
disp(['  root=x1=',num2str(root),' after ',num2str(k),' iterations']);
disp(['  Check: y(x)=',num2str(root),' = ',num2str(f(root)),'(should be ~0)']);

% Plot results
x=linspace(-xinit,xinit,100); %Careful: not good if xinit=0!
figure(); hold on;
plot(x,f(x));
plot(root,f(root),'r*');
plot(xinit,f(xinit),'k*');
grid on;
str=sprintf('Fig. %d:  Root=%6.4f',3,root);
title(str); xlabel('x'); ylabel('f(x)= x - e^{-x}');
hold off;

%% Problem 4
clear variables;
disp('Problem 4');
f=@(x) exp(x) - (x .* (x.^2 + 3.*x -3)) + (x.^3 + 4.*x.^2 + x + 2);
g=@(x) (exp(x) + x.^3 + 4.*x.^2 + x + 2)./(x.^2 + 3.*x - 3);

tolerance=1e-4; maxits=100; %Initialize loop constraints
xinit = -2; %Initial guess
k=0; x0=xinit; %Initialize counter and point x0
x1=g(x0); %Get first iterate

while(k<maxits && abs(x0-x1)> tolerance)
    k=k+1;
    x0 = x1; xpts(k)=x0; %Save the old x values
    x1 = g(x0); ypts(k)=x1; %Save new x values (the y values)
end
root=x1; %Save answer as the root

%Display some fixed point iterationresults
disp('  Sequence of iterations:');
disp([xpts;ypts]);
disp(['  root=x1=',num2str(root),' after ',num2str(k),' iterations']);
disp(['  Check: y(x)=',num2str(root),' = ',num2str(f(root)),'(should be ~0)']);

% Plot results
x=linspace(-xinit,xinit,100); %Careful: not good if xinit=0!
figure(); hold on;
plot(x,f(x));
plot(root,f(root),'r*');
plot(xinit,f(xinit),'k*');
grid on;
str=sprintf('Fig. %d:  Root=%6.4f',4,root);
title(str); xlabel('x'); ylabel('f(x)= e^x - x(x^2 +3x - 3) + (x^3 + 4x^2 + x + 2)');
hold off;

%% Problem 5
clear variables;
disp('Problem 5');
f=@(x) x - sin(x) - 0.5;
g=@(x) sin(x) + 0.5;

tolerance=1e-4; maxits=100; %Initialize loop constraints
xinit = 2; %Initial guess
k=0; x0=xinit; %Initialize counter and point x0
x1=g(x0); %Get first iterate

while(k<maxits && abs(x0-x1)> tolerance)
    k=k+1;
    x0 = x1; xpts(k)=x0; %Save the old x values
    x1 = g(x0); ypts(k)=x1; %Save new x values (the y values)
end
root=x1; %Save answer as the root

%Display some fixed point iterationresults
disp('  Sequence of iterations:');
disp([xpts;ypts]);
disp(['  root=x1=',num2str(root),' after ',num2str(k),' iterations']);
disp(['  Check: y(x)=',num2str(root),' = ',num2str(f(root)),'(should be ~0)']);

% Plot results
x=linspace(-xinit,xinit,100); %Careful: not good if xinit=0!
figure(); hold on;
plot(x,f(x));
plot(root,f(root),'r*');
plot(xinit,f(xinit),'k*');
grid on;
str=sprintf('Fig. %d:  Root=%6.4f',5,root);
title(str); xlabel('x'); ylabel('f(x)= x + sin(x) + {}^1/{}_2');
hold off;

%% Problem 6
clear variables;
disp('Problem 6');
f=@(x) exp(-x) + 3.*log(x);
g=@(x) exp(exp(-x)./3);

tolerance=1e-4; maxits=100; %Initialize loop constraints
xinit = 2; %Initial guess
k=0; x0=xinit; %Initialize counter and point x0
x1=g(x0); %Get first iterate

while(k<maxits && abs(x0-x1)> tolerance)
    k=k+1;
    x0 = x1; xpts(k)=x0; %Save the old x values
    x1 = g(x0); ypts(k)=x1; %Save new x values (the y values)
end
root=x1; %Save answer as the root

%Display some fixed point iterationresults
disp('  Sequence of iterations:');
disp([xpts;ypts]);
disp(['  root=x1=',num2str(root),' after ',num2str(k),' iterations']);
disp(['  Check: y(x)=',num2str(root),' = ',num2str(f(root)),'(should be ~0)']);

% Plot results
x=linspace(1e-6,xinit,100); %The domain of ln is (0, inf)
figure(); hold on;
plot(x,f(x));
plot(root,f(root),'r*');
plot(xinit,f(xinit),'k*');
grid on;
str=sprintf('Fig. %d:  Root=%6.4f',6,root);
title(str); xlabel('x'); ylabel('f(x)= e^{-x} + 3ln(x)');
hold off;
