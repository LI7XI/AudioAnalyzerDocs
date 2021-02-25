## Fourier Transform

Fourier Transform of the signal. Gives you values of frequencies from 0 to SamplingRate/2 (=Nyquist frequency).

Should always be used with Band handler. You can get values directly from FFT but that doesn't make much sense: there is a variable number of resulting values, which is difficult to manage in skin.

_Todo: a full rewrite of this section._

## FFT type Properties

### Jump list

- [Type](#type).
- [BinWidth](#bin-width).
- [OverlapBoost](#overlap-boost).
- [CascadesCount](#cascades-count).
- [WindowFunction](#window-function).
<!-- - [Usage Examples](#Usage-Examples). -->
- [Documentation Questions](#q).

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

Width of one FFT result bin.<small id="i1">[1](#q)</small> Also corresponds to the rate at which FFT is natively updated (before taking into account [OverlapBoost](#overlap-boost)). FFT with `BinWidth 10` and `OverlapBoost 1` will update 10 times per second.

The less this option is, the more detailed result you get, but the less frequently values change.<br/>
Recommended values start from `60` to `5`.

The formula for converting `BinWidth` to AudioLevel `FFTSize`: `FFTSize = SampleRate / BinWidth`.

So if you have an AudioLevel skin with FFTSize=4096, then, assuming sampling rate is 48000, corresponding BinWidth is 11.71875
Though, if sample rate is 192000, then same FFTSize=4096 corresponds to BinWidth 46.875, which is completely different story in terms of details of fft result.<br/>
This is the reason this plugin uses BinWidth instead of fftSize.<small id="i2">[2](#q)</small>

_Examples:_

```ini
Handler-HandlerName=Type FFT | BinWidth 6
```

BinWidth `10`

<img src="docs\handler-types\examples\fft\bin-width10.PNG" />

BinWidth `4`

<img src="docs\handler-types\examples\fft\bin-width4.PNG" />

---

<p id="overlap-boost" class="p-title"><b>OverlapBoost</b><b>Default: 2</b></p>

A float number that is bigger or equal to `1`.<br>
Increases FFT update rate at the expense of increased CPU load.

The formula for converting `OverlapBoost` to AudioLevel `FFTOverlap`:

`OverlapBoost = 1 / (1 - FFTOverlap)`, where overlap is calculated as AudioLevel `FFTOverlap / FFTSize`.<small id="i3">[3](#q)</small>

So if you have an AudioLevel skin with FFTOverlap 2048 and FFTSize 4096 then Overlap is 0.5, and OverlapBoost is 2.<small id="i4">[4](#q)</small>

_Examples:_

```ini
Handler-HandlerName=Type FFT | BinWidth 6 | OverlapBoost 10
```

---

<p id="cascades-count" class="p-title"><b>CascadesCount</b><b>Default: 5</b></p>

An integer in range from `1` to `20`.<br/>
The plugin can increase resolution in lower frequencies by using cascades of FFT.<small id="i5">[5](#q)</small>

See [FFT Cascades]() discussion.

_Examples:_

```ini
Handler-HandlerName=Type FFT | CascadesCount 1
```

---

<p id="window-function" class="p-title"><b>WindowFunction</b><b>Default: Hann</b></p>

Window functions make FFT results better. They make result look cleaner. But different functions will give slightly different results.

The syntax: Window function is defined as a type string optionally followed by arguments in brackets.<br/>
Like this: `SomeType[10]`.

!>Note that the brackets are connected to the type (`SomeType[10]`) and not separated (`SomeType [10]`).

Possible types:

- `None`: No arguments.
- `Hann`: No arguments.
- `Hamming`: No arguments.
- `kaiser`(Named alpha on Wikipedia): A float number argument. Default value: `3.0`
- `Exponential`(Named D on Wikipedia): A float number argument. Default value: `8.69`.
- `Chebyshev`: A float number argument (attenuation of side lobes in decibels)<small id="i6">[6](#q)</small>.<small id="i7">[7](#q)</small>. Default value: `80.0`.

I personally find that kaiser with default alpha is the best. You can experiment to see the difference yourself, maybe you will find a more suitable window for your usage.

You can read about them in [Wikipedia](https://en.wikipedia.org/wiki/Window_function) or watch this [video](https://www.youtube.com/watch?v=YsqGQzJ_2V0) to know what is a window function.

_Examples:_

```ini
Handler-HandlerName=Type FFT | WindowFunction Hann
```

Or

```ini
Handler-HandlerName=Type FFT | WindowFunction kaiser[3]
```

## Documentation Questions <i id="q">

[Q1](#i1): I couldn't find illustrations to explain this, wikipedia seems overwhelming, should we leave it for later?<br/>P.S I guess users already know this parameter (AudioLevel `FFTSize`).<br/>
[Q2](#i2): Assuming sample rate is always going to be 48000 (idk how AudioLevel deals with that), will this formula always work?<br/>
[Q3](#i3): First time we did AudioLevel `FFTSize` to `BinWidth` conversion, but this time we did AudioAnalyzer `OverlapBoost` to `FFTOverlap` conversion. shouldn't we do the opposite here?<br/>
[Q4](#i4): wut? "overlap is 0.5", which overlap? yes i did few corrections but now i'm confused.<br/>
[Q5](#i5): I thought it increases the update rate speed, in other words making values update faster.<br/>
[Q6](#i6): Unless someone have read about it, he won't know what this means, just like when i read it in first time.<br/>
[Q7](#i7): When using this function, it makes the skin and rainmeter as a whole freezes for few minutes. But it still works.<br/>

</i>
