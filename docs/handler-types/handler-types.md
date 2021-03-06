## Handler Types

In this discussion, we will explain what is a handler, and what types are available, what's the difference between the similar ones, and how they related to section variables.

## What is a handler

After we make a [Process](/docs/plugin-structure/parent?id=processing) and specify its [description](/docs/plugin-structure/parent?id=processing-processname):

```ini
Processing=Main
Processing-Main=Channels Auto | Handlers MainFFT, Main_Resampler1 | Filter like-a
```

This Process is going to provide a chunk of audio data, separated into channels (such as left and right for a stereo audio stream).

Handlers will take this data, and process it to extract a specific signal from it. Using one of the [available handler](#available-handlers) types.

```ini
Handler-Main=Type FFT
; Or
Handler-MainFFT=Type Loudness
```

Then, handlers will generate a value from the processed audio signal that can be used in [Child](/docs/plugin-structure/child.md) measures.

## Available Handlers

There are types like `FFT`, `RMS`, `Peak`, `Loudness` and `Waveform` that can be used to extract the desired audio signal.<br/>
There are other types, we will talk about them later.

### FFT

Fast Fourier Transformation is a mathematical formula that samples an audio signal over a period of time and divide it into its frequency components.

?>Note this is the only handler type that provides an [index](/docs/plugin-structure/child?id=index) range for the child measures to use, which mean any handler that is taking data from it will have an index range as well.

#### BandResampler

Handler of type `FFT` is not very useful on it's own, while you still can retrieve values from it, its recommended to use a `BandResampler` after it, and retrieve values from that instead.

It will give you a better control of which frequency bands you want to retrieve and the results will look much better.

#### BandCascadeTransformer

There is a fundamental math issue in FFT algorithm, you can either have a very detailed results that is updating slowly, or fast results that is not detailed enough, or something in between.

The problem is that high frequencies (2000Hz and up) mostly have higher resolution than low and mid frequencies (less than 2000Hz) while still updating faster than mids and lows.

This handler type lets you have high resolution in low frequencies based on an option called [CascadesCount](/docs/handler-types/fft/fft?id=cascades-count) in [FFT](/docs/handler-types/fft/fft) type parameters, then it combines both of low and high frequencies together to have a detailed result through out the entire frequencies range.

See [FFT Cascades](/docs/discussions/fft-cascades.md) discussion.

#### UniformBlur

Since `FFT` handler type provides and index range, and each index corresponds to a specific band value, this handler allows you to blur values between the bands, so that the transition between bands values look smoother.

Before:

<img src="resources\uniform-blur-before.PNG" />

After:

<img src="resources\uniform-blur-after.PNG" />

Examples above were done without using [CubicInterpolation](/docs/handler-types/fft/band-resampler?id=cubic-interpolation) parameter.

?>Note that the results here will vary based on your settings (e.g. frequency range, resolution, bands count, etc).

---

### RMS, Peak and Loudness

At first, these 3 handlers will look similar to each other, but they have few differences:

- `RMS`: Sum squares of values over X ms, find average, get root of result.
- `Peak`: Find maximum value over X ms. If there was a silence and just 1 sound sample near maximum, then result will be near maximum.
- `Loudness`: Sum squares of values over X ms (but separated into smaller blocks), throw out too quiet blocks, find average of remaining blocks. Unlike RMS, it doesn't get root of result, but in case of using decibels this changes a little.

?>Unless you have a specific need for `RMS` or `Peak` handler types, it's recommended to use `Loudness`.

## Value manipulators

Handlers like [TimeResampler](/docs/handler-types/time-resampler.md) or [ValueTransformer](/docs/handler-types/value-transformer) lets you.. _WIP_

## Image generators

Not all handler provide a numerical value, [Spectrogram](/docs/handler-types/spectrogram.md) and [Waveform](/docs/handler-types/waveform.md) types will generate an image and write it to disk. Mostly, the value of this handler is a string to where that image is located.

### Spectrogram

---

### Waveform

<!--


!>Note that first handler of any process must be one of the following types: `FFT`, `RMS`, `Peak`, `Loudness`, `Spectrogram`, or `Waveform`


You can use the raw audio signal that is provided by the [Signal Processors]() as it is, but you can refine it to make a better output using Value manipulators ([Transformations]()).

## Reference

- [What is audio chunk](https://techterms.com/definition/wave)


There are to types of handlers:

- [Signal processors]().
- [Value manipulators]().

### Signal processors

These handler types take the audio data and extract a specific audio signal from it.

!>Note that first handler of any process must be a Signal processors.

```ini
Processing-Main=Channels Auto | Handlers Handler1, Handler2 | Filter Like-a
Handler-Handler1=Type FFT | SetOfOptions
; Or any other "Signal processor" type
Handler-Handler1=Type Loudness | SetOfOptions
Handler-Handler1=Type Peak | SetOfOptions

```

### Value manipulators

These handler types will apply transformation on that raw audio signal.

But what is a transformation?<br/>
It's a chain of math operations on a value, that change it.

_Description of this page is WIP, infos here may not be correct._
_I may even rewrite everything here._

But before we get into them, lets understand [what is a Handler](/docs/handler-types/what-is-a-handler.md). -->
