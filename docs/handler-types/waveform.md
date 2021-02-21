## Waveform

Draws a waveform picture. That is: shows min and max values of the sound wave over some past time.

Generates BMP image on disk. Name of the file is unspecified. To get it, you can follow this way:

Lets say this is your image meter:

```ini
[MeterWaveform]
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
[MeterWaveform]
Meter=Image
MeasureName=ChildMeasure
```

## Waveform type Properties

### Jump list

- [Type](#type).
- [Folder](#folder).
- [Length](#length).
- [Resolution](#resolution).
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

<p id="type" class="p-title"><b>Type</b><b>Waveform</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type Waveform
```

---

<p id="folder" class="p-title"><b>Folder</b><b>Default: <code>Skin folder</code></b></p>

Path to folder where image will be stored.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | Folder #@#Images
```

---

<p id="width" class="p-title"><b>Width</b><b>Default: 100</b></p>

An integer that is bigger than `0`.<br>
Specifies image width. Equals to the count of points in time to show.

?>Type of this option is an integer, which means float numbers will be rounded: `60.3 → 60`.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | Width 160
```

---

<p id="height" class="p-title"><b>Height</b><b>Default: 100</b></p>

Same as [Width](#width).

_Examples:_

```ini
Handler-HandlerName=Type Waveform | Height 110
```

---

<p id="resolution" class="p-title"><b>Resolution</b><b>Default: 50</b></p>

A float number that is bigger than `0`.<br>
Time in milliseconds of block that represents one pixel width in image.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | Resolution 50
```

Resolution: `2`

<img src="docs\handler-types\examples\waveform\res2.PNG" title="Resolution 2" />

Resolution: `15`

<img src="docs\handler-types\examples\waveform\res15.PNG" title="Resolution 15" />

---

<p id="stationary" class="p-title"><b>Stationary</b><b>Default: false</b></p>

When false image is completely redrawn on each update. Image is moving to the left as it updates.

When true image is only redrawn in places where it has changed. All stripes are stationary, but some are replaces with new values.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | Stationary true
```

Stationary `false`

<video src="docs\handler-types\examples\waveform\stationary-false.mp4" autoplay loop muted title="Stationary false"></video>

Stationary `true`

<video src="docs\handler-types\examples\waveform\stationary-true.mp4" autoplay loop muted title="Stationary true"></video>

---

<p id="id" class="p-title"><b>Connected</b><b>Default: true</b></p>

When false draw real min-max values.
When true correct min-max so that waveform on the image doesn't contain gaps.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | Connected true
```

---

<p id="id" class="p-title"><b>option</b><b>Default: 0</b></p>

Description

_Examples:_

```ini
Handler-HandlerName=Type Waveform |
```

---
