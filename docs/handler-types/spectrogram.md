## Spectrogram

Draws a spectrogram picture. That is: band's values changes in time.

Generates BMP image on disk. Name of the file is unspecified. To get it, you can follow this way:

Lets say this is your image meter:

```ini
[MeterSpectrogram]
Meter=Image
ImageName=
DynamicVariables=1
; DynamicVariables=1 is important.
```

!>Note: Don't use `W` and `H` options of the meter for resizing, the image may look blurred or distorted. Instead, change how the image is outputted from the handler itself.

You will use [handlerInfo]() Section Variable with `File` data property. Like this:

```ini
[&ParentMeasure:resolve(HandlerInfo, Channel Auto | Handler SpectogramHandler | Data File)]
```

Then you set the above as a value to `ImageName` option.

```ini
ImageName=[&ParentMeasure:resolve(HandlerInfo, Channel Auto | Handler SpectogramHandler | Data File)].
```

However, a more convenient way to obtain file name is to use a child measure with `StringValue=Info`.<br/>
Like so:

```ini
StringValue=Info
InfoRequest=HandlerInfo, Channel Auto | Handler SpectogramHandler | Data File
```

Then you use that in your image meter. Like so:

```ini
[MeterSpectrogram]
Meter=Image
MeasureName=ChildMeasure
; Dynamic variables are not needed since we are using MeasureName option.
```

Color of the pixel is linearly interpolated between color points, described by either [Colors]() property, or between [BaseColor]() and [MaxColor]() if Colors property is not present.

Width of the image is determined by [Length]() property, height of the image is determined by number of values in [source]() handler. You can control height by changing number of bands in [BandResampler]() handler.

### Jump list

- [Type](#type).
- [Source](#source).
- [](#).
- [](#).
- [](#).

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

; In child measure
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

<p id="type" class="p-title"><b>Resolution</b><b>Default: 50</b></p>

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

<p id="type" class="p-title"><b>Folder</b><b>Default: <code>Skin folder</code></b></p>

Path to folder where image will be stored.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | Folder #@#Images/
```

---

<p id="type" class="p-title"><b>Colors</b><b>Parameters: (See below)</b></p>

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

<p id="type" class="p-title"><b>BaseColor</b><b>Default: 0,0,0</b></p>

Color of the space where band values are below 0.

?>Only used when Colors property is not present, otherwise ignored.<small id="i1">[1](#q1)</small>

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler | BaseColor 0.0.2,0.21,0.25
```

BaseColor `0.1,0.1,0.25`

<img src="docs\handler-types\examples\spectrogram\basecolor1.PNG" title="BaseColor 0.1,0.1,0.25" />

BaseColor `1,1,0.4`

<img src="docs\handler-types\examples\spectrogram\basecolor2.PNG" title="BaseColor 1,1,0.4" />

---

<p id="type" class="p-title"><b>MaxColor</b><b>Default: 1,1,1</b></p>

Color of the space where band values are above 1.

?>Only used when Colors property is not present, otherwise ignored.<small id="i1">[1](#q1)</small>

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

<p id="type" class="p-title"><b>option</b><b>Default: 0</b></p>

Description

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler
```

---

<p id="type" class="p-title"><b>option</b><b>Default: 0</b></p>

Description

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source SourceHandler
```

---

## Documentation Questions <i id="q">

<small id="q1"></small>[Q1](#i1): "otherwise ignored."?<br/>
<small id="q1"></small>[Q1](#i1): <br/>
<small id="q1"></small>[Q1](#i1): <br/>
<small id="q1"></small>[Q1](#i1): <br/>
</i>
