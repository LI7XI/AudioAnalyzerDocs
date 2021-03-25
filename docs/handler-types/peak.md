## Peak

Maximum of an "absolute" value of the signal a over period of time.<br/>
Use when you need to know if there was any sound on not, or when detecting possible clipping.

## Peak Parameters

### Jump list

- [Type](#type)
- [Transform](#transform)
- [UpdateRate](#update-rate)
- [Attack](#attack)
- [Decay](#decay)
- [Usage](#usage)

---

<p id="type" class="p-title"><b>Type</b><b>Peak</b></p>

Specifies the type of the handler

_Examples:_

```ini
Handler-HandlerName=Type Peak
```

---

<p id="transform" class="p-title"><b>Transform</b><b>Defaults: None</b></p>

Description on how to transform values before outputting them. When using this handler it's recommended to transform values to decibels to have the expected results.<br/>
See [Transforms](/docs/discussions/transforms.md) discussion.

_Examples:_

```ini
Handler-HandlerName=Type Peak | Transform db
```

---

<p id="update-rate" class="p-title"><b>UpdateRate</b><b>Default: 10</b></p>

A float number that is greater than `0`.<br/>
Time in milliseconds of block in which maximum is found.

_Examples:_

```ini
Handler-HandlerName=Type Peak | Transform db | UpdateRate 5
```

---

<p id="attack" class="p-title"><b>Attack</b><b>Default: 0</b></p>

Time in milliseconds. A float number that is greater than `0`.<br/>

When not zero, smooths the result in such a way that it takes roughly Attack milliseconds to raise from one stable level to another. Very roughly.<br/>
It may be useful when values are updating too quickly. This parameter is similar to AudioLevel `PeakAttack`.

_Examples:_

```ini
Handler-HandlerName=Type Peak | Transform db | Attack 10
```

---

<p id="decay" class="p-title"><b>Decay</b><b>Default: <code>Value of Attack</code></b></p>

Time in milliseconds. A float number that is greater than `0`.<br/>

When not zero, smooths the result in such a way that it takes roughly `Decay` milliseconds to fall from one stable level to another. Very roughly.<br/>
It may be useful when values are updating too quickly. This parameter is similar to AudioLevel `PeakDecay`.

_Examples:_

```ini
Handler-HandlerName=Type Peak | Transform db | Decay 30
```

?>When `Decay` is not specified, but `Attack` is specified, `Decay` will be equal to `Attack`

```ini
Handler-HandlerName=Type Peak | Transform db | Attack 10
; Here Decay will equal to 40 as well.
```

## Usage

Check out [this](/docs/usage-examples/peak.md) example to see how this handler is used.
