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
- [Width](#width).
- [Height](#Height).
- [Resolution](#resolution).
- [Stationary](#stationary).
- [Connected](#connected).
- [BackgroundColor](#background-color).
- [WaveColor](#wave-color).
- [LineColor](#line-color).
- [BorderSize](#border-size).
- [BorderColor](#border-color).
- [FadingRatio](#fading-ratio).
- [LineDrawingPolicy](#line-drawing-policy).
- [Transform](#transform).
- [SilenceThreshold](#silence-threshold).
- [Handler Info](#handler-info).
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
Handler-HandlerName=Type Waveform | Folder [#@]Images
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

Same as [Width](#width), but for Height.

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
Handler-HandlerName=Type Waveform | Resolution 1
```

Resolution: `0.8`

<img src="docs\handler-types\examples\waveform\res08.PNG" title="Resolution 0.8" />

Resolution: `40`

<img src="docs\handler-types\examples\waveform\res40.PNG" title="Resolution 40" />

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

<p id="connected" class="p-title"><b>Connected</b><b>Default: true</b></p>

When false draw real min-max values.
When true correct min-max so that waveform on the image doesn't contain gaps.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | Connected true
```

---

<p id="background-color" class="p-title"><b>BackgroundColor</b><b>Default: 0,0,0</b></p>

Color of the space where wave is not drawn.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | BackgroundColor 0.23,0.1,0.4
```

---

<p id="wave-color" class="p-title"><b>WaveColor</b><b>Default: 1,1,1</b></p>

Color of the wave.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | WaveColor 0.8,0.69,0.7
```

---

<p id="line-color" class="p-title"><b>LineColor</b><b>Default: <code>WaveColor</code></b></p>

Color of the line in zero values.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | LineColor 0.7,0.7,0.9
```

---

<p id="border-size" class="p-title"><b>BorderSize</b><b>Default: 0</b></p>

Define size of the border in the oldest stripes of the image.
It only makes sense to use this property when Stationary is true.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | BorderSize 3
```

---

<p id="border-color" class="p-title"><b>BorderColor</b><b>Default: 1.0,0.2,0.2</b></p>

Color of the border.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | BorderColor 0.6,0.6,0.8
```

---

<p id="fading-ratio" class="p-title"><b>FadingRatio</b><b>Default: 0</b></p>

A Float number in range from `0` to `1`.<br/>
Oldest `FadingRatio * 100%` stripes in the image are smoothly faded into the background color.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | FadingRatio 0.3
```

---

<p id="line-drawing-policy" class="p-title"><b>LineDrawingPolicy</b><b>Default: Always</b></p>

Resulting image can have horizontal line indicating zero value.

- `Always`: Draw line above wave.
- `BelowWave`: Wave will hide line.
- `Never`: Don't draw line.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | LineDrawingPolicy BelowWave
```

LineDrawingPolicy `Always`

<img src="docs\handler-types\examples\waveform\ldp-always.PNG" title="LineDrawingPolicy Always" />

LineDrawingPolicy `BelowWave`

<img src="docs\handler-types\examples\waveform\ldp-below-wave.PNG" title="LineDrawingPolicy BelowWave" />

LineDrawingPolicy `Never`

<img src="docs\handler-types\examples\waveform\ldp-never.PNG" title="LineDrawingPolicy Never" />

---

<p id="transform" class="p-title"><b>Transform</b><b>Default: None</b></p>

Description of transforms that are applied to values after calculating min and max.

Waveform always shows values in range [-1.0, 1.0]. If transform makes values outside of this range, they will not be displayed correctly.

When writing transform for waveform you may assume that all values are >= 0, and you also should produce values >= 0. Negative values will be calculated the same way, with automatic sign correction.

_Examples:_<small id="i1">[1](#q)</small>

```ini
Handler-HandlerName=Type Waveform |
```

---

<p id="silence-threshold" class="p-title"><b>SilenceThreshold</b><b>Default: -70</b></p>

Peak value threshold specified in decibels.

If sound wave is below SilenceThreshold then it is considered silence. Else image is updated. If you set it too high image will not be updating even when it should be.

The main usage for this property is to synchronize several images, if you have them in one skin. If two images have the same Resolution, SilenceThreshold and image width, and they are in the same parent measure, then they will perfectly synchronized.

_Examples:_

```ini
Handler-HandlerName=Type Waveform | SilenceThreshold -50
```

---

### Handler Info

- `File`: Path of the file in which image is written.
- `Block size`: Size of the block that represents one pixel in image, in audio points.

_Examples:_<small id="i2">[2](#q)</small>

```ini
[!Log [&ParentMeasure:Resolve(HandlerInfo, Channel Auto | HandlerName WaveformHandler | Data File)]]
; Or
[!Log [&ParentMeasure:Resolve(HandlerInfo, Channel Auto | HandlerName WaveformHandler | Data Block Size)]]
```

## Usage Examples

_WIP_.

## Documentation Questions <i id="q">

[Q1](#i1): In some handler types (i guess `RMS`, `Peak` and `loudness`), i said that `Transform` is "Required", is that true?<br/>
[Q2](#i2): Is the `Block Size` example correct?<br/>

</i>
