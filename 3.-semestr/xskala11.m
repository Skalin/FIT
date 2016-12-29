% 1) Nacteni signalu a zakladni prace nad nim
[Signal, Fs] = audioread('xskala11.wav');

%signal musi byt radkovy vektor, pomoci fce whos zjisteno, ze je sloupcovy, proto inverze na radkovy
Signal = Signal';

%zobrazime hodnoty vzorkovaci frekvence
fprintf('Vzorkovaci frekvence signalu xskala11.wav je: %d\n', Fs);

%delka signálu
siglen = length(Signal);
fprintf('Delka signalu xskala11.wav je: %d v S/s nebo %d sekunda\n', siglen, (siglen/Fs));

%2) FFT a spektrum
spectrum = fft(Signal);
f = (0:(Fs-1))/Fs*Fs/2;
plot(f,abs(spectrum));
print('Spectrum','-dpng');

%3) Hodnota spektra v maximu
[~, maxindex] = max(abs(spectrum));
max = maxindex/Fs * Fs;
fprintf('Maximum modulu spektra ma: %d Hz\n', max);


%4) Filtr init
%implementujeme filtr za pomoci fce zplane, aby se nam lepe videlo, zda-li je filtr stabilni
%definice vstupu, pro pozdeji pouziti
a = [0.2289 0.4662];
b = [0.2324 -0.4112 0.2324];
zplane(b,a);
print('IIR_Filtr','-dpng');
%filtr stabilni neni, protoze | pol/y (je pouze jeden) | > 1, pro stabilitu je treba, aby | pol/y | < 1, vice v doku

%5) Frekvencni charakteristika filtru
H = freqz(b,a,Fs);
f = ((0:Fs-1)/Fs * Fs / 2);
plot(f,abs(H));
print('IIR_Filtr_kmitocet', '-dpng');

%6) Filtrace 
h = filter(b,a,Signal);
plot(f,h);
result = fft(h);
plot(f,abs(result));
print('IIR_Filtrace', '-dpng');

