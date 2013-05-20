function plotellipse(q,plotoptions)

xc = q(1);
yc = q(2);
a = q(3);
b = q(4);
alpha = q(5);

t = 0:pi/200:2*pi;

xu = a*cos(t);
yv = b*sin(t);

xx = xu*cos(-alpha) - yv*sin(-alpha);
yy = xu*sin(-alpha) + yv*cos(-alpha);

x = xc + xx; 
y = yc + yy;

plot(x,y,plotoptions);