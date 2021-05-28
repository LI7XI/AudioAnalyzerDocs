## Spectrogram Waveform Example

In this example, we have one objective: syncing Spectrogram and Waveform handlers together.

First let's setup the skin.

```ini
[Rainmeter]
Update=[#UpdateRate]

[Variables]
Fps=60
UpdateRate=(1000 / #Fps#)
; Formula is stolen from here: https://forum.rainmeter.net/viewtopic.php?t=26831#p140108
```

Now let's create the parent measure.

```ini
[MeasureAudio]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Parent
```

Let's make a new processing unit. We will call it Main.

```ini
ProcessingUnits=Main
```

Let's specify its description.<br/>
It's just a combination of both [Spectrogram](/docs/usage-examples/spectrogram.md) and [Waveform](/docs/usage-examples/waveform.md) examples.

```ini
Unit-Main=Channels Auto | Handlers FFT -> Resampler -> CascadeTransformer -> Transformer -> UniformBLur -> Spectrogram, Waveform | Filter none
```

Now let's specify the handlers description.<br/>

```ini
Handler-FFT=Type FFT | BinWidth 10 | OverlapBoost 40 | CascadesCount 1 | WindowFunction Hann
; --------------------------------------------------------------------------------------
Handler-Resampler=Type BandResampler | Bands Log(Count 150, FreqMin 20, FreqMax 20000) | CubicInterpolation true
; --------------------------------------------------------------------------------------
Handler-CascadeTransformer=Type BandCascadeTransformer
; --------------------------------------------------------------------------------------
Handler-Transformer=Type ValueTransformer | Transform dB, Map(From -50 : -0)
; --------------------------------------------------------------------------------------
Handler-UniformBLur=Type UniformBlur | Radius 1
; --------------------------------------------------------------------------------------
Handler-Spectrogram=Type Spectrogram | Folder [#@]Images/ | Length 300 | UpdateRate 28.5 | Stationary true | SilenceThreshold -70 | BorderSize 1 | DefaultColorSpace sRGB | MixMode sRGB255 | FadingRatio 0.2 | BorderColor @sRGB255 255, 171, 92 | Colors 0.0: @hsl 217,0.38,0.11 ; 1: @hsl 29, 0.96, 0.62
; --------------------------------------------------------------------------------------
Handler-Waveform=Type Waveform | Folder [#@]Images/ | Width 300 | Height 200 | UpdateRate 28.5 | Stationary true | BorderSize 1 | BorderColor 255, 64, 89| Connected true | DefaultColorSpace sRGB255 | BackgroundColor @hsl 237,0.34,0.20 | WaveColor 255, 64, 89 | LineColor @sRGB 0.5,0.5,0.5 | FadingRatio 0.2 | LineDrawingPolicy Never | SilenceThreshold -70
```

Let's make the child measures the same way we did in other examples.

```ini

[MeasureWaveform]
measure=plugin
Plugin=AudioAnalyzer
Type=child
Parent=MeasureAudio
StringValue=Info
InfoRequest=HandlerInfo, Channel Auto | Handler Waveform | Data File

[MeasureSpectrogram]
Measure=plugin
Plugin=AudioAnalyzer
Type=Child
Parent=MeasureAudio
StringValue=Info
InfoRequest=HandlerInfo, Channel auto | Handler Spectrogram | Data File
```

Lastly, let's make the meters.

```ini
[MeterWaveForm]
Meter=Image
MeasureName=MeasureWaveform

[MeterSpectrogram]
Meter=Image
MeasureName=MeasureSpectrogram
X=0
Y=200
```

That's all! The results:

<video src="docs\usage-examples\resources\spectrogram-waveform.mp4" autoplay loop muted title="Spectrogram Waveform"></video>

But if we made few changes in the parameter, let's say we changed the `UpdateRate` of the Waveform, we will get a different results.

`UpdateRate 50`

<img src="docs\usage-examples\resources\spectrogram-waveform-res-20.png" title="UpdateRate 50" />
