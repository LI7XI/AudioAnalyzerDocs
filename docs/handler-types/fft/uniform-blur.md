## UniformBlur

Allows you to blur values.

## UniformBlur type Properties

### Jump list

- [Type](#type).
- [Source](#source).
- [Radius](#radius).
- [RadiusAdaptation](#radius-adaptation).
- [Documentation Questions](#q).

---

<p id="type" class="p-title"><b>Type</b><b>UniformBlur</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type UniformBlur
```

---

<p id="source" class="p-title"><b>Source</b><b>Required</b></p>

Name of source handler. Should be name of some handler from FFT transform chain, so that source handler has many values.

?>Note that the handlers arrangement (`BandResampler` → `ValueTransformer` → `TimeResampler` or `TimeResampler` → `ValueTransformer`) will give slightly different results. Mostly i prefer to use `UniformBlur` at the very end.<small id="i1">[1](#q)</small>

_Examples:_

```ini
; Lets say you have this
Handler-FFTHandler=Type FFT
Handler-BandResampler=Type BandResampler | source FFTHandler
Handler-ValueTransformer=Type ValueTransformer | source BandResampler
Handler-TimeResampler=Type TimeResampler | source ValueTransformer

; You can apply UniformBlur on any of the above handlers
Handler-HandlerName=Type UniformBlur | Source TimeResampler
; or
Handler-HandlerName=Type UniformBlur | Source BandResampler
```

---

<p id="radius" class="p-title"><b>Radius</b><b>Default: 1</b></p>

A float number that is bigger or equal to `0`.<br>
Radius of blur for the first cascade.

?>Note that this value is relative to the amount of `Bands` you have in `BandsResampler`, if you are using this handler, and you changed this value, remember to increase it when increasing the `Bands` count, and vice versa.

_Examples:_

```ini
Handler-HandlerName=Type UniformBlur | Radius 3
```

Radius `0`

<img src="docs\handler-types\examples\fft\radius0.PNG" />

Radius `5`

<img src="docs\handler-types\examples\fft\radius5.PNG" />

---

<p id="radius-adaptation" class="p-title"><b>RadiusAdaptation</b><b>Default: 1</b></p>

A float number that is bigger or equal to `0`.<small id="i2">[2](#q)</small><br>
Radius for cascade N is: `Radius * RadiusAdaptation^N`.<small id="i3">[3](#q)</small>

_Examples:_

```ini
Handler-HandlerName=Type UniformBlur | RadiusAdaptation 1
```

## Documentation Questions <i id="q">

[Q1](#i1): Yes, that's what i would do :P. We will discuss if this matters that much in performance later on, because i guess no handler should have raw FFT as it's source except BandResampler.<br/>
[Q2](#i2): Note that RadiusAdaptation doesn't work at all, no matter how much you tweak the values, is it related to using cascades?<br/>
[Q3](#i3): ?<br/>

</i>
