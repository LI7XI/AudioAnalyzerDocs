## Transforms

AudioLevel plugin has a mysterious gain and sensitivity options. You set them to something, and it works. In some way.

But they don't really give you a fine control, and if something doesn't work as you expect, then you can do nothing about it. Transformations solve this problem!

What is a Transformation?<br/>
It's a chain of math operations on a value, that change it.

Available operations and syntax:

- Transform to decibels: `dB`.

  Here is a detailed explication on how decibels work:

  <details>

  If you looked online to know how decibels work, you may not find a clear explanation. It's probably because decibels aren't a unit of measurement.

  When you write "value `x` = 50dB", you are only saying that value `x` is `10^(50 / 10)` times more than a reference value.<br/>
  The issue is that when you write "value `x` = 100dB", you don't write any reference value. And in different context there will be different reference values.

  So, "the loudest usable sound is 0 dB" and "the loudest usable sound is 140 dB" are both valid sentences, because they use different reference values. Also, "the loudest possible usable sound is 70 dB" is also a perfectly valid sentence, because it is applied to value of different type.<br/>
  So, when you see a phrase like "value `x` = 50dB", you can't make much assumptions on whether the value is big or small.

  When working with audio, there are generally two reference values, first: `1` and `the quietest sound a human can hear`.<br/>
  Second is the one you should use when measuring real sound. So when you buy a fan in a store, it usually has some mark like "loudness is 40 dB".

  Now, forget everything from the previous paragraph, as that info is not related to this plugin at all.<br/>
  In computer world there is no possible way to know real sound pressure value or anything related to it, so we can't compare the loudness to `the quietest sound a human can hear`.

  Also, while in reality you can stand near an airplane taking off, get over 200 dB of loud and unbearable sound, in PC world it's impossible: the loudness is limited, you can't make louder sounds than what your speakers/headphones/whatever-you-are-using can create.

  So in computers, `1` is used as a reference value. It is the loudest possible sound in PC.<br/>
  This is not the only place where `1` is used as a reference value, and all such scales have a name "dBFS": decibels relative to full scale. Since `1` is 0 dB, and everything else is less than `1`. All dB values are negative.

  Humans are believed to be able to hear a range of 140 decibels: `the loudest possible sound` is 140 dB louder than `the quietest possible sound`.<br/>
  So this is where claim like `140 dB is dangerous for you` came from: `the quietest possible sound` is the reference point of real life audio decibels, so `the quietest possible sound` is 0 dB, and `the loudest possible sound` then becomes 140 dB.

  Now, there is a bit of misunderstanding happening in the paragraphs above.

  Remember: when you write "value `x` = 50dB", you are only saying that value `x` = `10^(50 / 10)` times more than a reference value.<br/>
  But there is no saying about the dimensions of these values. So, non-linear transformations will give you unexpected results in decibels.<br/>

  And when you operate on _"energy"_, you are in fact dealing with squared values. So when you say that something has amplitude of 10 dB more, it doesn't mean that its energy will be 10 dB more. Its energy will be 20 dB more because energy is squared.

  And loudness is energy. So, for example, when you adjust your PC master loudness in settings to be 10 dB more (even though natively windows doesn't allow you to specify master volume in decibels, but you can imagine it, since 10 dB is "ten times more"), your loudness will become 20 dB more.

  It can very quickly become very confusing, because there are a lot of both linearly-dependent values and squarely-dependent values.

  </details>

- Linear interpolation: `Map(From <Min> : <Max>, to <Min> : <Max>)`.

  !>`From` parameter is required, `to` parameter is optional. If `to` is not present, then source range is transformed in [0, 1] range.

- Limiting value to some range: `Clamp(to <MinValue> : <MaxValue>)`.<br/>
  Parameters are optional. Default `MinValue` is 0, default `MaxValue` is 1.

Transformations are defined as chains. Transformation chain is a sequence of operations separated by a comma.

## Examples

```ini
; Example 1
Handler-HandlerName= ... | Transform dB, Map(From -70 : 0), Clamp
; Example 2
Handler-HandlerName= ... | Transform dB, Map(From -50 : 0, to 5 : 100), Clamp(to 5 : 100)
```

Example 1 is something that audio Peak or Loudness meter could be using.

It will transform values to decibels and then select range [-70, 0] and interpolate and clamp them in [0, 1] range so that the results could be used in rainmeter meters, like Bar or Line.

!>Note that the operation order matters.

For example, let's say you have the following:

```ini
Handler-HandlerName= ... | Transform dB, Map(From -50 : 0), Clamp
```

It will transform values from range [-50, 0] into range [0, 1] and limit the values to this range.<br/>
But if you changed the order:

```ini
Handler-HandlerName= ... | Transform dB, Clamp, Map(From 0: 10)
```

It will work in a completely different way. For example:<br/>

First It will transform all values that are smaller than `0` into `0` and all values that are bigger than `1` into `1`, and then multiply the values by 0.1, resulting in [0, 0.1] range.
