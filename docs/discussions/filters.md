## Filters

!>Note: this is intended for advanced usage and it's absolutely optional. Feel free to skip it unless you know about signal filtering.

Audio filters is something, that alters audio stream. Filters usually affect certain frequencies. For example, filters that remove low frequencies, are usually called high pass filters.<br/>
You can look [here](http://jaggedplanet.com/iir/iir-explorer.asp) or [here](https://www.earlevel.com/main/2013/10/13/biquad-calculator-v2/) to see how different filters affect frequencies of the sound.

This plugin have a set of usable filters. They are from two classes: [Biquad](https://en.wikipedia.org/wiki/Digital_biquad_filter) filters and [Butterworth](https://en.wikipedia.org/wiki/Butterworth_filter) filters.<br/>
All filters have the following syntax: First we write the parameter name (`Filter`), then the word `Custom`, then the filter itself:

```ini
Unit-UnitName=Channels ... | Handlers ... | Filter Custom <FilterName>(<ArgName1> <ArgValue1>, <ArgName2> <ArgValue2>)
```

**Biquad filters:**

- bqHighPass: `bqHighPass(Q <Value>, Freq <Value>)`.
- bqLowPass: `bqLowPass(Q <Value>, Freq <Value>)`.
- bqHighShelf: `bqHighPass(Q <Value>, Freq <Value>, Gain <Value>)`.
- bqLowShelf: `bqLowShelf(Q <Value>, Freq <Value>, Gain <Value>)`.
- bqPeak: `bqPeak(Q <Value>, Freq <Value>, Gain <Value>)`.

`Gain` is defined in decibels.

---

**Butterworth filters:**

- bwLowPass : `bwLowPass(Order <Value>, Freq <Value>)`.
- bwHighPass: `bwHighPass(Order <Value>, Freq <Value>)`.
- bwBandPass: `bwBandPass(Order <Value>, FreqLow <Value>, FreqHigh <Value>)`.
- bwBandStop: `bwBandStop(Order <Value>, FreqLow <Value>, FreqHigh <Value>)`.

Allowed range of `Order` argument is limited to [1, 5] due to possible issues with precision.<br/>
You can use several filters in sequence if you want stronger effect that high orders could provide (see [examples](#examples) below).

---

Besides filter-specific parameters, each filter can have a `ForcedGain` parameter (specified in decibels) that controls upper level of the filter.

Traditionally filters like `bqPeak(Q 0.5, Freq 100, Gain 5)` would make frequencies near 100 Hz 5 db stronger.<br/>
However, the plugin alters this behavior: upper level is kept at 0 db no matter the parameters.

Although, forcedGain is not compensated for, so if you write `bqPeak[Q 0.5, freq 100, gain 5, forcedGain 5]` then this filter would behave like traditional Biquad peak filter.

## Examples

```ini
Unit-UnitName=Channels ... | Handlers ... | Filter Custom bwHighPass(Order 3, Freq 2000)
Unit-UnitName=Channels ... | Handlers ... | Filter Custom bqPeak(Q 0.5, Freq 100, Gain 5)

; You can chain a comma-separated filters
Unit-UnitName=Channels ... | Handlers ... | Filter Custom bqHighPass(Q 0.3, Freq 200, ForcedGain 3.58), bwLowPass(Order 5, Freq 10000)
```

If you are interested, standard filters are also defined as a sequence of these `biquad` and `Butterworth` filters.

- `like-a`
- `like-d`

Think of them as a preset. Also no need to use the word `Custom` before them.

```ini
; This
Unit-UnitName=Channels ... | Handlers ... | Filter Like-a

; Is a shortcut for this
Unit-UnitName=Channels ... | Handlers ... | Filter Custom bqHighPass(Q 0.3, Freq 200, ForcedGain 3.58), bwLowPass(Order 5, Freq 10000)

; Same for this
Unit-UnitName=Channels ... | Handlers ... | Filter Like-d
; Equals this
Unit-UnitName=Channels ... | Handlers ... | Filter Custom bqHighPass(Q 0.3, Freq 200, forcedGain 3.65), bqPeak(Q 1.0, Freq 6000, Gain 5.28), bwLowPass(Order 5, Freq 10000)
```
