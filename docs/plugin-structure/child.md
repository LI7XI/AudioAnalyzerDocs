## Child Measure

Child measures grab there data from Parent measure.

Usually child measures are used to retrieve numerical values from parent measure, with an optional string value.<br/>
We will show you how to retrieve both [numerical and string](#stringvalue) values as we go on.

## Use cases for Child measures

Child measure can be used for:

- Getting [audio device infos]().
- Providing access to values of handlers in Parent measure.

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

?>This option is optional. If you don't specify it, the plugin will try to find the process with the specified HandlerName.

!>But you have to specify this option only if parent measure has several processes with same handler.

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

This will make sense when we explain [HandlerName]() option.

---

<p style="display: flex; justify-content: space-between;"><b>Channel</b><b>Default: Auto</b></p>

Channel to get data from.

?>This option accepts same Channels specified in [Channels](/docs/plugin-structure/parent?id=parent-channel-para) parameter in Processing option of the Parent. (Correct? or simply i should say, this is same as that parameter?)

Possible Channels (with optional name aliases):

- `Auto` &emsp; &emsp; &emsp; &nbsp; &nbsp; &nbsp; (No alias available)
- `FrontLeft` &emsp; &nbsp; &nbsp; &nbsp; (`Left` or `FL`)
- `FrontRight` &emsp; &nbsp; &nbsp; (`Right` or `FR`)
- `Center` &emsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; (`C`)
- `CenterBack` &emsp; &nbsp; &nbsp; (`CB`)
- `LowFrequency` &emsp; (`LFE`)
- `BackLeft` &emsp; &nbsp; &nbsp; &nbsp; &nbsp; (`BL`)
- `BackRight` &emsp; &nbsp; &nbsp; &nbsp; (`BR`)
- `SideLeft` &emsp; &nbsp; &nbsp; &nbsp; &nbsp; (`SL`)
- `SideRight` &emsp; &nbsp; &nbsp; &nbsp; (`SR`)

_Examples:_

```ini
Channel=Auto
; Or
Channel=FrontLeft
; Or
Channel=FR
```

!>Note that Child measure can only listen to one Channel at a time.

```ini
; Something like this:
Channel=FL, Right
; Is not allowed
```

---

<p style="display: flex; justify-content: space-between;"><b>HandlerName</b><b>Default: None</b></p>

Name of the Handler in Parent measure that will provide values.

_Examples:_

```ini
; Lets say you have this in parent measure
Processing-Main=Channels Auto | Handlers Handler1, handler2

; Then HandlerName would be
HandlerName=Handler1
; Or
HandlerName=Handler2
```

But if there is a HandlerName that is present in 2 processes, then you have to specify [Processing]() option.

_Examples:_

```ini
; Lets say you have this in parent measure
Processing-ProcessA=Channels Auto | Handlers Handler1, handler2
Processing-ProcessB=Channels Auto | Handlers Handler1, handler2

; The plugin won't know which process handler you want this child measure to read values from
; So you have to specify the Processing option in Child measure

Processing=ProcessA
HandlerName=Handler1
; Or
Processing=ProcessB
HandlerName=Handler1

```

---

<p style="display: flex; justify-content: space-between;"><b>Index</b><b>Default: 0</b></p>

Index of value in handler.

Many handlers produce arrays of data, and the `Index` option specifies the index of value in that array.
For example:
Generally, only handlers that transform data from FFT produce arrays of data (Like, if you have handler chain FFT → BandResampler → ValueTransformer → TimeResampler, then all four of these will make data arrays). Independent handlers (like Loudness) usually produce only one value, so any index except for 0 will be invalid.

_Examples:_

```ini
; Lets say you have the following in Parent Measure:
Handler-Mainfft=Type fft | BinWidth 5 | OverlapBoost 10 | CascadesCount 3
Handler-MainResampler=Type BandResampler | Source Mainfft | Bands log 5 20 4000

; Then index can be any where from 0 to the Bands parameter specified MainResampler Handler
Index=0
; Or
Index=13
```

?>In case you have `HandlerName=SomeHandler`, and the type of that `SomeHandler` is `Type Loudness` or Any Other than `Type fft`, setting index option to other than 0 will make this Child measure provide 0 as a value.

_Examples:_

```ini
; Lets say you have the following in Parent Measure:
Handler-loudness=type loudness | transform db
Handler-lodnessPercent=type ValueTransformer | source loudness | transform map[from -50 : 0] clamp

; Setting Index to other than 0
Index=7
; Will make this Child measure provide 0 as a value
```

---

<p style="display: flex; justify-content: space-between;"><b>Transform</b><b>Default: </b></p>

> Specify a transformation to be applied to numerical values of this Child measure.<br/>
> See [Transformations]() discussion for full list of possible values.
>
> _Examples:_
>
> ```ini
> ; Lets say you are getting a value in range [0 to 1] from a handler
> Transform=map[0, 100] clamp
> ; Will convert it to range from 0 to 100
> ```
>
> _Does this option follows the same syntax as the one in ValueTransformer >handler type?_ >_Is the syntax correct? or we should discuss that after writing transformation docs?_

_WIP._

---

<p id="stringvalue" style="display: flex; justify-content: space-between;"><b>StringValue</b><b>Default: Number</b></p>

Determines what kind of value this child measure will return.

- `Number`: Will make this Child measure provide the retrieved String values of handler as a numerical value.(Correct?)
- `Info`: [InfoRequest](#inforequest) option will determine what string value this Child measure will provide

_Examples:_

```ini
StringValue=Number
; makes this child measure return a numerical value based on what it receives from the handler: 0.3, 0.78, etc..
```

Or

```ini
StringValue=Info
; examples of this are WIP
```

---

<p id="inforequest" style="display: flex; justify-content: space-between;"><b>InfoRequest</b><b>Parameters: (See Below)</b></p>

When [StringValue](#stringvalue) is set to `Info`, this option will determine what infos this measure will provide.

?>This is similar to SectionVariables in Parent measure, but without a function call.

_Examples: WIP_

```ini
InfoRequest=current device, description
; Will output...(?)
```
