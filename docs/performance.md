## Performance

While this plugin has a superior "performance to quality" ratio compared to AudioLevel, some care should be taken in few areas.

## FFT

Don't create many of FFT handler type **unless** you have to, it's unnecessary and it will use more performance.

Instead, use 1 FFT handler and let other BandResamplers inherit from it:

```ini
; Don't do this
Unit-UnitName=Channels ... | Handlers FFT1, FFT2, Resampler1(FFT1), Resampler2(FFT2)

; Instead, do this
Unit-UnitName=Channels ... | Handlers FFT, Resampler1(FFT), Resampler2(FFT)
```

## Target Rate

Earlier we said that:

> So if your audio device sample rate is 48000 and TargetRate is 44100, then nothing will happen. If you sampling rate is less than TargetRate then nothing will happen.

Lets explain what that means.

You have `sample rate` (as the input), `target rate` and `final rate`.<br/>
You `final rate` will be as close to the `target rate` as possible with integer division, but it will always be at least as big as `target rate`.

Example 1: `sample rate` is 44100 and your `target rate` is 4000. You `final rate` will be `44100 / 11 == 4009`, because `44100 / 12 == 3675`, and 3675 would be less than your target rate.

Example 2: `sample rate` is 44100 and your `target rate` is 44100. You `final rate` will be 44100.

Example 3: `sample rate` is 44100 and your `target rate` is 48000. You `final rate` will be 44100 (`target rate` will not increase your `sample rate`) .

Example 4: `sample rate` is 88200 and your `target rate` is 48000. You `final rate` will be 88200, because `88200 / 2 == 44100` would be less than your target rate.

The main takeaway from `TargetRate` parameter is to specify only the value that you need. If you need frequencies up to 20 kHz, then you don't have to specify something like 48000 to have some slack.

Though, it's better to have small slack, because resampling to lower sample rate is not free in terms of frequency response: higher frequencies get reduced a bit.

However, if you only need frequencies up to 20 kHz, then 44100 would be enough. If you want to also capture 22 kHz range, then it would be better to have target rate 48000, but for human hearable sound visualization this won't make a difference.

---

In most cases high sample rate is not needed, some times it takes more performance for no quality gain, so it makes sense to down-sample it.

For example, when using FFT then BandResampler, you always specify a frequency range (`FreqMin`, `FreqMax`), which means any frequencies beyond `FreqMax` don't need to be captured.

We can calculate the target rate rate from the frequency range, simply, 100Hz of frequency need at least 200Hz sample rate, 210Hz need at least 420Hz, and so on.

So we can make a variable for the `TargetRate`, and assuming we already have a variable for `FreqMax`, we can calculate the `TargetRate` as the following: `TargetRate=((#FreqMax# * 2) * 1.1)`

Actually we don't even need a variable for that, we can do this directly in the parameter itself:

```ini
Unit-Unitname=Channels ... | Handlers ... | TargetRate ((#FreqMax# * 2) * 1.1) | Filters ...
```

The extra 10% (`* 1.1`) is there to make some room for any possible distortion.

---

But what about other handlers like Loudness or Waveform?<br/>
They will only react to `#FreqMax#` frequency range, if you want them to react to all human hearable frequencies, you could make a new processing unit for them then specify a different `TargeRate`.

## Image meters CPU Usage

This plugin is very light weight, but when using handlers like Spectrogram and Waveform, the CPU usage increases. It's not because this plugin, it's because how rainmeter handles them.

We talked about this earlier in Spectrogram and waveform examples, just to rewind, rainmeter doesn't support in-memory image-transfer, which means it can't read images from Ram.

The only way to display images in image meters is first, writing the image to disk, then making rainmeter read it from there to display it.

You see where is the problem, your disk lifespan will be shortened, and your skin will use higher CPU usage. All due to reading/writing to disk.

There is a temporary solution, which is making a Ram-disk, then making the plugin output the image there, and make the meters read it from there.

## Processing Units

No need to create many processing units, except for using a different filters or a different Target rate.

Instead, you could do everything in one unit. You just need to be clever about arranging your handlers.
