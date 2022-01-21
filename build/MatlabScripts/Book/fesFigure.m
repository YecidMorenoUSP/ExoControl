clc
clear all
close all

A = 10:5:120;
t = 1:length(A);


A = reshape([A;A],1,length(A)*2);
t = reshape([t;t],1,length(t)*2);

t = [0 t(1:end-1)];

figure
plot(t,A)
axis square
grid minor
grid on
xlim([5,10])

figure
plot(t,A)
xlabel('Time [ s ]')
ylabel('Current [ mA ]')
grid minor
grid