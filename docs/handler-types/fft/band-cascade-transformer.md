## BandCascadeTransformer

Allows you to combine several cascades into one set of final values.

## BandCascadeTransformer type Properties

### Jump list

- [Type](#type).
- [Source](#source).
- [MixFunction](#mix-function).
- [MinWeight](#min-weight).
- [TargetWeight](#target-weight).
- [ZeroLevelMultiplier](#zero-level-multiplier).

---

<p id="type" class="p-title"><b>Type</b><b>BandCascadeTransformer</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type BandCascadeTransformer
```

---

<p id="source" class="p-title"><b>Source</b><b>Required</b></p>

Name of source handler.

!>Should be name of [BandResampler](/docs/handler-types/fft/band-resampler.md) type handler.

_Examples:_

```ini
Handler-HandlerName=Type BandCascadeTransformer | Source BandResamplerHandler
```

---

<p id="mix-function" class="p-title"><b>MixFunction</b><b>Default: Product</b></p>

Determines how different cascades are mixed.

When Product: result = `(c1 * c2 * ...) ^ (1 / N)`.<br/>
When Average: result = `(c1 + c2 + ...) / N`.

_Examples:_

```ini
Handler-HandlerName=Type BandCascadeTransformer | MixFunction Product
```

MixFunction `Product`

<img src="docs\handler-types\examples\fft\mix-function-product.PNG" />

MixFunction `Average`

<img src="docs\handler-types\examples\fft\mix-function-average.PNG" />

---

<p id="min-weight" class="p-title"><b>MinWeight</b><b>Default: 0.1</b></p>

A float number that is bigger or equal to `0`.<br>
Values with weight below MinWeight are thrown away.

Band weight is measured in FFT bins.<br/>
If band frequency width is the same as FFT bin width, then band weight is 1.<br/>
If band frequency width is half the width of FFT bin, then band weight is 0.5.

_Examples:_

```ini
Handler-HandlerName=Type BandCascadeTransformer | MinWeight 1
```

---

<p id="target-weight" class="p-title"><b>TargetWeight</b><b>Default: 2.5</b></p>

A float number that is bigger or equal to `MinWeight`.<br>
Minimum target weight of band.

Cascades are summed (and averaged at the end) until sum of their weights is less than TargetWeight. TargetWeight allows you to discard slow cascade values when band is already detailed enough.

_Examples:_

```ini
Handler-HandlerName=Type BandCascadeTransformer | TargetWeight 3
```

---

<p id="zero-level-multiplier" class="p-title"><b>ZeroLevelMultiplier</b><b>Default: 1</b></p>

A float number that is bigger or equal to `0`.<br>

Some FFT cascades may be updated very slowly. When there were a silence and then suddenly some sound, then some cascades may have already be updated while some are still zero. ZeroLevelMultiplier allows you to discard such old values to make transitions from silence to sound look smoother.

_Examples:_

```ini
Handler-HandlerName=Type BandCascadeTransformer | ZeroLevelMultiplier 2
```
