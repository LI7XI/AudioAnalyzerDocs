## Why using AudioAnalyzer?

AudioAnalyzer Plugin has much better ways to extract loudness information from audio stream, it has better implementation of fourier transform with ways to fight fundamental flaw of FFT algorithm, it also can draw a waveform, and it can draw a spectrogram (not a spectrum which only give you slice of frequency information, but a spectrogram).

By the way, drawing the spectrogram is the feature I was missing the most, and it was the main reason why I created this plugin in the first place.

On top of that, among other features, AudioAnalyzer 1.1.5 brings automatic switching between audio devices (including WASAPI exclusive mode handling) and [async computing]() for better UI performance.
