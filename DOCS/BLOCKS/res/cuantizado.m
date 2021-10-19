clc
clear all
close all

F1 = 200;
F2 = 60;

F = 2;
Tf = 0.5;

T1 = linspace(0,Tf,F1*Tf);
T2 = linspace(0,Tf,F2*Tf);

T1 = reshape([T1;T1],1,length(T1)*2);
T2 = reshape([T2;T2],1,length(T2)*2);


A1 = sin(2*pi*F*T1);
A2 = sin(2*pi*F*T2);

A1 = [A1(1) A1];
T1 = [T1 T1(end)];

A2 = [A2(1) A2];
T2 = [T2 T2(end)];

H1 = figure(1)

hold on
plot(T1,A1)
plot(T2,A2)

text(0.3,0.4,"$Y = sin(2*\pi*(2Hz)*t)$","interpreter","latex")

grid minor

legend("Fs : 200Hz","Fs : 60Hz");

title("Cuantizacion de una señal seno a frecuencias de 200 y 60 Hz")
ylabel("Amplitud [ U ]")
xlabel("Tiempo [ s ]")

set(gcf,"color",[ 1 1 1])
