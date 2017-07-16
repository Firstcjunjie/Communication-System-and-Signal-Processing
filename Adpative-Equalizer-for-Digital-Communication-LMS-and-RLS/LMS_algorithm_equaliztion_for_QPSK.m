% Adaptive Equalization for Digital Communications - Least Mean Square filter
% Two-ray multipath channel 

% Reset MATLAB variables 
clear;
clc;

% Parameter setting 
d_leng = 128;            % Length of sequence of transmitted symbols
M1 = 5;               
M2 = 5;               
q_leng = M1 + M2 + 1;    % Length of the multipath distorted pulse symbol waveform
g2_abs = 0.5;            % Path 2 channel response amplitude
g2_phase = (7*pi)/8;     % Paht 2 channel response phase
beta = 0.35;             % For TDMA digital cellular standard
w_length = 12;           % Length of filter taps 

% Initialization of varible 
d = zeros(1,d_leng);              % Sequence of transmitted symbols
q = zeros(1,q_leng);              % Multipath distorted pulse symbol waveform
d_hat = zeros(1,d_leng);          % Estimation of transmitted symbols
e = 0;                            % LMS filter error
w = zeros(w_length,1);            % Filter taps
miu = 10^(-1);                    % LMS algorithm learning rate

% Sequence of transmitted symbols
for n = 1:d_leng                 
	d(1,n) = sgn(-2*rand+1) + j*sgn(-2*rand+1);  % Random generationn
end

% Multipath distorted pulse symbol waveform 
for n = 1:q_leng                  % Waveform  is assumed to have raised cosine spectrum
    q(1,n) = g2_abs*exp(j*g2_phase)*(sin(pi*(n-(M1+1)-0.5))/(pi*(n-(M1+1)-0.5)))*(cos(beta*pi*(n-(M1+1)-0.5))/(1-4*(beta^2)*(n-(M1+1)-0.5)^2));
end
q(1,M1+1) = q(1,M1+1) + 1;        % Impulse response 

% Sequence of received symbols
u = [conv(d,q),0];                % Sequence of received symbols

% Least mean square algorithm 
for n = 1:d_leng
	u_tmp = zeros(w_length,1);
	for k = 1:w_length
		u_tmp(k) = u(w_length-k+n);
    end
	d_hat(1,n) = w'*u_tmp;
	e = d(1,n) - d_hat(1,n);  
	w = w + miu*conj(e)*u_tmp;  % Update the filter weigths
end

% Plot diagram 
figure(1);

scatter(real(d),imag(d),200,'g','filled'); % Transmitted symbols
hold on;

scatter(real(u),imag(u),20,'r');           % Received symbols
hold on;

scatter(real(d_hat),imag(d_hat),20,'b');   % LMS estimation
hold on;

axis([-2,2,-2,2]);                        
legend('Transmitted symbols','Received symbols','LMS estimation')
title('LMS filter equalization for QPSK');
xlabel('Real');
ylabel('Imaginary');

