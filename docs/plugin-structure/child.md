## Child Measure

Child measures grab there data from Parent measure.

Usually child measures are used to retrieve numerical values from parent measure, with an optional string value.<br/>
We will show you how to retrieve both numerical and string values as we go on.

## Use cases for Child measures

You can use Child measure for:

- Getting [audio device infos]().
- Getting processed audio data and return it as a [ranged number]() (e.g from 0 to 1) to be used in your skin.

## Available Options

<div style="display: flex; justify-content: space-between;"><b>Parent</b><b>Required</b></div>

Name of parent measure to retrieve data from.

_Examples:_

```ini
Parent=MeasureAudio
```

---

<div style="display: flex; justify-content: space-between;"><b>Processing</b><b>Default: None</b></div>

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

<div style="display: flex; justify-content: space-between;"><b>Index</b><b>Default: 0</b></div>

Index of value in handler.

An example of a value index would be a band in handler of type [fft]().

_Examples:_

```ini
Index=0
```

_Is this option always avaliable in every child measure?_
_What if ValueID was set to Loudness handler type, and this option was set to other than 0? will the child still retrieve values?_

---

<div style="display: flex; justify-content: space-between;"><b></b><b>Default: </b></div>

- ``:
- ``:

_Examples:_

```ini

```

---

<div style="display: flex; justify-content: space-between;"><b></b><b>Default: </b></div>

- ``:
- ``:

_Examples:_

```ini

```

---
