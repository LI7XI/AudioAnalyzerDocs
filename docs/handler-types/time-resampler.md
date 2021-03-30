## TimeResampler

Downsamples or upsamples values in time.

If your update rate is too low, the handler will extrapolate values so that they will look smoother.

If your update rate is too high, the handler will smooth the values out so that they don't look too sharp and you don't lose data by just throwing excessive values away.

## TimeResampler Parameters

### Jump list

- [Type](#type)
- [UpdateRate](#update-rate)
- [Attack](#attack)
- [Decay](#decay)
- [Transform](#transform)
- [Usage](#usage)

<p id="type" class="p-title"><b>Type</b><b>TimeResampler</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type TimeResampler
```

---

<p id="update-rate" class="p-title"><b>UpdateRate</b><b>Default: 16.667</b></p>

A float number that is bigger than `0`.<br>
Time in milliseconds of one block that the handler will produce.

No matter how fast source handler is updated, this handler will always consistently produce one data block in `UpdateRate` milliseconds.

See [Tips](/docs/tips-code?id=handlers-arrangement) discussion.

_Examples:_

```ini
Handler-HandlerName=Type TimeResampler | UpdateRate 33.2
```

---

<p id="attack" class="p-title"><b>Attack</b><b>Default: 0</b></p>

A float number that is bigger than `0`.<br>

This parameter is similar to `FFTAttack` in AudioLevel plugin, except AudioLevel don't smooth values when they are updating very rarely.<br/>
Attack only affects how values are smoothed when they are increasing.

_Examples:_

```ini
Handler-HandlerName=Type TimeResampler | Attack 40
```

---

<p id="decay" class="p-title"><b>Decay</b><b>Default: <code>Value of Attack</code></b></p>

A float number that is bigger than `0`.<br>
Same as `Attack` but only affects how values are decreasing.

_Examples:_

```ini
Handler-HandlerName=Type TimeResampler | Decay 110
```

?>When `Decay` is not specified, but `Attack` is specified, `Decay` will be equal to `Attack`

```ini
Handler-HandlerName=Type TimeResampler | Attack 40
; Here Decay will equal to 40 as well.
```

---

<p id="transform" class="p-title"><b>Transform</b><b>Default: None</b></p>

Description of transforms that are applied to values after filtering.<br/>
See [Transforms](/docs/discussions/transforms.md) discussion for full list of possible values.

_Examples:_

```ini
Handler-HandlerName=Type TimeResampler | Transform dB, Map(-70 : 0), Clamp
```

## Usage

Check out [this](/docs/usage-examples/fft-spectrum.md) example to see how this handler is used.
