## Spectrogram

Draws a spectrogram picture. That is: band's values changes in time.

Generates BMP image on disk. Name of the file is unspecified. To get it, you can follow this way:

Lets say this is your image meter:

```ini
[MeterSpectrogram]
Meter=Image
MeasureName=
```

!>Note: Don't use `W` and `H` options of the meter for resizing, the image may look blurred or distorted. Instead, change how the image is outputted from the handler itself.

You make a child measure with `StringValue=Info`, and set the `InfoRequest` to the following:

```ini
StringValue=Info
InfoRequest=HandlerInfo, Channel Auto | Handler SpectogramHandler | Data File
```

Then you use that in your image meter. Like so:

```ini
[MeterSpectrogram]
Meter=Image
MeasureName=ChildMeasure
```

Color of the pixel is linearly interpolated between color points, described by either [Colors](#colors) property, or between [BaseColor](#base-color) and [MaxColor](max-color) if Colors property is not present.

Width of the image is determined by [Length](#lenth) property, height of the image is determined by number of values in [Source](#source) handler. You can control height by changing number of bands in [BandResampler]() handler.

## Spectrogram type Properties

### Jump list

- [Type](#type).
- [Source](#source).
- [Length](#length).
- [Resolution](#resolution).
- [Folder](#folder).
- [Colors](#colors).
- [BaseColor](#base-color).
- [MaxColor](#max-color).
- [MixMode](#mix-mode).
- [Stationary](#stationary).
- [BorderSize](#border-size).
- [BorderColor](#border-color).
- [FadingRatio](#fading-ratio).
- [SilenceThreshold](#silence-threshold).
- [Usage Examples](#Usage-Examples).
- [Documentation Questions](#q).

---

<p id="type" class="p-title"><b>Type</b><b>Spectrogram</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram
```

---

<p id="source" class="p-title"><b>Source</b><b>Required</b></p>

Name of source handler. Should be name of some handler from [FFT]() transform chain, so that source handler has many values.

_Examples:_

```ini
; In parent measure
Handler-SourceHandler=Type BandResampler
; Or
Handler-SourceHandler=Type BandCascadeTransformer

; Then
Handler-HandlerName=Type Spectrogram | Source SourceHandler
```

---

<p id="length" class="p-title"><b>Length</b><b>Default: 100</b></p>

An integer that is bigger than `0`.<br>
Count of points in time to show. Equals to resulting image width.

?>Type of this option is an integer, which means float numbers will be rounded: `60.3 → 60`.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | Length 320
```

---

<p id="resolution" class="p-title"><b>Resolution</b><b>Default: 50</b></p>

A float number that is bigger than `0`.<br>
Time in milliseconds of block that represents one pixel width in image.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | Resolution 50
```

Resolution: `2`

<img src="docs\handler-types\examples\spectrogram\res2.PNG" title="Resolution 2" />

Resolution: `15`

<img src="docs\handler-types\examples\spectrogram\res15.PNG" title="Resolution 15" />

---

<p id="folder" class="p-title"><b>Folder</b><b>Default: <code>Skin folder</code></b></p>

Path to folder where image will be stored.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | Folder #@#Images
```

---

<p id="colors" class="p-title"><b>Colors</b><b>Parameters: (See below)</b></p>

A set of points that describe colors of the spectrogram.

Color point syntax: `Colors <Value> : <ColorDescription>`.<br/>
Values correspond to values from source handler.

`<ColorDescription>` in the simplest case can be represented as a comma-separated list of 3 or 4 values in range [0.0, 1.0].

In that case values correspond to RGB channels and alpha channel of the color.

See [Colors section]() for full list of color description possible values.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | Colors 0.0 : 0.1,0.1,0.1 ; 1.0 : 0.9,0.85,0.5 ; 1.5 : 1.0,0.0,0.0
```

---

<p id="base-color" class="p-title"><b>BaseColor</b><b>Default: 0,0,0</b></p>

Color of the space where band values are below 0.

?>Only used when Colors property is not present, otherwise ignored.<small id="i1">[1](#q)</small>

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | BaseColor 0.0.2,0.21,0.25
```

BaseColor `0.1,0.1,0.25`

<img src="docs\handler-types\examples\spectrogram\basecolor1.PNG" title="BaseColor 0.1,0.1,0.25" />

BaseColor `1,1,0.4`

<img src="docs\handler-types\examples\spectrogram\basecolor2.PNG" title="BaseColor 1,1,0.4" />

---

<p id="max-color" class="p-title"><b>MaxColor</b><b>Default: 1,1,1</b></p>

Color of the space where band values are above 1.

?>Only used when Colors property is not present, otherwise ignored.<small id="i1">[1](#q)</small>

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | MaxColor 0.7,0.68,0.73
```

Lets say `BaseColor 0,0,0`

MaxColor `1,1,1`

<img src="docs\handler-types\examples\spectrogram\maxcolor1.PNG" title="MaxColor 1,1,1" />

MaxColor `0,0,1`

<img src="docs\handler-types\examples\spectrogram\maxcolor2.PNG" title="MaxColor 0,0,1" />

---

<p id="mix-mode" class="p-title"><b>MixMode</b><b>Default: sRGB</b></p>

Sets the color space in which values are interpolated.

!>Note that `MixMode` doesn't affect how colors are read (e.g. in `Colors`, `BaseColor`, etc..). It only affects how intermediate colors are calculated.

Parameters:

- `sRGB` : When using sRGB colors: `0.6,0.5,0.7`.
- `HSV` : When using Hue, Saturation, Value colors: `122,0.67,0.89`.
- `HSL` : When using Hue, Saturation, Lightness colors: `200,0.7,0.4`.
- `YCbCr`: When using .<small id="i2">[2](#q)</small>

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | MixMode HSV | BaseColor 160,0.5,0.79
```

---

<p id="stationary" class="p-title"><b>Stationary</b><b>Default: false</b></p>

When false image is completely redrawn on each update. Image is moving to the left as it updates.

When true image is only redrawn in places where it has changed. All stripes are stationary, but some are replaces with new values.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | Stationary true
```

Stationary `false`

<video src="docs\handler-types\examples\spectrogram\stationary-false.mp4" autoplay loop muted title="Stationary false"></video>

Stationary `true`

<video src="docs\handler-types\examples\spectrogram\stationary-true.mp4" autoplay loop muted title="Stationary true"></video>

---

<p id="border-size" class="p-title"><b>BorderSize</b><b>Default: 0</b></p>

Define size of the border in the oldest stripes of the image.
It only makes sense to use this property when Stationary is true.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | Stationary true | BorderSize 3
```

BorderSize `20`

<img src="docs\handler-types\examples\spectrogram\border-size20.png" title="BorderSize 20" />

---

<p id="border-color" class="p-title"><b>BorderColor</b><b>Default: 1.0,0.2,0.2</b></p>

Color of the border

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | Stationary true | BorderSize 3 | BorderColor 0.3,0.3,0.75
```

---

<p id="fading-ratio" class="p-title"><b>FadingRatio</b><b>Default: 0</b></p>

A Float number in range from `0` to `1`.<br/>
Oldest `FadingRatio * 100%` stripes in the image are smoothly faded into the background color.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | FadingRatio 1
```

FadingRatio `0.3`

<img src="docs\handler-types\examples\spectrogram\fading-ratio03.png" title="FadingRatio 0.3" />

FadingRatio `1`

<img src="docs\handler-types\examples\spectrogram\fading-ratio1.png" title="FadingRatio 1" />

---

<p id="silence-threshold" class="p-title"><b>SilenceThreshold</b><b>Default: -70</b></p>

A Float number that is bigger than `0`.<br/>
Peak value threshold specified in decibels.

If sound wave is below SilenceThreshold then it is considered silence. Else image is updated. If you set it too high image will not be updating even when it should be.

The main usage for this property is to synchronize several images, if you have them in one skin. If two images have the same Resolution, SilenceThreshold and image width, and they are in the same parent measure, then they will perfectly synchronized.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | SilenceThreshold -50
```

## Usage Examples

_WIP_.

## Documentation Questions <i id="q">

[Q1](#i1): "otherwise ignored.", should i keep that?<br/>
[Q2](#i2): How to write this format (the syntax)?<br/>
</i>
