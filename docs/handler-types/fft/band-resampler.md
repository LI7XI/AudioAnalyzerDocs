## BandResampler

Allows you to get one or more bands from [FFT](/docs/handler-types/fft/fft.md) result.
Each cascade of FFT result is resampled to fit into specified list of bands.

## BandResampler type Properties

### Jump list

- [Type](#type).
- [Source](#source).
- [Bands](#bands).
- [MinCascade](#min-cascade).
- [MaxCascade](#max-cascade).
- [CubicInterpolation](#cubic-interpolation).
- [Handler Info](#handler-info).
- [Documentation Questions](#q).

---

<p id="type" class="p-title"><b>Type</b><b>BandResampler</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type BandResampler
```

---

<p id="source" class="p-title"><b>Source</b><b>Required</b></p>

Name of source handler.

!>Should be name of [FFT](/docs/handler-types/fft/fft.md) type handler.

_Examples:_

```ini
Handler-HandlerName=Type Spectrogram | Source FFTHandler
```

---

<p id="bands" class="p-title"><b>Bands</b><b>Required</b></p>

Description on what bounds bands will have.

This parameter takes few arguments: `<Type>`, `<BandsCount>`, `<FreqMin>`, `<FreqMax>`

Possible types:

- `Log`: Will generate logarithmically increasing values.
- `Linear`(Recommended<small id="i1">[1](#q)</small>): Will generate evenly distributed values.
- `Custom`: You can specify anything you want.<small id="i2">[2](#q)</small>

_Examples:_

```ini
Handler-HandlerName=Type BandResampler | Source FFTHandler | Bands Linear 5 20 110
```

Or

```ini
Handler-HandlerName=Type BandResampler | Source FFTHandler | Bands Custom (?)
```

---

<p id="min-cascade" class="p-title"><b>MinCascade</b><b>Default: 0</b></p>

An integer in range from `0` to [FFT](/docs/handler-types/fft/fft?id=cascades-count) `CascadesCount`.<small id="i3">[3](#q)</small><br/>
Min cascade that should be used in value calculating.

Values other than 0 are meant mainly for testing purposes, because you can increase FFT `BinWidth` and get the same result but better performance.<small id="i4">[4](#q)</small><br/>

Set to 0 to use all cascades. Set to value in range from `1` to FFT `CascadesCount` to use cascades starting from cascadeMin.

_Examples:_

```ini
Handler-HandlerName=Type BandResampler | MinCascade 0
```

---

<p id="max-cascade" class="p-title"><b>MaxCascade</b><b>Default: 0</b></p>

An integer in range from `MinCascade` to [FFT](/docs/handler-types/fft/fft?id=cascades-count) `CascadesCount`.<small id="i3">[3](#q)</small><br/>
Max cascade that should be used in value calculating.<small id="i5">[5](#q)</small>

Values other than 0 are meant mainly for testing purposes, because you can decrease FFT `CascadesCount` and get the same result but better performance.

Set to value in range from cascadeMin to FFT `CascadesCount` to use cascades from cascadeMin to cascadeMax.<small id="i6">[6](#q)</small>

If MaxCascade is less than cascadeMin then all cascades up from cascadeMin are used.

_Examples:_

```ini
Handler-HandlerName=Type BandResampler | MaxCascade 0
```

---

<p id="cubic-interpolation" class="p-title"><b>CubicInterpolation</b><b>Default: true</b></p>

When one there are two bands that both take data from one FFT bin, there is a question on how they should sample data from it.

AudioLevel uses nearest neighbor sampling, which leads to issue of several neighbor bands having the same value.

AudioAnalyzer can do the same, or, when `CubicInterpolation` is true, it can use fancy cubic resampling, which makes values transition smoother to create an illusion of better resolution.

_Examples:_

```ini
Handler-HandlerName=Type BandResampler | CubicInterpolation true
```

CubicInterpolation `true`

<img src="docs\handler-types\examples\fft\cubic-interpolation-true.PNG" />

CubicInterpolation `false`

<img src="docs\handler-types\examples\fft\cubic-interpolation-false.PNG" />

---

### Handler Info

- `Bands Count`: Count of bands as specified by [freqList](#bands).
- `Lower Bound <Index>`: Lower frequency bound of Nth band.
- `Upper Bound <Index>`: Upper frequency bound of Nth band.
- `Central Frequency <Index>`: Center frequency of Nth band.

_Examples:_

```ini
[!Log [&ParentMeasure:Resolve(HandlerInfo, Channel Auto | HandlerName BandResamplerHandler | Bands Count)]]
; Or
[!Log [&ParentMeasure:Resolve(HandlerInfo, Channel Auto | HandlerName BandResamplerHandler | Upper Bound 5)]]
```

## Documentation Questions <i id="q">

[Q1](#i1): Because this is what users will expect, it took me a long time to figure it out when i copied your examples.<br/>
[Q2](#i2): Any example?<br/>
[Q3](#i3): I don't understand this relation and i don't know even how this parameter works, same for MaxCascade, maybe because i still didn't read the discussion, but no worries i'll come back to it later.<br/>
[Q4](#i4): This sentence was the main reason for why i didn't use them, also, when i tried to use them, the visualization looked really weird in some cases, it was better to just make the BinWidth smaller. Also what testing purposes?<br/>
[Q5](#i5): ?<br/>
[Q6](#i6): Is this a typo or you really mean cascadeMin and Max?<br/>

</i>
