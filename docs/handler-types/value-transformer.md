## ValueTransformer

Allows you to make various changes to values using transform semantics.

## ValueTransformer type Properties

### Jump list

- [Type](#type).
- [Source](#source).
- [Transform](#transform).

---

<p id="type" class="p-title"><b>Type</b><b>ValueTransformer</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type ValueTransformer
```

---

<p id="source" class="p-title"><b>Source</b><b>Required</b></p>

Name of source handler.

_Examples:_

```ini
Handler-HandlerName=Type ValueTransformer | Source SourceHandler
```

---

<p id="transform" class="p-title"><b>Transform</b><b>Default: None</b></p>

Description of transforms that are applied to values.<br/>
See [Transforms]() discussion for full list of possible values.

_Examples:_

```ini
Handler-HandlerName=Type ValueTransformer | Source SourceHandler | Transform Db Map[-70, 0] Clamp
```
