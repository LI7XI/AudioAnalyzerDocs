## TimeResampler

Downsamples or upsamples values in time.

If your update rate is too low, the handler will extrapolate values so that they will look smoother.

If your update rate is too high, the handler will smooth the values out so that they don't look too sharp and you don't lose data by just throwing excessive values away.

## TimeResampler type Properties

### Jump list

- [Type](#type).
- [Source](#source).
- [Granularity](#granularity).
- [Attack](#attack).
- [Decay](#decay).
- [Transform](#transform).

<p id="type" class="p-title"><b>Type</b><b>TimeResampler</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type TimeResampler
```

---

<p id="source" class="p-title"><b>Source</b><b>Required</b></p>

Name of source handler.

_Examples:_

```ini
Handler-HandlerName=Type TimeResampler | Source SourceHandler
```

---

<p id="granularity" class="p-title"><b>Granularity</b><b>Default: 16.667</b></p>

A float number that is bigger than `0`.<br>
Time in milliseconds of one block that the handler will produce.

No matter how fast source handler is updated, this handler will always consistently produce one data block in Granularity milliseconds.

See [Tips]() discussion.

_Examples:_

```ini
Handler-HandlerName=Type TimeResampler | Source SourceHandler | Granularity 33.2
```

---

<p id="attack" class="p-title"><b>Attack</b><b>Default: 0</b></p>

A float number that is bigger than `0`.<br>
A parameter for filter that smooths values.

This is the same parameter as `FFTAttack` in AudioLevel plugin, except AudioLevel don't smooth values when they are updating very rarely.
Attack only affects how values are smoothed when they are increasing.

_Examples:_

```ini
Handler-HandlerName=Type TimeResampler | Source SourceHandler | Attack 40
```

---

<p id="decay" class="p-title"><b>Decay</b><b>Default: <code>Value of Attack parameter</code></b></p>

A float number that is bigger than `0`.<br>
Same as `Attack` but only affects how values are decreasing.

_Examples:_

```ini
Handler-HandlerName=Type TimeResampler | Source SourceHandler | Decay 110
```

---

<p id="transform" class="p-title"><b>Transform</b><b>Default: None</b></p>

Description of transforms that are applied to values after filtering.<br/>
See [Transforms]() discussion for full list of possible values.

_Examples:_

```ini
Handler-HandlerName=Type TimeResampler | Source SourceHandler | Transform Db Map[-70, 0] Clamp
```
