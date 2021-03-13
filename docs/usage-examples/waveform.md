## Waveform Example

Here we will create a simple Waveform visualizer.

First lets setup the skin.

```ini
[Rainmeter]
Update=[#UpdateRate]

[Variables]
Fps=30
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

```ini
Unit-Main=Channels Auto | Handlers Waveform | Filter None
```

Now lets specify the handlers description.

```ini
Handler-Waveform=Type Waveform | Folder [#@]Images/ | Width 300 | Height 200 | Stationary false | BorderSize 1 | BorderColor 255, 64, 89 | Resolution 0.6 | Connected true | DefaultColorSpace sRGB255 | BackgroundColor @hsl 237,0.34,0.20 | WaveColor 255, 64, 89 | LineColor @sRGB 0.5,0.5,0.5 | FadingRatio 0.2 | LineDrawingPolicy Never | SilenceThreshold -70
```

Waveform meter generates an image and write it to disk, by default the plugin will write it to where the .ini skin file is located, but we can change that using `Folder` parameter.

We can use child measure to access the image, it will provide the path as well as the image name.

To that, we can set `StringValue` option to `Info` and use `InfoRequest` option to get the image location.

In `InfoRequest` option specify the following:

- `HandlerInfo` argument is used when getting infos from handlers.
- `Channels` parameter to specify the channel. <!-- Q -->
- `Handler` parameter to specify the handler we want to get infos from.
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
InfoRequest=HandlerInfo, Channel Auto | Handler Waveform | Data File
```

?>Note that it's always recommended to use a child measure to get the image, because the image name will change based on your process name and handler name.

Now everything is ready :tada:<br/>
Simply make an image meter and set the `MeasureName` option to the child measure you created.

```ini
[MeterWaveForm]
Meter=Image
MeasureName=MeasureWaveform
```

![Waveform](/examples/waveform.png "Waveform visualizer")

?>Since it's an image meter, all fancy image manipulation option that rainmeter provides are available (`ImageRotate`, `ImageFlip`, `ImageCrop`, `ColorMatrix`, etc..)

!>One thing to note, avoid using `W` and `H` options to change the image dimensions, instead, change them from the handler itself.
