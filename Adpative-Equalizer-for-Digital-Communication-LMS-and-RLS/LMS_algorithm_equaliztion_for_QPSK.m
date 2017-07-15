%% Adaptive Equalization for Digital Communications - Least Mean Square algorithm
% Two-ray multipath channel 

%% Reset MATLAB
clear;
clc;

%% Parameter setting
tx_leng = 128;        % Transmission length
M = 5;                % Half length of response -M ~ M ( length = 2*M+1 )
ch_leng = M*2 + 1;    % Channel response length 
p2_abs = 0.5;         % Path 2 channel response amplitude
p2_phase = (7*pi)/8;  % Paht 2 channel response phase
beta = 0.35;          % For TDMA digital cellular standard
w_length = 12;        % Filter length

%% Initialization of varible
tx = zeros(1,tx_leng);            % Transmitted symbols
ch = zeros(1,ch_leng);            % Channel response
tx_hat = zeros(1,tx_leng);        % Estimation of transmitted symbols
error = 0;                        % LMS algorithm error
w = zeros(w_length,1);            % Filter
miu = 10^(-1);                       % LMS algorithm learning rate

%% Transmitted symbols 
for t = 1:tx_leng                 
	tx(1,t) = sgn(-2*rand+1) + j*sgn(-2*rand+1);  % Random generationn
end

%% Channel response 
for t = 1:ch_leng                 % Channel is assumed to have raised cosine spectrum
    ch(1,t) = p2_abs*exp(j*p2_phase)*(sin(pi*(t-(M+1)-0.5))/(pi*(t-(M+1)-0.5)))*(cos(beta*pi*(t-(M+1)-0.5))/(1-4*(beta^2)*(t-(M+1)-0.5)^2));
end
ch(1,M+1) = ch(1,M+1) + 1;        % Impulse response 

%% Received signals 
rx = [conv(tx,ch),0];             % Received symbols ( Time domain )

%% Least mean square algorithm
for t = 1:tx_leng
	rx_tmp = zeros(w_length,1);
	for k = 1:w_length
		rx_tmp(k) = rx(w_length-k+t);
    end
	tx_hat(1,t) = w'*rx_tmp;
	error = tx(1,t) - tx_hat(1,t);  
	w = w + miu*conj(error)*rx_tmp;  % Update the filter weigths
end

%% Plot diagram
figure(1);

scatter(real(tx),imag(tx),200,'g','filled'); % Transmitted symbols
hold on;

scatter(real(rx),imag(rx),20,'r');           % Received symbols
hold on;

scatter(real(tx_hat),imag(tx_hat),20,'b');   % LMS estimation
hold on;

axis([-2,2,-2,2]);                           
title('LMS algorithm equalization for QPSK');
xlabel('Real');
ylabel('Imaginary');



