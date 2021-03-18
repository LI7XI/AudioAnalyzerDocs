## Spectrogram Waveform Example

In this example, we have an objective: Syncing Spectrogram and Waveform handlers together.

First lets setup the skin.

```ini
[Rainmeter]
Update=[#UpdateRate]

[Variables]
Fps=60
UpdateRate=(1000 / #Fps#)
; Formula is stolen from here: https://forum.rainmeter.net/viewtopic.php?t=26831#p140108
```

Now lets create the parent measure.

```ini
[MeasureAudio]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Parent
MagicNumber=104
```

Lets make a new processing unit. We will call it Main.

```ini
ProcessingUnits=Main
```

Lets specify its description.<br/>
It's just a combination of both [Spectrogram](/docs/usage-examples/spectrogram.md) and [Waveform](/docs/usage-examples/waveform.md) examples.

```ini
Unit-Main=Channels Auto | Handlers FFT, Resampler(FFT), CascadeTransformer(Resampler), Transformer(CascadeTransformer), UniformBLur(Transformer), Spectrogram(UniformBLur), Waveform | Filter none
```

Now lets specify the handlers description.<br/>

```ini
Handler-FFT=Type FFT | BinWidth 10 | OverlapBoost 40 | CascadesCount 1 | WindowFunction Hann
; --------------------------------------------------------------------------------------
Handler-Resampler=Type BandResampler | Bands Log(Count 150, Min 20, Max 20000) | CubicInterpolation true
; --------------------------------------------------------------------------------------
Handler-CascadeTransformer=Type BandCascadeTransformer
; --------------------------------------------------------------------------------------
Handler-Transformer=Type ValueTransformer | Transform dB, Map(From -50 : -0)
; --------------------------------------------------------------------------------------
Handler-UniformBLur=Type UniformBlur | Radius 1 | RadiusAdaptation 1
; --------------------------------------------------------------------------------------
Handler-Spectrogram=Type Spectrogram | Folder [#@]Images/ | Length 300 | Resolution 35 | Stationary true | SilenceThreshold -70 | BorderSize 1 | DefaultColorSpace sRGB | MixMode sRGB255 | FadingRatio 0.2 | BorderColor @sRGB255 255, 171, 92 | Colors 0.0: @hsl 217,0.38,0.11 ; 1: @hsl 29, 0.96, 0.62
; --------------------------------------------------------------------------------------
Handler-Waveform=Type Waveform | Folder [#@]Images/ | Width 300 | Height 200 | Resolution 35 | Stationary true | BorderSize 1 | BorderColor 255, 64, 89| Connected true | DefaultColorSpace sRGB255 | BackgroundColor @hsl 237,0.34,0.20 | WaveColor 255, 64, 89 | LineColor @sRGB 0.5,0.5,0.5 | FadingRatio 0.2 | LineDrawingPolicy Never | SilenceThreshold -70
```

Lets make the child measures the same way we did in other examples.

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

Lastly, lets make the meters.

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

That's all! Look how they are perfectly synced.

<video src="docs\usage-examples\examples\spectrogram-waveform.mp4" autoplay loop muted title="Spectrogram Waveform"></video>

But if we made few changes in the parameter, lets say we changed the resolution of the Waveform, we will get a different results.

`Resolution 20`

<img src="docs\usage-examples\examples\spectrogram-waveform-res20.png" title="Resolution 20" />
