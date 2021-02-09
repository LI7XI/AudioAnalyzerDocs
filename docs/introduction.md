## Introduction

Rainmeter has AudioLevel plugin, which provides you a basic functionality on extracting useful data from audio stream. However, the "basic" is the very fitting term here.

What do users want to see regarding audio visualization? Users may want to see a "loudness meter" and some fancy visualization frequencies.

AudioLevel plugin doesn't really have a correct loudness meter. It has "RMS" and "Peak" calculations, which will show you if there was any sound, but they won't really give you an insight on real loudness level. I will post loudness discussion somewhere nearby.

For fancy visualizations AudioLevel has Fourier transform. Kind of. It has several issues both from the mathematical nature of FFT algorithm and incorrect implementation.

There is also a second version of that plugin out there, AudioLevel2, that can also draw a waveform image.
