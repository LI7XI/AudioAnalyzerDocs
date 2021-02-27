## Colors

Colors may be defined in several color spaces: `RGB` (actually sRGB), `HSV`, `HSL`, `YCbCr`.

The way you use `Colors` parameter in [Spectrogram](/docs/handler-types/spectrogram?id=colors) is the following: `Colors <Position>: @<ColorSpace>$ <Value>, <Value>, <Value>, <Alpha>; ...`.

All values including Alpha are in range from `0` to `1`.

?>Alpha value is optional. If it is not defined, color is considered opaque, as if `Alpha` was 1.

?>`@<ColorSpace>$` part is optional. If it is not defined, then default color space will be used.<small id="i1">[1](#q)</small>

HSV and HSL color spaces have singularity points. That is: points where their exact values are not defined. The most obvious point is full black color: it only has Value (or Lightness), Hue and Saturation may be anything and nothing will change. Points when Saturation is zero doesn't have Hue.

Except: when using HSV or HSL color spaces in the spectrogram, it uses linear interpolation and Hue and Saturation are always used.

If you define color in some other space, then automatic conversion from that color space into HSV will not know what to set Hue and Saturation to, and they will end up as zeros.

!>This may significantly alter resulting colors, so keep this in mind. You can define color in HSV or HSL spaces, so that all values are explicitly defined by you, to prevent color interpolation artifacts.

You can read more about the difference between color spaces [here](https://www.programmersought.com/article/51822376187/).

## Jump list

- [RGB](#rgb)
- [HSV](#hsv)
- [HSL](#hsl)
- [YCbCr](#ycbcr)
- [Usage](#usage)

---

<h3 id="rgb">RGB</h3>
A classic color space, used almost everywhere.

Syntax: `@rgb$ <R>, <G>, <B>`.<br/>
Example: `0.0, 1.0, 1.0` for cyan color.

?>Alternatively, you can define colors in hex, like in most places in rainmeter.

Syntax: `@hex$ RRGGBB`.<br/>
Example: `@hex$ 00FFFF`

Where `<RR>` is a Red component, `<GG>` is Green, `<BB>` is Blue.<br/>
In case you need Alpha component, then it also uses this notation: `RRGGBBAA`, where `AA` represents Alpha component.

---

<h3 id="hsv">HSV</h3>

Stands for `Hue`, `Saturation`, `Value`.<br/>
Unlike most other values in colors, `Hue` is defined in range from `0` to `360`.

Syntax: `@hsv$ <H>, <S>, <V>`.<small id="i2">[2](#q)</small><br/>
Example: `@hsv$ 52.0, 0.0, 0.102`.

---

<h3 id="hsl">HSL</h3>

Stands for `Hue`, `Saturation`, `Lightness`.<br/>
Unlike most other values in colors, `Hue` is defined in range from `0` to `360`.

Syntax: `@hsv$ <H>, <S>, <L>`.<br/>
Example: `@hsv$ 52.0, 0.0, 0.305`.

---

<h3 id="ycbcr">YCbCr</h3>

Syntax: `@YCbCr$ <Y>, <Cb>, <Cr>`.<br/>
Example: `@YCbCr$ 0.5, 1.0, 0.75`.

## Usage

<small id="i3">[3](#q)</small>

In Spectrogram handler. Examples:

[Colors](/docs/handler-types/spectrogram?id=colors) Parameter: `Colors 0.0: @rgb$ 0.1,0.1,0.1; 1.0: @hsv$ 150,0.85,0.5; ...`.<br/>
[BaseColor](/docs/handler-types/spectrogram?id=base-color) Parameter: `BaseColor rgb 0.6,0.9,1.0`.<br/>
[BorderColor](/docs/handler-types/spectrogram?id=border-color) Parameter: `BorderColor hsl 90,0.8,0.4`.<br/>

And same for other parameters.

---

In Waveform handler. Examples::

[BackgroundColor](/docs/handler-types/waveform?id=background-color) Parameter: `BackgroundColor rgb 0.6,0.9,1.0`.<br/>
[WaveColor](/docs/handler-types/waveform?id=wave-color) Parameter: `WaveColor hsl 90,0.8,0.4`<br/>

And same for other parameters.

## Documentation Questions <i id="q">

[Q1](#i1): Assuming there is `DefaultColorSpace` parameter.<br/>
[Q2](#i2): `@hsv$ <H>, <S>, <V>, <A>` for Alpha?<br/>
[Q3](#i3): Assuming we used the new method for specifying colors.<br/>

</i>
