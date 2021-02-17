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
