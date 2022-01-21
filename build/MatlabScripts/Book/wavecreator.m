clc
clear all
close all

time = 2+8+4+8*2+4+8+2;

Amax = pi/10;

wave = [];

t = [];

taux = 0:.1:2;
wave = [wave  taux*0];
t = [t taux];

taux = 0:.1:8;
wave = [wave  Amax * sin(2*pi*1/8*taux)];
t = [t taux+t(end)];

taux = 0:.1:4;
wave = [wave  taux*0];
t = [t taux+t(end)];

taux = 0:.1:16;
wave = [wave  Amax * sin(2*pi*1/8*taux)];
t = [t taux+t(end)];

taux = 0:.1:4;
wave = [wave  taux*0];
t = [t taux+t(end)];

taux = 0:.1:8;
wave = [wave  Amax * sin(2*pi*1/8*taux)];
t = [t taux+t(end)];

taux = 0:.1:2;
wave = [wave  taux*0];
t = [t taux+t(end)];
ax = axes();
ax.Position = [.1 .1 .8 .3];
plot(t,wave,'LineWidth',2)
grid minor
grid on
xlabel('Time [ s ]')
ylabel('Degrees [ rads ]')
xlim([0 t(end)])
ylim([Amax*-1.1 Amax*1.1])

