## RMS

Root mean square or simply RMS.<br/>
Measures energy of the signal over a period of time. It used to be the best way to approximate loudness.

But now there is a better dedicated [Loudness](/docs/handler-types/signal-processors/loudness.md) handler, so now you probably don't need this handler for that purpose.

## RMS type Properties

### Jump list

- [Type](#type).
- [Transform](#transform).
- [UpdateInterval](#update-interval).
- [Attack](#attack).
- [Decay](#decay).
- [Usage Examples](#usage-examples).

---

<p id="type" class="p-title"><b>Type</b><b>RMS</b></p>

Specifies the type of the handler

_Examples:_

```ini
Handler-HandlerName=Type RMS
```

---

<p id="transform" class="p-title"><b>Transform</b><b>Required</b></p>

Description on how to transform values before outputting them.<br/>
See [Transformations]() discussion.

_Examples:_

```ini
Handler-HandlerName=Type RMS | Transform db
```

---

<p id="update-interval" class="p-title"><b>UpdateInterval</b><b>Default: 10</b></p>

A float number that is greater than `0`.<br/>
Time in milliseconds of block in which maximum is found.

_Examples:_

```ini
Handler-HandlerName=Type RMS | Transform db | UpdateInterval 10
```

---

<p id="attack" class="p-title"><b>Attack</b><b>Default: 0</b></p>

Time in milliseconds. A float number that is greater than `0`.<br/>

When not zero, smooths the result in such a way that it takes roughly Attack milliseconds to raise from one stable level to another. Very roughly.<br/>
It may be useful when values are updating too quickly.

_Examples:_

```ini
Handler-HandlerName=Type RMS | Transform db | Attack 40
```

---

<p id="decay" class="p-title"><b>Decay</b><b>Default: <code>Value of Attack</code></b></p>

Time in milliseconds. A float number that is greater than `0`.<br/>

When not zero, smooths the result in such a way that it takes roughly Decay milliseconds to fall from one stable level to another. Very roughly.<br/>
It may be useful when values are updating too quickly.

_Examples:_

```ini
Handler-HandlerName=Type RMS | Transform db | Decay 90
```

?>When `Decay` is not specified, but `Attack` is specified, `Decay` will be equal to `Attack`

```ini
Handler-HandlerName=Type RMS | Transform db | Attack 40
; Here Decay will equal to 40 as well.
```

## Usage Examples

```ini
Handler-HandlerName=Type RMS | Transform db
```

Or

```ini
Handler-HandlerName=Type RMS | Transform db | UpdateInterval 10 | Attack 40 | Decay 90
```
