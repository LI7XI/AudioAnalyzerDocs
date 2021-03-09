## BandResampler

Allows you to get one or more bands from [FFT](/docs/handler-types/fft/fft.md) result.
Each cascade of FFT result is resampled to fit into specified list of bands.

## BandResampler type Properties

### Jump list

- [Type](#type).
- [Source](#source).
- [Bands](#bands).
- [CubicInterpolation](#cubic-interpolation).
- [Handler Info](#handler-info).

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

This parameter takes few arguments: `<Type>(Count <Value>, FreqMin <Value>, FreqMax <Value>)`

Possible types:

- `Log`: Will generate logarithmically increasing values.
- `Linear`: Will generate evenly distributed values.
- `Custom`: You can specify anything you want. _WIP_

_Examples:_

```ini
Handler-HandlerName=Type BandResampler | Source FFTHandler | Bands Linear(Count 5, FreqMin 5, FreqMax 110)
; Or
Handler-HandlerName=Type BandResampler | Source FFTHandler | Bands Log(Count 5, FreqMin 5, FreqMax 110)
```

Or

```ini
Handler-HandlerName=Type BandResampler | Source FFTHandler | Bands Custom ...
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

- `BandsCount`: Count of bands as specified in [Bands](#bands).
- `LowerBound <Index>`: Lower frequency bound of Nth band. the `Index` here is an integer in range from `0` to `BandsCount`.

  ?>Setting the Index to `<bandsCount>` (e.g. 7, 20, ...) will actually give you upper bound of the last band.

- `CentralFreq <Index>`: Center frequency of Nth band. the `Index` here is an integer in range from `0` to `BandsCount - 1`.

_Examples:_

```ini
[!Log [&ParentMeasure:Resolve(HandlerInfo, Channel Auto | Handler BandResamplerHandler | Data BandsCount)]]
; Or
[!Log [&ParentMeasure:Resolve(HandlerInfo, Channel Auto | Handler BandResamplerHandler | Data LowerBound 5)]]
```
