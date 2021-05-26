## Colors

Colors may be defined in several color spaces: `sRGB`, `sRGB255`, `Hex`, `HSV`, `HSL`, `YCbCr`.

The way you use `Colors` parameter in [Spectrogram](/docs/handler-types/spectrogram?id=colors) is the following:<br/>
`Colors <Position>: @<ColorSpace> <Value>, <Value>, <Value>, <Alpha>; ...`<br/>
See [examples](#usage) below.

All values including Alpha are in range from `0` to `1`.

?>Alpha value is optional. If it is not defined, color is considered opaque, as if `Alpha` was 1.

?>`@<ColorSpace>` part is optional. If it is not defined, then default color space will be used.

HSV and HSL color spaces have singularity points. That is: points where their exact values are not defined. The most obvious point is full black color: it only has Value (or Lightness), Hue and Saturation may be anything and nothing will change. Points when Saturation is zero doesn't have Hue.

Except: when using HSV or HSL color spaces in the spectrogram, it uses linear interpolation and Hue and Saturation are always used.

If you define color in some other space, then automatic conversion from that color space into HSV will not know what to set Hue and Saturation to, and they will end up as zeros.

!>This may significantly alter resulting colors, so keep this in mind. You can define color in HSV or HSL spaces, so that all values are explicitly defined by you, to prevent color interpolation artifacts.

For example, these settings will give the following results:

`DefaultColorSpace sRGB255` `MixMode sRGB` `BorderColor 255, 171, 92` `Colors 0.0: @srgb 0.1,0.1,0.1 ; 1: @srgb 0.9, 0.9, 0.5`

<img src="docs/handler-types/examples/spectrogram/mixmode-srgb.png"/>

But when setting `MixMode` to `hsv`:

<img src="docs/handler-types/examples/spectrogram/mixmode-hsv.png"/>

Or `hsl`:

<img src="docs/handler-types/examples/spectrogram/mixmode-hsl.png"/>

You can read more about the difference between color spaces [here](https://www.programmersought.com/article/51822376187/).

## Jump list

- [sRGB](#rgb)
- [sRGB255](#srgb255)
- [HEX](#hex)
- [HSV](#hsv)
- [HSL](#hsl)
- [YCbCr](#ycbcr)
- [Usage](#usage)

---

<h3 id="srgb">sRGB</h3>

A classic color space, used almost everywhere.

Syntax: `@sRGB <R>, <G>, <B>`.<br/>
Example: `@sRGB 0.0, 1.0, 1.0` for cyan color.

You can use `Alpha` at the end, for example: `@sRGB <R>, <G>, <B>, <A>`.

---

<h3 id="srgb255">sRGB255</h3>

Similar to `sRGB`, but instead of being in [0, 1] range, it's in [0, 255] range.

Syntax: `@sRGB255 <R>, <G>, <B>`.<br/>
Example: `@sRGB255 130, 190, 200`.

You can use `Alpha` at the end, for example: `@sRGB255 <R>, <G>, <B>, <A>`.

?>Alpha is in [0, 255] range as well.

---

<h3 id="hex">HEX</h3>

You can specify colors in Hex format.

Syntax: `@hex RRGGBB`.<br/>
Example: `@hex 00FFFF`

Where `<RR>` is a Red component, `<GG>` is Green, `<BB>` is Blue.<br/>
In case you need Alpha component, then use this notation: `RRGGBBAA`, where `AA` represents Alpha component.

---

<h3 id="hsv">HSV</h3>

Stands for `Hue`, `Saturation`, `Value`.<br/>
Unlike most other values in colors, `Hue` is defined in range from `0` to `360`.

Syntax: `@hsv <H>, <S>, <V>`.<br/>
Example: `@hsv 52.0, 0.0, 0.102`.

You can use `Alpha` at the end, for example: `@hsv <H>, <S>, <V>, <A>`.

---

<h3 id="hsl">HSL</h3>

Stands for `Hue`, `Saturation`, `Lightness`.<br/>
Unlike most other values in colors, `Hue` is defined in range from `0` to `360`.

Syntax: `@hsl <H>, <S>, <L>`.<br/>
Example: `@hsl 52.0, 0.0, 0.305`.

You can use `Alpha` at the end, for example: `@hsl <H>, <S>, <L>, <A>`.

---

<h3 id="ycbcr">YCbCr</h3>

Syntax: `@YCbCr <Y>, <Cb>, <Cr>`.<br/>
Example: `@YCbCr 0.5, 1.0, 0.75`.

You can use `Alpha` at the end, for example: `@YCbCr <Y>, <Cb>, <Cr>, <A>`.

## Usage

In Spectrogram handler. Examples:

[Colors](/docs/handler-types/spectrogram?id=colors) Parameter: `Colors 0.0: @sRGB 0.1,0.1,0.1; 0.78: @hsv 150,0.85,0.5; ...`<br/>
[BaseColor](/docs/handler-types/spectrogram?id=base-color) Parameter: `BaseColor @sRGB255 170,140,190`<br/>
[BorderColor](/docs/handler-types/spectrogram?id=border-color) Parameter: `BorderColor @hsl 90,0.8,0.4`<br/>

And same for other parameters.

---

In Waveform handler. Examples:

[BackgroundColor](/docs/handler-types/waveform?id=background-color) Parameter: `BackgroundColor @sRGB 0.6,0.9,1.0`<br/>
[WaveColor](/docs/handler-types/waveform?id=wave-color) Parameter: `WaveColor @hsl 90,0.8,0.4`<br/>

And same for other parameters.
