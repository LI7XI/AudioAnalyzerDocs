## Handler Types

<!--

## What is a handler

After we make a [Process]() and specify its [description]():

```ini
Processing=Main
Processing-Main=Channels Auto | Handlers Mainfft, Main_Resampler1 | Filter like-a
```

This Process is going to provide a chunk of audio data, separated into channels (such as left and right for a stereo audio recording).

Handlers will take this data, and process it to extract a specific audio signal from it. Using one of the available [Signal processing]() types.

Then, handlers will generate a value from the processed audio signal that can be used in [Child]() measures.

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

_WIP_
