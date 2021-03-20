## Why using AudioAnalyzer?

AudioAnalyzer Plugin has much better ways to extract Loudness information from audio stream, it has better implementation of fourier transform with ways to fight fundamental flaws of FFT algorithm.

It also can draw a [Waveform](/docs/examples/waveform.md), and it can draw a [Spectrogram](/docs/examples/spectrogram.md) (not a [Spectrum](/docs/examples/spectrum.md) which only give you slice of frequency information, but a spectrogram). See [Examples](/docs/examples/examples.md) page.

On top of that, among other features, newer versions of AudioAnalyzer (1.1.5 and up) brings automatic switching between audio devices (including [WASAPI exclusive mode](/docs/plugin-structure/parent?id=exclusive-mode) handling) and [async computing](/docs/plugin-structure/parent?id=threading) for better UI performance.

## AudioAnalyzer vs AudioLevel

- AudioLevel doesn't have Spectrogram.
- AudioLevel doesn't correct Attack/Decay values when sample rate changes.
- AudioLevel doesn't do proper channel mapping. For example, it doesn't recognize 4.0 channel layout.
- AudioLevel can't resample wave when sampling rate is high.
- AudioLevel only allow you to declare one calculation of values for all channels. It doesn't allow you to define FFT for only one channel and RMS for one another.
- AudioLevel calculates values differently:
  - FFT: AudioLevel doesn't do proper normalization of the values. This leads to great change of values when `FFTSize` is changed. To be precise, FFT of size 16384 is 32 times bigger than FFT of size 16.
  - RMS: AudioLevel doesn't have RMS. It calculates filtered squared wave value instead.
  - Peak: AudioLevel doesn't have Peak. It calculates filtered absolute wave value instead.
- AudioLevel doesn't have cascaded FFT.
- AudioLevel don't let you define relative size of the FFT, only absolute (this causes a big problems when sample rate of your sound card changes or when you want to distribute your skin).
- AudioLevel doesn't correct zeroth value of the FFT.
- Band: AudioLevel's Band feature always calculates sum of the FFT bins instead of average, which is not always desirable.
- AudioLevel calculates bound using squared values of the FFT, which leads to incorrect filtering and (as far as I can tell) incorrect final values (they are much spikier than they need to be).
- AudioLevel's Band doesn't blur values.

This is a tiny portion of what this plugin provides.

Here is a small example of a simple skin using AudioLevel vs using AudioAnalyzer:<br/>
Tested on i3-2312m (2c 4t 2.10GHz) CPU with all skins disabled except this one.

AudioLevel: `FreqMin 20` `FreqMax 2000` `Bands 160` `FFTSize 32512` `FFTOverlap 16256`

<video src="\docs\examples\resources\test-audiolevel.mp4" autoplay loop muted title="Using AudioLevel"></video>

AudioAnalyzer: `FreqMin 20` `FreqMax 2000` `Bands 160` `BinWidth 10` `OverlapBoost 10` `CascadesCount 3`

<video src="\docs\examples\resources\test-audioanalyzer.mp4" autoplay loop muted title="Using AudioAnalyzer"></video>

?>Don't worry if you don't understand the options used here, all of them are explained in this documentation.

As you can see, AudioLevel is kinda struggling when using a lot of bands and a high FFT size. While AudioAnalyzer is handling it easily.

The visual difference comes to the fact that AudioLevel stretches frequencies logarithmically, AudioAnalyzer can do that as well, but it can also display frequencies linearly, which is what you saw above.
