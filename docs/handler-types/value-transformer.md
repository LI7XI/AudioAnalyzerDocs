## ValueTransformer

Allows you to make various changes to values using transform semantics.

## ValueTransformer Parameters

### Jump list

- [Type](#type)
- [Transform](#transform)
- [Usage](#usage)

---

<p id="type" class="p-title"><b>Type</b><b>ValueTransformer</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type ValueTransformer
```

---

<p id="transform" class="p-title"><b>Transform</b><b>Default: None</b></p>

Description of transforms that are applied to values.<br/>
See [Transforms](/docs/discussions/transforms.md) discussion for full list of possible values.

_Examples:_

```ini
Handler-HandlerName=Type ValueTransformer | Transform dB, Map(From -70 : 0), Clamp
```

## Usage

Check out [this](/docs/usage-examples/loudness.md) example to see how this handler is used.
