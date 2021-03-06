## Waveform Example

Here we will create a simple Waveform visualizer.

First let's setup the skin.

```ini
[Rainmeter]
Update=[#UpdateRate]

[Variables]
Fps=30
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

If you want to use filters, it's better to use custom filters, since filter presets (`like-a`, `like-d`) won't give you a good results when using waveform.

```ini
Unit-Main=Channels Auto | Handlers Waveform | Filter None
```

Now let's specify the handler description.

```ini
Handler-Waveform=Type Waveform | Folder [#@]Images/ | Width 300 | Height 200 | Stationary false | BorderSize 1 | BorderColor 255, 64, 89 | UpdateRate 1.666 | Connected true | DefaultColorSpace sRGB255 | BackgroundColor @hsl 237,0.34,0.20 | WaveColor 255, 64, 89 | LineColor @sRGB 0.5,0.5,0.5 | FadingRatio 0.2 | LineDrawingPolicy Never | SilenceThreshold -70
```

Waveform handler generates an image and write it to disk, by default the plugin will write it to where the .ini skin file is located, but we can change that using `Folder` parameter.

We can use child measure to access the image, it will provide the path as well as the image name.

To do that, we can set `StringValue` option to `Info` and use `InfoRequest` option to get the image location.

In `InfoRequest` option specify the following:

- `HandlerInfo` argument is used when getting infos from handlers.
- `Channels` parameter to specify the channel.
- `HandlerName` parameter to specify the handler we want to get infos from.
- `Data` parameter to specify what type of data we want this child measure to provide.

```ini
[MeasureWaveform]
measure=plugin
Plugin=AudioAnalyzer
Type=child
Parent=MeasureAudio
; Set StringValue to Info
StringValue=Info
; And specify what infos you want this child measure to provide
; Set the Data parameter to File to get the file path and name
InfoRequest=HandlerInfo, Channel Auto | HandlerName Waveform | Data File
```

?>Note that it's always recommended to use a child measure to get the image, because the image name will change based on your process name and handler name.

`DefaultColorSpace` let's you specify a default color space for any parameter that uses colors.<br/>

Let's say you have `BackgroundColor 0.9,0.4,0.7`, by defaults (without specifying `DefaultColorSpace`) the plugin will parse this as `sRGB` color (which is different from `sRGB255`, because `sRGB` values are in [0, 1] range).

If you set `DefaultColorSpace` to let's say `hsl` color space, the 3 values now corresponds to hue, saturation lightness. So it's pretty handy if you want to use one color space for all parameters.

But maybe you don't want all parameter to have the same color space, you can override the color space by writing `$<ColorSpace>` after the parameter name but before the color itself.<br/>
For example: `BackgroundColor @hsv 112,0.6,0.9` or `WaveColor @sRGB255 170, 220, 210`, same process for all parameters that use colors.

Now everything is ready :tada:<br/>
Simply make an image meter and set the `MeasureName` option to the child measure you created.

```ini
[MeterWaveForm]
Meter=Image
MeasureName=MeasureWaveform
```

<img src="docs\usage-examples\resources\waveform.png" title="Waveform visualizer" />

?>Since it's an image meter, all fancy image manipulation option that rainmeter provides are available (`ImageRotate`, `ImageFlip`, `ImageCrop`, `ColorMatrix`, etc..)

!>One thing to note, avoid using `W` and `H` options to change the image dimensions, instead, change them from the handler itself.
