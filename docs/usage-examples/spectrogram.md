## Spectrogram Example

Here we will create a simple Spectrogram visualizer.

First let's setup the skin.

```ini
[Rainmeter]
Update=[#UpdateRate]

[Variables]
Fps=40
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
The way Spectrogram handler works is it shows us how FFT band's values change in time.

Which means we first need to setup FFT, just as if we want to make a spectrum, then make it the source for our spectrogram.

?>We will assume that you already know how to make FFT spectrum, if not, please check out [this](/docs/usage-examples/fft-spectrum.md) tutorial before preceding.

```ini
Unit-Main=Channels Auto | Handlers FFT -> Resampler -> CascadeTransformer -> Filter -> UniformBLur -> Spectrogram | Filter none
```

Now let's specify the handlers description.

The setup is similar to the way we did it in FFT spectrum tutorial, but with few minor changes.<br/>
We will simply add the Spectrogram handler.

```ini
Handler-FFT=Type FFT | BinWidth 4 | OverlapBoost 15 | CascadesCount 1 | WindowFunction Hann
; --------------------------------------------------------------------------------------
Handler-Resampler=Type BandResampler | Bands Log(Count 150, FreqMin 20, FreqMax 20000) | CubicInterpolation true
; --------------------------------------------------------------------------------------
Handler-CascadeTransformer=Type BandCascadeTransformer | MixFunction Product | MinWeight 0.01 | TargetWeight 2
; --------------------------------------------------------------------------------------
Handler-Filter=Type TimeResampler | Transform dB, Map(From -50 : -0) | Attack 20 | Decay 5
; --------------------------------------------------------------------------------------
Handler-UniformBLur=Type UniformBlur | Radius 1
; --------------------------------------------------------------------------------------
Handler-Spectrogram=Type Spectrogram | Folder [#@]Images/ | length 300 | UpdateRate 28.5 | SilenceThreshold -70 | Stationary false | BorderSize 1 | DefaultColorSpace sRGB255 | MixMode sRGB | FadingRatio 0.2 | BorderColor 255, 171, 92 | Colors 0.0: @hsl 217,0.38,0.11 ; 1: @hsl 29, 0.96, 0.62
```

Similar to waveform handler, Spectrogram handler generates an image and write it to disk, by default the plugin will write it to where the .ini skin file is located, but we can change that using `Folder` parameter.

We can use child measure to access the image, it will provide the path as well as the image name.

To do that, we can set `StringValue` option to `Info` and use `InfoRequest` option to get the image location.

In `InfoRequest` option specify the following:

- `HandlerInfo` argument is used when getting infos from handlers.
- `Channels` parameter to specify the channel.
- `HandlerName` parameter to specify the handler we want to get infos from.
- `Data` parameter to specify what type of data we want this child measure to provide.

```ini
[MeasureSpectrogram]
measure=plugin
Plugin=AudioAnalyzer
Type=child
Parent=MeasureAudio
; Set StringValue to Info
StringValue=Info
; And specify what infos you want this child measure to provide
; Set the Data parameter to File to get the file path and name
InfoRequest=HandlerInfo, Channel Auto | HandlerName Spectrogram | Data File
```

?>Note that it's always recommended to use a child measure to get the image, because the image name will change based on your process name and handler name.

The width of the image is determent by `Length` parameter.<br/>
The height of the image is determent by how many bands you have in `BandResampler` handler.

`DefaultColorSpace` let's you specify a default color space for any parameter that uses colors.

Let's say you have `BaseColor 0.9,0.4,0.7`, by defaults (without specifying `DefaultColorSpace`) the plugin will parse this as `sRGB` color (which is different from `sRGB255` because here RGB values are in [0, 1] range).

If you set `DefaultColorSpace` to let's say `hsl` color space, the 3 values now corresponds to hue, saturation lightness. So it's pretty handy if you want to use one color space for all parameters.

But maybe you don't want all parameter to have the same color space, you can override the color space by writing `$<ColorSpace>` after the parameter name but before the color itself.<br/>
For example: `BaseColor @hsv 112,0.6,0.9` or `MaxColor @sRGB255 170, 220, 210`, same process for all parameters that use colors.

But in `Colors` parameter you specify the color space after the position.<br/>
For example: `Colors 0.0: @hsl 217,0.38,0.11 ; 0.5: @hsl 130,0.64,0.73 ; 1: @hsl 29, 0.96, 0.62`

`MixMode` parameter let's us specify in which color space intermediate colors are calculated, by default is uses the default color space.

There are 2 ways to specify the Spectrogram colors:

- `BaseColor` and `MaxColor` parameters.
- `Colors` parameter.

The difference is:

`BaseColor` and `MaxColor` let's you color source values that in [0, 1] range only, whereas `Colors` parameter gives you more freedom.

For example, if our source value is in range from [0, 1], `BaseColor` corresponds to 0, and `MaxColor` to 1, and values in between will be a mix between them.

`Colors` parameter on the other hand, let us be more specific, we can specify a color, and let it corresponds to a specific value, let's say `0.7`, `0.42` or even `1.35`, it all depends on the source range.<br/>
We will use `Colors` parameter.

That's it! Everything is ready :tada:<br/>
Simply make an image meter and set the `MeasureName` option to the child measure you created.

```ini
[MeterSpectrogram]
Meter=Image
MeasureName=MeasureSpectrogram
```

<img src="docs\usage-examples\resources\spectrogram.png" title="Spectrogram visualizer" />

?>Since it's an image meter, all fancy image manipulation option that rainmeter provides are available (`ImageRotate`, `ImageFlip`, `ImageCrop`, `ColorMatrix`, etc..)

!>One thing to note, avoid using `W` and `H` options to change the image dimensions, instead, change them from the handler itself.
