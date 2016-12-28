[Signal, Fs] = audioread('xskala11.wav');
Signal = Signal';
spectrum = fft(Signal, Fs/2);
