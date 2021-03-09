## Loudness

### What is Loudness?

Loudness is a way to measure audio levels based on the way humans perceive sound. Different factors influence the way we perceive loudness such as frequency, timbre, the listening environment, ear sensitivity, and more.

### How it works

Signal energy is calculated for blocks of size each (1000/[UpdatesPerSecond](#updates-per-second)<small>[1](#q)</small>) milliseconds. Blocks are averaged across [TimeWindow](#time-window) milliseconds.

However, not all blocks are used, blocks that are almost silent are discarded. But at most [GatingLimit](#gating-limit)\*100% <small>[6](#q)</small> blocks can be discarded.<br/>
This is similar to how EBU R 128 describes loudness metering.<small>[2](#q)</small>

## Loudness type Properties

### Jump list

- [Type](#type).
- [Transform](#transform).
- [UpdatesPerSecond](#updates-per-second).
- [GatingLimit](#gating-limit).
- [TimeWindow](#time-window).
- [GatingDB](#gating-db).
- [IgnoreGatingForSilence](#ignore-gating-for-silence).
- [Usage Examples](#usage-examples).
- [Reference](#reference).

---

<p id="type" class="p-title"><b>Type</b><b>Loudness</b></p>

Specifies the type of the handler

_Examples:_

```ini
Handler-HandlerName=Type Loudness
```

---

<p id="transform" class="p-title"><b>Transform</b><b>Required</b></p>

Description on how to transform values before outputting them. <small>[3](#q)</small><br/>
See [Transformations]() discussion.

_Examples:_

```ini
Handler-HandlerName=Type Loudness | Transform db
```

---

<p id="updates-per-second" class="p-title"><b>UpdatesPerSecond</b><b>Default: 20</b></p>

A Float number in range from `0.01` to `60`.<br/>
Speed at which handler is updating its values.<small>[4](#q)</small>

UpdatesPerSecond 10 would mean that every 100ms value will be updated.<small>[5](#q)</small><br/>
UpdatesPerSecond 1 would mean that value will only be updated once per second.<small>[5](#q)</small><br/>
Higher update rate does not necessary correspond to more accurate perceived loudness. Don't set it too high.

_Examples:_

```ini
Handler-HandlerName=Type Loudness | Transform db | UpdatesPerSecond 30
```

---

<p id="gating-limit" class="p-title"><b>GatingLimit</b><b>Default: 0.5</b></p>

A Float number in range from `0` to `1`.<br/>
Specifies the maximum percentage of discarded blocks.

_Examples:_

```ini
Handler-HandlerName=Type Loudness | Transform db | GatingLimit 0.5
```

---

<p id="time-window" class="p-title"><b>TimeWindow</b><b>Default: 1000</b></p>

Time in milliseconds. A Float number in range from `0.01` to `10000`.<br/>
Specifies size of the block in which loudness is calculated.

_Examples:_

```ini
Handler-HandlerName=Type Loudness | Transform db | TimeWindow 1000
```

---

<p id="gating-db" class="p-title"><b>GatingDB</b><b>Default: -20</b></p>

A Float number in range from `-70` to `0`.<br>
Values that are in decibels less than GatingDB than an average of a block are considered silent and discarded.

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

## Usage Examples

```ini
Handler-HandlerName=Type Loudness | Transform db
```

Or

```ini
Handler-HandlerName=Type Loudness | Transform db | UpdatesPerSecond 20 | GatingLimit 0.5 | TimeWindow 1000 | GatingDB -20 | IgnoreGatingForSilence True
```

## Documentation Questions <i id="q">

Q1: Skin updates per second? or when the plugin is running on a separate thread?<br/>
Q2: I don't know a whole lot about audio topics, so this analogy seems vague to me. Where did you learned about these topics?<br/>
Q3: outputting/providing them to child measure? looks a bit long sentence.<br/>
Q4: Is this related to `Threading` option? What if `Threading=Policy UiThread` and skin `Update=32`?<br/>
Q5: wut? i mean how to calculated this? 60 is the equivalent of skin `Update=16`?<br/>
Q6: sorcery formula. I mean i'm not good at math, i can't read it.
</i>

## Reference

- [What is Loudness meter](https://iconcollective.edu/loudness-meters/)
