## Filters

Signal filtering is a very complex topic. However, actually using filters in this plugin is simple.

Filter is something, that alters audio stream. Filters usually affect certain frequencies. For example, filters that remove low frequencies, are usually called high pass filters.<br/>
You can look [here](http://jaggedplanet.com/iir/iir-explorer.asp) or [here](https://www.earlevel.com/main/2013/10/13/biquad-calculator-v2/) to see how different filters affect frequencies of the sound.

This plugin have a set of usable filters. They are from two classes: `biquad` filters and `Butterworth` filters.<br/>
All filters have the following syntax: `<FilterName>[<ArgName1> <ArgValue1>, <ArgName2> <ArgValue2>]`.

**Biquad filters:**

- bqHighPass: `bqHighPass[Q <Value>, Freq <Value>]`.
- bqLowPass: `bqLowPass[Q <Value>, Freq <Value>]`.
- bqHighShelf: `bqHighPass[Q <Value>, Freq <Value>, Gain <Value>]`.
- bqLowShelf: `bqLowShelf[Q <Value>, Freq <Value>, Gain <Value>]`.
- bqPeak: `bqPeak[Q <Value>, Freq <Value>, Gain <Value>]`.

`Gain` is defined in decibels.

---

**Butterworth filters:**

- bwLowPass: `bwLowPass[Order <Value>, Freq <Value>]`.
- bwHighPass: `bwHighPass[Order <Value>, Freq <Value>]`.
- bwBandPass: `bwBandPass[Order <Value>, FreqLow <Value>, FreqHigh <Value>]`.
- bwBandStop: `bwBandStop[Order <Value>, FreqLow <Value>, FreqHigh <Value>]`.

Order is limited in range from `1` to `5` due to possible issues with precision. You can use several filters in sequence if you want stronger effect that high orders could provide (see examples below).

---

Besides filter-specific parameters each filter can have a `ForcedGain` parameter (defined in decibels) that controls upper level of the filter.

Traditionally filters like `bqPeak[Q 0.5, Freq 100, Gain 5]` would make frequencies near 100 Hz 5 db stronger. However, my plugin alters this behavior: upper level is kept at 0 db no matter the parameters. However, forcedGain is not compensated for, so if you write bqPeak[Q 0.5, freq 100, gain 5, forcedGain 5] then this filter would behave like traditional biquad peak filter.

I am really not a pro at signal filtering, so if you want to know details of how it works, which filters should you use for which purpose and which values must be in parameters, then just google it. It's also too complex to describe in this documentation.

## Examples:

```ini
Processing-Process=Channels ... | Handlers ... | Filter bwHighPass[Order 3, Freq 2000]
Processing-Process=Channels ... | Handlers ... | Filter bqPeak[Q 0.5, Freq 100, Gain 5]

; You can chain filters
Processing-Process=Channels ... | Handlers ... | Filter bqHighPass[q 0.3, freq 200, forcedGain 3.58] bwLowPass[order 5, freq 10000]
```

If you are interested, standard filters are also defined as a sequence of these `biquad` and `Butterworth` filters.

- `like-a`
- `like-d`

```ini
; This
Processing-Process=Channels ... | Handlers ... | Filter Like-a

; Is a shortcut for this
Processing-Process=Channels ... | Handlers ... | Filter bqHighPass[q 0.3, freq 200, forcedGain 3.58] bwLowPass[order 5, freq 10000]

; Same for this
Processing-Process=Channels ... | Handlers ... | Filter Like-d
; Equals this
Processing-Process=Channels ... | Handlers ... | Filter bqHighPass[q 0.3, freq 200, forcedGain 3.65] bqPeak[q 1.0, freq 6000, gain 5.28] bwLowPass[order 5, freq 10000]
```
