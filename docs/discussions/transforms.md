## Transforms

AudioLevel plugin has mysterious gain, sensitivity options. You set them to something, and it works. In some way.

But they don't really give you a fine control, and if something doesn't work as you expect, then you can do nothing about it. Transformations solve this problem!

What is a Transformation?<br/>
It's a chain of math operations on a value, that change it.

Available operations and syntax:

- Transform to decibels: `dB`.
- Linear interpolation: `Map(From <Min> : <Max>, to <Min> : <Max>)`.

  !>`From` parameter is required, `to` parameter is optional. If `to` is not present, then source range is transformed in [0, 1] range.

- Limiting value to some range: `Clamp(Min <MinValue>, Max <MaxValue>)`.<br/>
  Parameters are optional. Default `MinValue` is 0, default `MaxValue` is 1.

Transformations are defined as chains. Transformation chain is a sequence of operations separated by a comma.

## Examples

```ini
; Example 1
Handler-HandlerName= ... | Transform dB, Map(From -70 : 0), Clamp
; Example 2
Handler-HandlerName= ... | Transform dB, Map(From -50 : 0, to 5 : 100), Clamp(Min 5, Max 100)
```

Example 1 is something that audio Peak or Loudness meter could be using.

It will transform values to decibels and then select range [-70, 0] and interpolate and clamp them in [0, 1] range so that the results could be used in rainmeter meters, like Bar or Line.

!>Note that the operation order matters.

For example, let's say you have the following:

```ini
Handler-HandlerName= ... | Transform dB, Map(From -50 : 0), Clamp
```

It will transform values from range [0, 10] info range [0, 1] and limit the values to this range<br/>
But if you changed the order:

```ini
Handler-HandlerName= ... | Transform dB, Clamp, Map(From 0: 10)
```

It will work in a completely different way. For example:<br/>

First It will transform all values that are smaller than 0 into 0 and all values that are bigger than 1 into 1, and then multiply the values by 0.1, resulting in [0, 0.1] range.

_More examples are WIP, also idk how decibels work so i will read about them before making examples._
