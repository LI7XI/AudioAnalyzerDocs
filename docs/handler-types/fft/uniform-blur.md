## UniformBlur

Allows you to blur values between bands.

!>The source of this handler should be from [FFT](/docs/handler-types/fft/fft.md) transform chain, so that source handler has many values.

## UniformBlur Parameters

### Jump list

- [Type](#type)
- [Radius](#radius)
- [Usage](#usage)

---

<p id="type" class="p-title"><b>Type</b><b>UniformBlur</b></p>

Specifies the type of the handler.

_Examples:_

```ini
Handler-HandlerName=Type UniformBlur
```

---

<p id="radius" class="p-title"><b>Radius</b><b>Default: 1</b></p>

A float number that is bigger or equal to `1`.<br>
Radius of blur for the first cascade.

?>This parameter is relative to the amount of `Bands` you have in `BandsResampler`, remember to increase it when increasing the `Bands` count, and vice versa.

_Examples:_

```ini
Handler-HandlerName=Type UniformBlur | Radius 2.5
```

---

## Usage

Check out [this](/docs/usage-examples/fft-spectrum.md) example to see how this handler is used.
