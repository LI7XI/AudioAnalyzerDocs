## Why using AudioAnalyzer?

AudioAnalyzer Plugin has much better ways to extract Loudness information from audio stream, it has better implementation of fourier transform with ways to fight fundamental flaws of FFT algorithm.

It also can draw a [Waveform](/docs/examples/waveform.md), and it can draw a [Spectrogram](/docs/examples/spectrogram.md) (not a [Spectrum](/docs/examples/spectrum.md) which only give you slice of frequency information, but a spectrogram). See [Examples](/docs/examples/examples.md) page.

On top of that, among other features, newer versions of AudioAnalyzer (1.1.5 and up) brings automatic switching between audio devices (including [WASAPI exclusive mode](/docs/plugin-structure/parent?id=exclusive-mode) handling) and [async computing](/docs/plugin-structure/parent?id=threading) for better UI performance.

## AudioAnalyzer vs AudioLevel

- AudioLevel doesn't have correct FFT calculations.
- AudioLevel doesn't have correct loudness calculations.
- AudioLevel can't [blur values](/docs/handler-types/handler-types?id=uniformblur).
- AudioLevel can't draw Waveform.
- AudioLevel can't draw Spectrogram.
- AudioLevel doesn't have frequency filtering.

There are a ton of optimizations, improvements and other features AudioAnalyzer have, but these are the highlights.

Here is a small example of a simple skin using AudioLevel vs using AudioAnalyzer:<br/>
<small><i>Tested on i3-2312m (2c 4t 2.10GHz) CPU with all skins disabled except this one.</i></small>

AudioLevel: `FreqMin 20` `FreqMax 2000` `Bands 160` `FFTSize 32768` `FFTOverlap 16384` `FFTAttack 120` `FFTDecay 200` `Sensitivity 45`

<div style="height: 147px; overflow: hidden;"><video src="docs/examples/resources/al-vs-aa.mp4" autoplay loop muted title="Using AudioLevel"></video></div>

AudioAnalyzer: `FreqMin 20` `FreqMax 2000` `Bands 160` `BinWidth 3.2` `OverlapBoost 5` `CascadesCount 1` `Attack 60` `Decay 45` `MindB -40` `MaxdB -5`

<div style="height: 147px; overflow: hidden;"><video style="transform: translateY(-140px)" src="docs/examples/resources/al-vs-aa.mp4" autoplay loop muted title="Using AudioAnalyzer"></video></div>

?>The comparison here for demonstration only, and the settings used here don't exactly match AudioLevel settings.<br/><br/>Don't worry if you don't understand the options used here, all of them are explained in this documentation.

As you can see, AudioLevel is kinda struggling when using a lot of bands and a high FFT size. While AudioAnalyzer is handling it easily.

You may notice that `FFTAttack` and `FFTDecay` in AudioLevel don't match `Attack` and `Decay` in AudioAnalyzer, that's because AudioLevel calculates them differently than AudioAnalyzer.
