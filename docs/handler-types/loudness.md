## Loudness

### What is Loudness?

Loudness is a way to measure audio levels based on the way humans perceive sound. Different factors influence the way we perceive loudness such as frequency, timbre, the listening environment, ear sensitivity, and more.

### How it works

Signal energy is calculated for blocks of size each (1000/[UpdateRate](#update-rate)) milliseconds. Blocks are averaged across [TimeWindow](#time-window) milliseconds.

However, not all blocks are used, blocks that are almost silent are discarded. You can determine the amount of discarded blocks using [GatingLimit](#gating-limit) option.<br/>
This is similar to how [EBU R 128](https://en.wikipedia.org/wiki/EBU_R_128#EBU_Mode_metering) describes loudness metering.

Worth noting that `UpdateRate` is independent from how often the handler updates.<br/>
Handler value will be updated at the same rate as all other handlers, but blocks inside it are updated at independent rate.

If handlers are updated at lower rate than `UpdateRate`, then you obviously won't be able to receive value for each block, but the calculations inside handler will be as accurate as specified in `UpdateRate`.

## Loudness Parameters

### Jump list

- [Type](#type)
- [Transform](#transform)
- [UpdateRate](#update-rate)
- [GatingLimit](#gating-limit)
- [TimeWindow](#time-window)
- [GatingDB](#gating-db)
- [IgnoreGatingForSilence](#ignore-gating-for-silence)
- [Usage](#usage)

---

<p id="type" class="p-title"><b>Type</b><b>Loudness</b></p>

Specifies the type of the handler

_Examples:_

```ini
Handler-HandlerName=Type Loudness
```

---

<p id="transform" class="p-title"><b>Transform</b><b>Default: None</b></p>

Description on how to transform values before outputting them. When using this handler it's recommended to transform values to decibels to have the expected results.<br/>
See [Transforms](/docs/discussions/transforms.md) discussion.

_Examples:_

```ini
Handler-HandlerName=Type Loudness | Transform db
```

---

<p id="update-rate" class="p-title"><b>UpdateRate</b><b>Default: 20</b></p>

A Float number in range from `0.01` to `60`.<br/>
Speed at which handler is updating its values.

UpdateRate 10 would mean that every 100ms value will be updated.
UpdateRate 1 would mean that value will only be updated once per second.
Higher update rate does not necessary correspond to more accurate perceived loudness. Don't set it too high.

_Examples:_

```ini
Handler-HandlerName=Type Loudness | Transform db | UpdateRate 30
```

---

<p id="gating-limit" class="p-title"><b>GatingLimit</b><b>Default: 0.5</b></p>

A Float number in range from `0` to `1`.<br/>
Specifies the maximum percentage of discarded blocks.

If `GatingLimit` is 0.0, then all blocks will always be used.
If `GatingLimit` is 0.5, then half the blocks can be discarded because of gating.
If `GatingLimit` is 1.0, then in some cases handler will only look at one value to describe the loudness.

_Examples:_

```ini
Handler-HandlerName=Type Loudness | Transform db | GatingLimit 0.3
```

---

<p id="time-window" class="p-title"><b>TimeWindow</b><b>Default: 1000</b></p>

Time in milliseconds. A Float number in range from `0.01` to `10000`.<br/>
Specifies size of the block in which loudness is calculated.

_Examples:_

```ini
Handler-HandlerName=Type Loudness | Transform db | TimeWindow 500
```

---

<p id="gating-db" class="p-title"><b>GatingDB</b><b>Default: -20</b></p>

A Float number in range from `-70` to `0`.<br>
Values in decibels that are less than GatingDB then an average of a block is considered silent and discarded.

_Examples:_

```ini
Handler-HandlerName=Type Loudness | Transform dB | GatingDB -20
```

---

<p id="ignore-gating-for-silence" class="p-title"><b>IgnoreGatingForSilence</b><b>Default: True</b></p>

When you are listening to something and there was small silent moment, perceived loudness is still high. However, when you turn it off, perceived loudness changes instantly, unlike averaging with gating.

IgnoreGatingForSilence ensures that if there is not just something silent in the audio stream, but an absence of any sounds, them loudness value goes down quickly.

_Examples:_

```ini
Handler-HandlerName=Type Loudness | Transform db | IgnoreGatingForSilence True
```

## Usage

Check out [this](/docs/usage-examples/loudness.md) example to see how this handler is used.
