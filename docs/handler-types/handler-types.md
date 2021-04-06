## Handler Types

This discussion is all about handlers.

## What is a handler

After we make a [Process](/docs/plugin-structure/parent?id=processing-unit) and specify its [description](/docs/plugin-structure/parent?id=unit-unitname):

```ini
ProcessingUnit=Main
Unit-Main=Channels Auto | Handlers HandlerA, HandlerB | Filter like-a
```

This Process is going to provide a chunk of audio data, separated into channels (such as `Left` and `Right` for a stereo audio stream).

Handlers will take this data, and process it to extract a specific signal from it. Using one of the [available handler](#available-handlers) types.

```ini
Handler-HandlerA=Type FFT
; Or
Handler-HandlerB=Type Loudness
```

Then, handlers will generate a value from the processed audio signal that can be used in [Child](/docs/plugin-structure/child.md) measures.

## Handler description

Any handler you specify, has a set of parameters, For example:

```ini
Handler-MainBR=Type BandResampler | Bands Log(Count [#Bands], FreqMin 20, FreqMax 2000) | CubicInterpolation | | SomeRandomParameter with value
```

In the line above:

- Rainmeter option name is: `Handler-MainBR`
- Handler name is: `MainBR`
- Handler type is: `BandResampler`
- `Bands` parameter is: `Log(Count [#Bands], FreqMin 20, FreqMax 2000)`<br>
  `[#Bands]`, which is a standard Rainmeter way to dereference a variable. Like all rainmeter variables, it is defined somewhere in the `[Variables]` section of the skin.
- `CubicInterpolation` parameter is empty, which means it uses default value. Just as If it wasn't specified.
- `SomeRandomParameter` is: with value<br/>
  This parameter does not apply to handlers of type `BandResampler`, which is why there will be a log warning about unused property.<br/>
- There is also an empty property description without a name (`| |`). It doesn't do and doesn't mean anything. Such empty properties are ignored.

## Handler Source

Some handlers can be chained together, to do that, we go to unit description, then we specify the name of the source handler inside parentheses:

```ini
Unit-Main=Channels ... | Handlers HandlerA, HandlerB(HandlerA), HandlerC(HandlerB) | ...
```

Alternatively there is another syntax (`->`) for specifying handler source:

```ini
Unit-Main=Channels ... | Handlers HandlerA -> HandlerB -> HandlerC | ...
```

The above is equivalent to `Handlers HandlerA, HandlerB(HandlerA), HandlerC(HandlerB)`.

You can mix both syntaxes:

```ini
Unit-Main=Channels ... | Handlers HandlerA -> HandlerB, HandlerC(HandlerB) | ...
```

---

Although not all handler types can be used as a source or they accept taking a source.

FFT, RMS, Peak, Loudness, these handlers can become a source for other handlers, but they don't accept taking a source.

ValueTransformer and TimeResampler take a source, and they can be used as a source as well.

Spectrogram takes a source, but it can't become a source, since it only outputs an image not a numerical value.

Waveform doesn't accept taking a source, nor it can become a source, since it only outputs an image not a numerical value.

## Available Handlers

There are types like `FFT`, `RMS`, `Peak`, `Loudness` and `Waveform` that can be used to extract the desired audio signal.<br/>
There are other types, we will talk about them in a moment.

### FFT

Fast Fourier Transformation is a mathematical formula that samples an audio signal over a period of time and divide it into its frequency components.

?>Note this is the only handler type that provides an [index](/docs/plugin-structure/child?id=index) range for the child measures to use, which mean any handler that is using it as a source will have an index range as well.

?>This handler type provides an array of values, which you can specify the value index using [index](/docs/plugin-structure/child?id=index) option in child measures.<br/> Any handler that is using this handler as a source will have an array of values as well.

#### BandResampler

Handler of type `FFT` is not very useful on it's own, while you still can retrieve values from it, you **should** use a `BandResampler` after it, and retrieve values from that instead.

It will give you a better control of which frequency bands you want to retrieve and the results will look much better.

#### BandCascadeTransformer

There is a fundamental math issue in FFT algorithm, you can either have a very detailed results that is updating slowly, or fast results that is not detailed enough, or something in between.

The problem is that high frequencies (800Hz and up) mostly have higher resolution than low and mid frequencies (less than 800Hz) while still updating faster than mids and lows.

This handler type lets you have high resolution in low frequencies based on an option called [CascadesCount](/docs/handler-types/fft/fft?id=cascades-count) in [FFT](/docs/handler-types/fft/fft.md) parameters, then it combines both of low and high frequencies together to have a detailed result through the entire frequencies range.

See [FFT Cascades](/docs/discussions/fft-cascades.md) discussion.

#### UniformBlur

Since `FFT` handler provides an index range, and each index corresponds to a specific band value, this handler allows you to blur values between the bands, so that the transition between bands values look smoother.

Before:

<img src="docs/examples/resources/uniform-blur-before.PNG" />

After:

<img src="docs/examples/resources/uniform-blur-after.PNG" />

Examples above were done without using [CubicInterpolation](/docs/handler-types/fft/band-resampler?id=cubic-interpolation) parameter.

?>Note that the results here will vary based on your settings (e.g. frequency range, resolution, bands count, etc).

---

### RMS, Peak and Loudness

At first, these 3 handlers will look similar to each other, but they have few differences:

- `RMS`: Sum squares of values over X ms, find average, get root of result.
- `Peak`: Find maximum value over X ms. If there was a silence and just 1 sound sample near maximum, then result will be near maximum.
- `Loudness`: Sum squares of values over X ms (but separated into smaller blocks), throw out too quiet blocks, find average of remaining blocks.

  Unlike RMS, Loudness doesn't get root of result, but in case of using decibels this changes little.<br/>
  Decibel value of a root of some value is 2 times less than a decibels of this value without root.

  For example, let `x=0.1`, then `x^2`, it will equal `0.01` which is 10 times less.<br/>
  But when using decibels: `dB(x)=-10dB`, then `dB(x^2)`, it will equal `-20dB`, the difference is only 2 times, not 10.

  If you use `x=5`, then `x^2`, normally `x^2` will be 5 times more than x, but `dB(x^2)` will still be just 2 times more than `dB(x)`.

  So, when you are using linear values, the difference between RMS and Loudness handlers will be drastic, but when converted to decibels, it will be quite hard to spot the difference.

  See [Transforms](/docs/discussions/transforms.md) discussion to know more about decibels.

?>Unless you have a specific need for `RMS` or `Peak` handler types, it's recommended to use `Loudness`.

## Value manipulators

### TimeResampler

[TimeResampler](/docs/handler-types/time-resampler.md) down-samples or up-samples values in time.<br/>

It can be used to interpolate values to make a smooth transitions between them. Also it can help you to create a consistent data output.

This will be very handy when using [FFT Cascades](/docs/discussion/fft-cascades.md). Since low frequencies will update slower and high frequencies will update faster.<br/>
See [this](/docs/usage-examples/fft-spectrum.md) example to know more.

### ValueTransformer

[ValueTransformer](/docs/handler-types/value-transformer) lets you transform source values using the available operations.<br/>
For example if the source value is in range [0, 1], this handler will let you transform it to lets say [10, 50].

See [Transforms](/docs/discussions/transforms.md) discussion.

## Image generators

Not all handler provide a numerical value, [Spectrogram](/docs/handler-types/spectrogram.md) and [Waveform](/docs/handler-types/waveform.md) types will generate an image and write it to disk. Mostly, the value of this handler is a string to where that image is located.

!>Note that since these handlers will write the image to disk, this has some side effects on the local drive and performance. See [Performance](/docs/performance.md) discussion.

### Spectrogram

This handler lets you visualize how the value of a band changes in time.<br/>
The source of this handler must be from FFT transform chain, so that source handler has many values.

### Waveform

This handler shows you the waveform of an audio signal.<br/>
Unlike Spectrogram handler, this handler doesn't need a source.

Spectrogram and Waveform handler have some similar parameters. You can check Spectrogram page to see examples with images of these parameters.

## Handler Infos and Section variables

You may want to retrieve some infos about the handlers, some handlers can provide infos about there parameters, or there values. You can get these infos without the need for a child measure, only using section variables.

If the handler can provide these infos, you will find them documented with examples at the end of the page.
