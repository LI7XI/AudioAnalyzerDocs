## Child Measure

Child measures grab there data from Parent measure.

Usually child measures are used to retrieve numerical values from parent measure, with an optional string value.<br/>
We will show you how to retrieve both [numerical and string](#stringvalue) values as we go on.

## Use cases for Child measures

You can use Child measure for:

- Getting [audio device infos]().
- Getting processed audio data and return it as a [ranged number]() (e.g from 0 to 1) to be used in your skin.

## Available Options

<p style="display: flex; justify-content: space-between;"><b>Parent</b><b>Required</b></p>

Name of parent measure to retrieve data from.

_Examples:_

```ini
Parent=MeasureAudio
```

---

<p style="display: flex; justify-content: space-between;"><b>Processing</b><b>Default: None</b></p>

Name of the process to get data from.

?>This option is optional. If you don't specify it, the plugin will try to find processing with specified HandlerName.

!>But you have to specify it only if parent measure has several processings with same handler, so that HandlerName doesn't uniquely identify the handler(?, after the 'so that' part).

_Examples:_

```ini
; If you have this in parent measure, 2 proesses has same hander name
Processing-Process1=Channels Auto | Handlers SameHandlerName
Processing-Process2=Channels Auto | Handlers SameHandlerName

; Then you have to Specify which process handler you want this child measure to read values from
Processing=Process1
; Or
Processing=Process2
```

This will make sense when we explain [ValueID]() option.

---

<p style="display: flex; justify-content: space-between;"><b>Index</b><b>Default: 0</b></p>

Index of value in handler.

An example of a value index would be a band in handler of type [fft]().

_Examples:_

```ini
Index=0
```

_Is this option always avaliable in every child measure?_
_What if ValueID was set to Loudness handler type, and this option was set to other than 0? will the child still retrieve values?_

---

<p style="display: flex; justify-content: space-between;"><b>Transform</b><b>Default: </b></p>

Specify a transformation to be applied to numerical values of this Child measure.<br/>
See [Transformations]() discussion for full list of possible values.

_Examples:_

```ini
; Lets say you are getting a value in range [0 to 1] from a handler
Transform=map[0, 100] clamp
; Will convert it to range from 0 to 100
```

_Does this option follows the same syntax as the one in ValueTransformer handler type?_
_Is the syntax correct? or we should discuss that after writing transformation docs?_

---

<p id="stringvalue" style="display: flex; justify-content: space-between;"><b>StringValue</b><b>Default: Number</b></p>

Determines what kind of value this child measure will return.

- `Number`: String values of measure match number value.(?)
- `Info`: [InfoRequest](#inforequest) option will determine what string value this measure will return

_Examples:_

```ini
StringValue=Number
; makes this child measure return a numerical value based on what it receives from the handler: 0.3, 40, etc..
; (?, is explanation correct?)
```

Or

```ini
StringValue=Info
; examples of this are WIP
```

_What if both of `StringValue=String` and `ValueID=HandlerName` was specified?_<br/>
_This option lacks some documentations._

---

<p id="inforequest" style="display: flex; justify-content: space-between;"><b>InfoRequest</b><b>Parameters: (See Below)</b></p>

When [StringValue](#stringvalue) is set to `Info`, this option will determine what infos this measure will provide.

?>This is similar to SectionVariables in Parent measure, but without a function call.

- ``:
- ``:

_Examples:_

```ini
InfoRequest=current device, description
; Will output...(?)
```

---

<p style="display: flex; justify-content: space-between;"><b></b><b>Default: </b></p>

- ``:
- ``:

_Examples:_

```ini

```

---
