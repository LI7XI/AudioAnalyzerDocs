## Why using AudioAnalyzer?

AudioAnalyzer Plugin has much better ways to extract loudness information from audio stream, it has better implementation of fourier transform with ways to fight fundamental flaw of FFT algorithm, it also can draw a [Waveform](/docs/examples/waveform.md), and it can draw a [Spectrogram](/docs/examples/spectrogram.md) (not a [Spectrum](/docs/examples/spectrum.md) which only give you slice of frequency information, but a spectrogram). See [Examples](/docs/examples/examples.md) page.

By the way, Drawing the spectrogram is the feature I was missing the most, and it was the main reason why this plugin is created in the first place.<small id="i1">[1](#q)</small>

On top of that, among other features, AudioAnalyzer 1.1.5 brings automatic switching between audio devices (including WASAPI exclusive mode handling) and [async computing]() for better UI performance.<small id="i1">[1](#q)</small>

## AudioAnalyzer vs AudioLevel

- AudioLevel doesn't have Spectrogram.
- AudioLevel doesn't correct Attack/Decay values when sample rate changes.
- AudioLevel doesn't do proper channel mapping. For example, it doesn't recognize 4.0 channel layout.
- AudioLevel can't resample wave when sampling rate is high.
- AudioLevel only allow you to declare one calculation of values for all channels. It doesn't allow you to define FFT for only one channel and RMS for one another.
- AudioLevel calculates values differently:
  - FFT: AudioLevel doesn't do proper normalization of the values. This leads to great change of values when `FFTSize`<small id="i2">[2](#q)</small> is changed. To be precise, FFT of size 16384 is 32 times bigger than FFT of size 16.
  - RMS: AudioLevel doesn't have RMS. It calculates filtered squared wave value instead.
  - Peak: AudioLevel doesn't have Peak. It calculates filtered absolute wave value instead.
- AudioLevel doesn't have cascaded FFT.
- AudioLevel don't let you define relative size of the FFT, only absolute (this causes a big problems when sample rate of your sound card changes or when you want to distribute your skin).
- AudioLevel doesn't correct zeroth value of the FFT.
- Band: AudioLevel's Band feature always calculates sum of the FFT bins instead of average, which is not always desirable.
- AudioLevel calculates bound using squared values of the FFT, which leads to incorrect filtering and (as far as I can tell) incorrect final values (they are much spikier than they need to be).
- AudioLevel's Band doesn't blur values.

Here is a small example of a simple skin using AudioLevel vs using AudioAnalyzer:

AudioLevel: `FreqMin 20` `FreqMax 110` `Bands 160` `FFTSize 8128` `FFTOverlap 4096`

<video src="" autoplay loop muted title="Using AudioLevel"></video>

AudioAnalyzer: `FreqMin 20` `FreqMax 110` `Bands 160` `BinWidth 5` `OverlapBoost 2`

<video src="" autoplay loop muted title="Using AudioAnalyzer"></video>

?>Don't worry if you don't understand the options used here, all of them are explained in this documentation.

## Documentation Questions <i id="q">

[Q1](#i1): Keep it?<br/>
[Q2](#i2): "FFTSize" right? also is this comparison list still valid?<br/>

</i>
