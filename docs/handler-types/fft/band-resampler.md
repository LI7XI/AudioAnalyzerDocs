## BandResampler

Allows you to get one or more bands from [FFT](/docs/handler-types/fft/fft.md) result.
Each cascade of FFT result is resampled to fit into specified list of bands.

!>The source of this handler must be of type FFT.

## BandResampler Parameters

### Jump list

- [Type](#type)
- [Bands](#bands)
- [CubicInterpolation](#cubic-interpolation)
- [Handler Info](#handler-info)
- [Usage](#usage)

---

<p id="type" class="p-title"><b>Type</b><b>BandResampler</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type BandResampler
```

---

<p id="bands" class="p-title"><b>Bands</b><b>Required</b></p>

Description on what bounds bands will have.

This parameter takes few arguments: `<Type>(Count <Value>, FreqMin <Value>, FreqMax <Value>)`

Possible types:

- `Log`: Will generate logarithmically increasing values.
- `Linear`: Will generate evenly distributed values.
- `Custom`: You can specify custom boundaries.

_Examples:_

```ini
Handler-HandlerName=Type BandResampler | Bands Linear(Count 5, FreqMin 20, FreqMax 110)
; Or
Handler-HandlerName=Type BandResampler | Bands Log(Count 5, FreqMin 20, FreqMax 110)
```

Or

```ini
Handler-HandlerName=Type BandResampler | Bands Custom(20, 300, 850, 1200, 2000, 3560)
; Here we specified 6 boundaries which will give us 5 bands
; Each band will corresponds to a specific frequency range:

; 20 |  300  |  800  |  1200 |  2000  | 3560
;  Band0 | Band1 | Band2 | Band3 | Band4

; Band0: From 20Hz to 300Hz
; Band1: From 300Hz to 850Hz
; Band2: From 850Hz to 1200Hz
; Band3: From 1200Hz to 2000Hz
; Band4: From 2000Hz to 3560Hz
```

---

<p id="cubic-interpolation" class="p-title"><b>CubicInterpolation</b><b>Default: true</b></p>

When one there are two bands that both take data from one FFT bin, there is a question on how they should sample data from it.

AudioLevel uses nearest neighbor sampling, which leads to issue of several neighbor bands having the same value.

AudioAnalyzer can do the same, or, when `CubicInterpolation` is true, it can use cubic resampling, which makes values transition smoother to create an illusion of better resolution.

_Examples:_

```ini
Handler-HandlerName=Type BandResampler | CubicInterpolation true
```

CubicInterpolation `true`

<img src="docs\handler-types\examples\fft\cubic-interpolation-true.png" />

CubicInterpolation `false`

<img src="docs\handler-types\examples\fft\cubic-interpolation-false.png" />

---

### Handler Info

- `BandsCount`: Count of bands as specified in [Bands](#bands).
- `LowerBound <Index>`: Lower frequency bound of Nth band. the `Index` here is an integer in range from `0` to `BandsCount`.

  ?>Setting the Index to `<bandsCount>` will actually give you upper bound of the last band.

- `CentralFreq <Index>`: Center frequency of Nth band. the `Index` here is an integer in range from `0` to `BandsCount - 1`.

_Examples:_

```ini
[!Log "[&ParentMeasure:Resolve(HandlerInfo, Channel Auto | Handler BandResamplerHandler | Data BandsCount)]"]
; Or
[!Log "[&ParentMeasure:Resolve(HandlerInfo, Channel Auto | Handler BandResamplerHandler | Data LowerBound 5)]"]
```

## Usage

Check out [this](/docs/usage-examples/fft-spectrum.md) example to see how this handler is used.
