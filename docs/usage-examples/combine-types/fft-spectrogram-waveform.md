## FFT Spectrogram Waveform Example

The main purpose of this example is showing you the relation between FFT bands and the spectrogram.<br/>

?>To keep it short, we aren't getting into details about how the meters are made. It's all available in the .rmskin file, check it out!

First let's setup the skin.

```ini
[Rainmeter]
Update=[#UpdateRate]
; To make a cool background
BackgroundMode=2
GradientAngle=-90
SolidColor=0,0,0,100
SolidColor2=0,0,0,0

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
It's just a combination of [FFT Spectrum](/docs/usage-examples/fft-spectrum.md), [Spectrogram](/docs/usage-examples/spectrogram.md) and [Waveform](/docs/usage-examples/waveform.md) examples.

```ini
Unit-Main=Channels Auto | Handlers FFT -> Resampler -> CascadeTransformer, UniformBLur(CascadeTransformer), ReMaper(CascadeTransformer), Transformer(UniformBLur) -> Spectrogram, Waveform | Filter none
```

Now let's specify the handlers description.<br/>

```ini
Handler-FFT=Type FFT | BinWidth 10 | OverlapBoost 40 | CascadesCount 4 | WindowFunction Hann
; --------------------------------------------------------------------------------------
Handler-Resampler=Type BandResampler | Bands Linear(Count #Bands#, FreqMin 20, FreqMax 2000) | CubicInterpolation true
; --------------------------------------------------------------------------------------
Handler-CascadeTransformer=Type BandCascadeTransformer | MixFunction Average | MinWeight 0.01 | TargetWeight 2
; --------------------------------------------------------------------------------------
Handler-UniformBLur=Type UniformBlur | Radius 1
; --------------------------------------------------------------------------------------
Handler-ReMaper=Type TimeResampler | Attack 20 | Decay 60 | UpdateRate ([#UpdateRate]*2) | Transform dB, Map(From -41 : -0, to [#MinHeight] : [#MaxHeight]), Clamp(to [#MinHeight] : [#MaxHeight])
; --------------------------------------------------------------------------------------
Handler-Transformer=Type ValueTransformer | Transform dB, Map(From -41 : -0)
; --------------------------------------------------------------------------------------
; --------------------------------------------------------------------------------------
Handler-Spectrogram=Type Spectrogram | Folder [#@]Images/ | Length 100 | UpdateRate 28.5 | SilenceThreshold -70 | Stationary false | BorderSize 1 | DefaultColorSpace sRGB | MixMode sRGB255 | FadingRatio 0.2 | BorderColor @sRGB255 255, 171, 92 | Colors 0.0: @hsl 217,0.38,0.11 ; 0.5: @hsl 29, 0.96, 0.62 ; 0.81: @hsl 0, 0.96, 0.62
; --------------------------------------------------------------------------------------
Handler-Waveform=Type Waveform | Folder [#@]Images/ | Width 300 | Height 200 | UpdateRate 1666.6 | Stationary false | BorderSize 1 | BorderColor 255, 64, 89 | Connected true | DefaultColorSpace sRGB255 | BackgroundColor @hsl 237,0.34,0.20 | WaveColor 255, 64, 89 | LineColor @sRGB 0.5,0.5,0.5 | FadingRatio 0.2 | LineDrawingPolicy Never | SilenceThreshold -70
```

Lemme explain what is going on here:

First, we simply created a spectrum, but we changed the order a bit. We made `UniformBlur` handler comes before `TimeResampler`, so we can have a specific value for each purpose:

- `ReMaper` handler will be used for the spectrum.
- `Transformer` handler will be used for the spectrogram, because it needs a different transformations than the spectrum.
- And finally `Waveform`, this this handler doesn't need a source + it outputs an image and not a numerical value, so we added it at the very end. Changing its position in the handlers order won't affect anything.

Now the parent measure is ready!

We will simply follow what we did in the previous examples in creating child measures and meters.

Child measures:

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

@Include=#@#Measures/FFTSpectrogramWaveform.inc
```

Meters:

```ini
[MeterWaveForm]
Meter=Image
MeasureName=MeasureWaveform

[MeterSpectrogram]
Meter=Image
MeasureName=MeasureSpectrogram
X=300
Y=100
ImageRotate=90

; There is another shape meter that is used for the spectrum, the shapes are generated using a script so it has its own file.
@Include2=#@#Meters/FFTSpectrogramWaveform.inc
```

That's it!

<video src="docs\usage-examples\resources\fft-spectrogram-waveform.mp4" autoplay loop muted title="FFT Spectrogram Waveform"></video>
