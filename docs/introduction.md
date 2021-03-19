## Introduction

As we all know, rainmeter has AudioLevel plugin, which provides you a basic functionality on extracting useful data from audio stream. However, the word "basic" is very fitting term here.

Rainmeter has Fourier Transform. But it has several issues both from the mathematical nature of FFT algorithm and incorrect implementation.

Also it has `RMS` and `Peak` calculations. Which will show you if there was any sound, but they won't really give you an insight on real loudness level.

But aside from what AudioLevel provides, what else users may want to see?<br/>
They may want to see a Loudness meter, a Waveform, or a Spectrogram. Which unfortunately AudioLevel doesn't provide.

Worth noting that there is also a second version of AudioLevel called [AudioLevel2](https://forum.rainmeter.net/viewtopic.php?t=18802&start=280), it can draw a waveform image.

[What does AudioAnalyzer Provides over AudioLevel?](/docs/why.md)
