%--带通滤波器--%
clc;
fs=20000;
Wp1=2*pi*4000;  Wp2=2*pi*6000;
Ws1=2*pi*3000;  Ws2=2*pi*7500;
Rp=1;
Rs=40;
%--切比雪夫I型--%
[n1,wn1]=cheb1ord([Wp1,Wp2],[Ws1,Ws2],Rp,Rs,'s');
[b1,a1]=cheby1(n1,Rp,wn1,'s');
[B1,A1]=bilinear(b1,a1,fs);
[H1,w1]=freqz(B1,A1);
h1=grpdelay(B1,A1,512);
%--切比雪夫II型--%
[n2,wn2]=cheb2ord([Wp1,Wp2],[Ws1,Ws2],Rp,Rs,'s');
[b2,a2]=cheby2(n2,Rs,wn2,'s');
[B2,A2]=bilinear(b2,a2,fs);
[H2,w2]=freqz(B2,A2);
h2=grpdelay(B2,A2,512);
%--椭圆型--%
[n3,wn3]=ellipord([Wp1,Wp2],[Ws1,Ws2],Rp,Rs,'s');
[b3,a3]=ellip(n3,Rp,Rs,wn3,'s');
[B3,A3]=bilinear(b3,a3,fs);
[H3,w3]=freqz(B3,A3);
h3=grpdelay(B3,A3,512);
%--画图--%
figure(1);
subplot(311);  plot(w1/pi,abs(H1));  title('切比雪夫I幅频');
subplot(312);  plot(w2/pi,abs(H2));  title('切比雪夫II幅频');
subplot(313);  plot(w3/pi,abs(H3));  title('椭圆型幅频');
figure(2);
subplot(311);  plot(w1/pi,angle(H1));  title('切比雪夫I相频');
subplot(312);  plot(w2/pi,angle(H2));  title('切比雪夫II相频');
subplot(313);  plot(w3/pi,angle(H3));  title('椭圆型相频');
figure(3);
subplot(311);  plot(w1/pi,20*log10(abs(H1)));  title('切比雪夫I对数幅频');
subplot(312);  plot(w2/pi,20*log10(abs(H2)));  title('切比雪夫II对数幅频');
subplot(313);  plot(w3/pi,20*log10(abs(H3)));  title('椭圆型对数幅频');
figure(4);
subplot(311);  plot(h1);  title('切比雪夫I群延迟');
subplot(312);  plot(h2);  title('切比雪夫II群延迟');
subplot(313);  plot(h3);  title('椭圆型群延迟');