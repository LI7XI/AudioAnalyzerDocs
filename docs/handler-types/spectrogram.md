## Spectrogram

Draws a spectrogram picture. That is: band's values changes in time.

This handler will generate an image and write it to disk, to use it in your skin, you can do the following:

Let's say this is your image meter:

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

Color of the pixel is linearly interpolated between color points, described by either [Colors](#colors) parameter, or between [BaseColor](#base-color) and [MaxColor](max-color) if Colors parameter is not present.

!>The source of this handler should be from [FFT](/docs/handler-types/fft/fft.md) transform chain, so that source handler has many values.

Width of the image is determined by [Length](#lenth) parameter, height of the image is determined by number of bands in [BandResampler](/docs/handler-types/fft/band-resampler.md) handler.

## Spectrogram Parameters

### Jump list

- [Type](#type)
- [Length](#length)
- [UpdateRate](#update-rate)
- [Folder](#folder)
- [Colors](#colors)
- [BaseColor](#base-color)
- [MaxColor](#max-color)
- [MixMode](#mix-mode)
- [Stationary](#stationary)
- [BorderSize](#border-size)
- [BorderColor](#border-color)
- [FadingRatio](#fading-ratio)
- [SilenceThreshold](#silence-threshold)
- [Usage](#usage)

---

<p id="type" class="p-title"><b>Type</b><b>Spectrogram</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram
```

---

<p id="length" class="p-title"><b>Length</b><b>Default: 100</b></p>

An integer that is bigger than `0`.<br>
Count of points in time to show. Equals to resulting image width.

?>Type of this option is an integer, which means float numbers will be rounded: `60.3 → 60`.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Length 320
```

---

<p id="update-rate" class="p-title"><b>UpdateRate</b><b>Default: 20</b></p>

A float number in range from `1` to `20000`.<br>
Image will have `UpdateRate` amount of new lines that represents one pixel width in image each second.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | UpdateRate 50
```

UpdateRate: `500`

<img src="docs\handler-types\examples\spectrogram\res2.PNG" title="UpdateRate 500" />

UpdateRate: `66.6`

<img src="docs\handler-types\examples\spectrogram\res15.PNG" title="UpdateRate 66.6" />

---

<p id="folder" class="p-title"><b>DefaultColorSpace</b><b>Default: sRGB</b></p>

You can set a default color space to be used in all parameters that uses colors. But of course you can override it in any parameter.

Available color spaces are:

- `sRGB`
- `sRGB255`
- `Hex`
- `Hsl`
- `Hsv`
- `YCbCr`

See [Colors](/docs/discussions/colors.md) discussion.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | DefaultColorSpace sRGB255
; Or
Handler-HandlerName=Type Spectrogram | DefaultColorSpace Hsl
```

?>You can override the default color space in any parameter that uses colors. Just use `@` symbol before the color space.

```ini
Handler-HandlerName=Type Spectrogram | DefaultColorSpace sRGB255 | BaseColor @Hsv 166,0.5,0.9
```

---

<p id="folder" class="p-title"><b>Folder</b><b>Default: <code>Skin folder</code></b></p>

Path to folder where image will be stored.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Folder [#@]Images
```

---

<p id="colors" class="p-title"><b>Colors</b><b>Parameters: (See below)</b></p>

A set of points that describe colors of the spectrogram.

Color point syntax: `Colors <Position> : <ColorDescription>`.<br/>
Position correspond to values from source handler.

`<ColorDescription>` in the simplest case can be represented as a comma-separated list of 3 or 4 values in range [0.0, 1.0].

See [Colors](/docs/discussions/colors.md) discussion.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Colors 0.0 : 0.1,0.1,0.1 ; 1.0 : @hsv 173,0.85,0.5 ; 1.5 : @sRGB255 235,90,70
```

---

<p id="base-color" class="p-title"><b>BaseColor</b><b>Default: 0,0,0</b></p>

Color of the space where band values are below 0.

?>If [Colors](#colors) parameter is used, this parameter will be ignored.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | BaseColor 0.2,0.21,0.25
```

BaseColor `0.1,0.1,0.25`

<img src="docs\handler-types\examples\spectrogram\basecolor1.PNG" title="BaseColor 0.1,0.1,0.25" />

BaseColor `1,1,0.4`

<img src="docs\handler-types\examples\spectrogram\basecolor2.PNG" title="BaseColor 1,1,0.4" />

---

<p id="max-color" class="p-title"><b>MaxColor</b><b>Default: 1,1,1</b></p>

Color of the space where band values are above 1.

?>If [Colors](#colors) parameter is used, this parameter will be ignored.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | MaxColor 0.7,0.68,0.73
```

Let's say `BaseColor 0,0,0`

MaxColor `1,1,1`

<img src="docs\handler-types\examples\spectrogram\maxcolor1.PNG" title="MaxColor 1,1,1" />

---

<p id="mix-mode" class="p-title"><b>MixMode</b><b>Default: <code>Value of DefaultColorSpace</code></b></p>

Sets the color space in which values are interpolated.

!>Note that `MixMode` doesn't affect how colors are read (e.g. in `Colors`, `BaseColor`, etc..). It only affects how intermediate colors are calculated.

You can use any of the following color spaces: `sRGB`, `hsv`, `hsl`, `YCbCr`.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | MixMode HSV | BaseColor 160,0.5,0.79
```

`MixMode sRGB` with `Colors 0.0: @hsl 217,0.38,0.11 ; 1: @hsl 29, 0.96, 0.62`:

<img src="docs/handler-types/examples/spectrogram/mixmode-srgb.png"/>

`MixMode hsv` with same colors:

<img src="docs/handler-types/examples/spectrogram/mixmode-hsv.png"/>

---

<p id="stationary" class="p-title"><b>Stationary</b><b>Default: false</b></p>

When false image is completely redrawn on each update. Image is moving to the left as it updates.

When true image is only redrawn in places where it has changed. All stripes are stationary, but some are replaces with new values.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Stationary true
```

Stationary `false`

<video src="docs\handler-types\examples\spectrogram\stationary-false.mp4" autoplay loop muted title="Stationary false"></video>

Stationary `true`

<video src="docs\handler-types\examples\spectrogram\stationary-true.mp4" autoplay loop muted title="Stationary true"></video>

---

<p id="border-size" class="p-title"><b>BorderSize</b><b>Default: 0</b></p>

Define size of the border in the oldest stripes of the image.
It only makes sense to use this parameter when Stationary is true.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Stationary true | BorderSize 3
```

BorderSize `20`

<img src="docs\handler-types\examples\spectrogram\border-size20.png" title="BorderSize 20" />

---

<p id="border-color" class="p-title"><b>BorderColor</b><b>Default: 1.0,0.2,0.2</b></p>

Color of the border

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Stationary true | BorderSize 3 | BorderColor 0.3,0.3,0.75
```

---

<p id="fading-ratio" class="p-title"><b>FadingRatio</b><b>Default: 0</b></p>

A Float number in range from `0` to `1`.<br/>
Oldest `FadingRatio * 100%` stripes in the image are smoothly faded into the background color.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | FadingRatio 1
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

The main usage for this parameter is to synchronize several images, if you have them in one skin. If two images have the same UpdateRate, SilenceThreshold and image width, and they are in the same parent measure, then they will perfectly synchronized.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | SilenceThreshold -50
```

## Usage

Check out [this](/docs/usage-examples/spectrogram.md) example to see how this handler is used.
