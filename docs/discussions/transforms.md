## Transforms

AudioLevel plugin has mysterious gain, sensitivity options. You set them to something, and it works. In some way.

But they don't really give you a fine control, and if something doesn't work as you expect, then you can do nothing about it. Transformations solve this problem!

What is a Transformation?<br/>
It's a chain of math operations on a value, that change it.

Available operations and syntax:

- Transform to decibels: `DB`.
- Linear interpolation: `Map[from <Min> : <Max>, to <Min> : <Max>]`.

  !>`From` parameter is required, `to` parameter is optional. If `to` is not present, then source range is transformed in [0, 1] range.

- Limiting value to some range: `Clamp[Min <MinValue>, Max <MaxValue>]`.<br/>
  Parameters are optional. Default `MinValue` is 0, default `MaxValue` is 1.

Transformations are defined as chains. Transformation chain is a sequence of operations separated by spaces.

Example: `DB Map[from -70 : 0] Clamp`.(?, does the operation order matter? what if clamp came before map or db?)<br/>
Example above is something that audio peak or loudness meter could be using.

It will transform values to decibels and then select range [-70, 0] and interpolate and clamp it in such a way that the result could be used in rainmeter meters, like Bar or Line.

_More examples are WIP, also idk how decibels work so i will read about them before making examples._
