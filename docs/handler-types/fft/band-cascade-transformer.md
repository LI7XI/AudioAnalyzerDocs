## BandCascadeTransformer

Allows you to combine several cascades into one set of final values.

!>The source of this handler must be of type [BandResampler](/docs/handler-types/fft/band-resampler.md).

## BandCascadeTransformer Parameters

### Jump list

- [Type](#type)
- [MixFunction](#mix-function)
- [MinWeight](#min-weight)
- [TargetWeight](#target-weight)
- [Usage](#usage)

---

<p id="type" class="p-title"><b>Type</b><b>BandCascadeTransformer</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type BandCascadeTransformer
```

---

<p id="mix-function" class="p-title"><b>MixFunction</b><b>Default: Product</b></p>

Determines how different cascades are mixed.

When using `Product`: Results = `(c1 * c2 * ...) ^ (1 / N)`.<br/>
When using `Average`: Results = `(c1 + c2 + ...) / N`.

_Examples:_

```ini
Handler-HandlerName=Type BandCascadeTransformer | MixFunction Product
```

---

<p id="min-weight" class="p-title"><b>MinWeight</b><b>Default: 0</b></p>

A float number that is bigger or equal to `0`.<br>
Values with weight below MinWeight are thrown away.

Band weight is measured in FFT bins.<br/>
If band frequency width is the same as FFT bin width, then band weight is 1.<br/>
If band frequency width is half the width of FFT bin, then band weight is 0.5.

_Examples:_

```ini
Handler-HandlerName=Type BandCascadeTransformer | MinWeight 0
```

---

<p id="target-weight" class="p-title"><b>TargetWeight</b><b>Default: 2.5</b></p>

A float number that is bigger or equal to `MinWeight`.<br>
Minimum target weight of band.

Cascades are summed (and averaged at the end) until sum of their weights is less than TargetWeight. TargetWeight allows you to discard slow cascade values when band is already detailed enough.

_Examples:_

```ini
Handler-HandlerName=Type BandCascadeTransformer | TargetWeight 2
```

---

## Usage

Check out [this](/docs/usage-examples/fft-spectrum.md) example to see how this handler is used.
