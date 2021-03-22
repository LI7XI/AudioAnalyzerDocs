## Fast Fourier Transform

Fourier Transform is a mathematical formula that decomposes an audio signal and tells you what frequencies it consists of.

?>Worth noting that you shouldn't use this handler on its own, it's recommended to use it with a [BandResampler](/docs/handler-types/fft/band-resampler.md).

## FFT Parameters

### Jump list

- [Type](#type)
- [BinWidth](#bin-width)
- [OverlapBoost](#overlap-boost)
- [CascadesCount](#cascades-count)
- [WindowFunction](#window-function)
- [Handler Info](#handler-info)
- [Usage](#usage)

---

<p id="type" class="p-title"><b>Type</b><b>FFT</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type FFT
```

---

<p id="bin-width" class="p-title"><b>BinWidth</b><b>Default: 100</b></p>

A float number that is bigger than `0`.<br>

Width of one FFT result bin, it's similar to AudioLevel `FFTSize`.<br/>
Also corresponds to the rate at which FFT is natively updated (before taking into account [OverlapBoost](#overlap-boost)). FFT with `BinWidth 10` and `OverlapBoost 1` will update 10 times per second.

The less this option is, the more detailed result you get, but the less frequently values change.<br/>
Recommended values start from `60` to `5`.

_Examples:_

```ini
Handler-HandlerName=Type FFT | BinWidth 6
```

---

<p id="overlap-boost" class="p-title"><b>OverlapBoost</b><b>Default: 2</b></p>

A float number that is bigger or equal to `1`.<br>
Similar to AudioLevel `FFTOverlap`. Increases FFT update rate at the expense of increased CPU load.

_Examples:_

```ini
Handler-HandlerName=Type FFT | BinWidth 6 | OverlapBoost 10
```

---

<p id="cascades-count" class="p-title"><b>CascadesCount</b><b>Default: 5</b></p>

An integer in range from `1` to `20`.<br/>
The plugin can increase resolution in low frequencies by using cascades of FFT.

!>You wouldn't see the effect of this parameter unless you used a [BandCascadeTransformer](/docs/handler-types/fft/band-cascade-transformer.md).

Think of this parameter as a `BinWidth` divider. If you have `BinWidth 8` and `CascadesCount 2` then the BinWidth in low frequencies would be `4`, but it will still be `10` in high frequencies.

See [FFT Cascades](/docs/discussions/fft-cascades.md) discussion.

_Examples:_

```ini
Handler-HandlerName=Type FFT | CascadesCount 1
```

---

<p id="window-function" class="p-title"><b>WindowFunction</b><b>Default: Hann</b></p>

Window functions make FFT results better. They make results look cleaner. But different functions will give slightly different results.

The syntax: Window function is defined as a type string optionally followed by arguments in parentheses.<br/>
Like this: `SomeType(10)`.

!>Note that the parentheses are connected to the type (`SomeType(10)`) and not separated (`SomeType (10)`).

Possible types:

- `None`: No arguments.
- `Hann`: No arguments.
- `Hamming`: No arguments.
- `kaiser`(Named alpha on Wikipedia): A float number argument. Default value: `3.0`.
- `Exponential`(Named D on Wikipedia): A float number argument. Default value: `8.69`.
- `Chebyshev`: A float number argument (attenuation of side lobes in decibels). Default value: `80.0`.

You can read about them in [Wikipedia](https://en.wikipedia.org/wiki/Window_function) or watch this [video](https://www.youtube.com/watch?v=YsqGQzJ_2V0) to know what is a window function.

_Examples:_

```ini
Handler-HandlerName=Type FFT | WindowFunction Hann
```

Or

```ini
Handler-HandlerName=Type FFT | WindowFunction kaiser
; The plugin will use the default value for this function, which is 3
```

Or

```ini
Handler-HandlerName=Type FFT | WindowFunction kaiser(7)
```

---

### Handler Info

- `Size`: Size of the FFT.
- `Cascades Count`: Value of [CascadesCount](#cascades-count) parameter.
- `Overlap`: Value of [OverlapBoost](#overlap-boost) parameter.
- `Nyquist Frequency`: Nyquist frequency of first cascade.
- `Nyquist Frequency <Index>`: Nyquist frequency of Nth cascade.
- `DC`: DC value of first cascade.
- `DC <Index>`: DC value of Nth cascade
- `BinWidth`: Actual BinWidth of first cascade.
- `BinWidth <Index>`: Actual BinWidth of Nth cascade.

_Examples:_

```ini
[!Log "[&ParentMeasure:Resolve(HandlerInfo, Channel Auto | Handler FFTHandler | Size)]"]
; Or
[!Log "[&ParentMeasure:Resolve(HandlerInfo, Channel Auto | Handler FFTHandler | Nyquist Frequency 5)]"]
```

## Usage

Check out [this](/docs/usage-examples/fft-spectrum.md) example to see how this handler is used.
