## Child Measure

Child measures are used to retrieve numerical values from parent measure, with an optional string value.<br/>
We will show you how to retrieve both [numerical and string](#string-value) values as we go on.

## Jump list

- [Parent](#parent).
- [HandlerName](#handler-name).
- [Processing](#processing).
- [Channel](#channel).
- [Index](#index).
- [Transform](#transfrom).
- [StringValue](#string-value).
- [InfoRequest](#info-request).

## Available Options

<p id="parent" class="p-title"><b>Parent</b><b>Required</b></p>

Name of parent measure.

_Examples:_

```ini
Parent=MeasureAudio
```

---

<p id="handler-name" class="p-title"><b>HandlerName</b><b>Default: None</b></p>

Name of the Handler in Parent measure that will provide values.

_Example:_

```ini
; Lets say you have this in parent measure
ProcessingUnits-Main=Channels Auto | Handlers Handler1, handler2

; Then HandlerName would be
HandlerName=Handler1
; Or
HandlerName=Handler2
```

But if there is a HandlerName that is present in 2 processes Like this:

```ini
ProcessingUnits-UnitA=Channels Auto | Handlers SameHandlerName | ...
ProcessingUnits-UnitB=Channels Auto | Handlers SameHandlerName | ...
```

Then you have to specify [Processing](#processing) option.

---

<p id="processing" class="p-title"><b>Processing</b><b>Default: None</b></p>

Name of the process that have the handler specified in `HandlerName` option.

?>This option is optional. If you don't specify it, the plugin will automatically try to find the process with the specified `HandlerName`.

Child measure retrieve data from a specific handler. Usually it's enough to specify `HandlerHame` option to find that handler. However, it's possible to have same handler name in several processes. For example:

```ini
ProcessingUnits-UnitA=Channels Auto | Handlers SameHandlerName | ...
ProcessingUnits-UnitB=Channels Auto | Handlers SameHandlerName | ...
```

In such case, it's not clear which handler this Child measure should use.<br/>
Here is where `Processing` option comes in, it allows you to specify exactly from which Process you want this handler. Like so:

```ini
; If you have this in parent measure, 2 proesses has same hander name
ProcessingUnits-UnitA=Channels Auto | Handlers SameHandlerName | ...
ProcessingUnits-UnitB=Channels Auto | Handlers SameHandlerName | ...

; Then you can specify from which process you want the handler
Processing=UnitA
; Or
Processing=UnitB
```

---

<p id="channel" class="p-title"><b>Channel</b><b>Default: Auto</b></p>

Channel to get data from.

?>This option accepts same Channels specified in [Channels](/docs/plugin-structure/parent?id=parent-channel-para) parameter in Processing option of the Parent.

Possible Channels (with optional name aliases):

<ul class="channel-list">
  <li><code>Auto</code><span>(No alias available)</span></li>
  <li><code>FrontLeft</code><span>(<code>Left</code> or <code>FL</code>)</span></li>
  <li><code>FrontRight</code><span>(<code>Right</code> or <code>FR</code>)</span></li>
  <li><code>Center</code><span>(<code>C</code>)</span></li>
  <li><code>CenterBack</code><span>(<code>CB</code>)</span></li>
  <li><code>LowFrequency</code><span>(<code>LFE</code>)</span></li>
  <li><code>BackLeft</code><span>(<code>BL</code>)</span></li>
  <li><code>BackRight</code><span>(<code>BR</code>)</span></li>
  <li><code>SideLeft</code><span>(<code>SL</code>)</span></li>
  <li><code>SideRight</code><span>(<code>SR</code>)</span></li>
</ul>

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

<p id="index" class="p-title"><b>Index</b><b>Default: 0</b></p>

Index of value in handler.

Many handlers produce arrays of data, and the `Index` option specifies the index of value in that array.

For example: Generally, only handlers that transform data from FFT produce arrays of data (Like, if you have this handler chain: `FFT` → `BandResampler` → `ValueTransformer` → `TimeResampler`, then all four of these will make data arrays).

Independent handlers (like Loudness) usually produce only one value, so any index except for 0 will be invalid.

_Examples:_

```ini
; Lets say you have the following in Parent Measure:
Unit-Main=Channels ... | Handlers MainFFT, MainResampler(MainFFT) | ...
Handler-MainFFT=Type FFT | BinWidth 5 | OverlapBoost 10 | CascadesCount 3
Handler-MainResampler=Type BandResampler | Bands Log(Count 5, Min 20, Max 4000)

; Then index can be any where from 0 to the BandsCount - 1
Index=0
; Or
Index=4
```

?>In case you have `HandlerName=SomeHandler`, and the type of that `SomeHandler` is `Type Loudness` or **any other** than `Type fft`, setting index option to other than 0 will make this Child measure provide 0 as a value. For example:

```ini
; Lets say you have the following in Parent Measure:
Unit-Main=Channels ... | Handlers Loudness, LoudnessPercent(Loudness) | ...
Handler-Loudness=Type Loudness | Transform dB
Handler-LoudnessPercent=Type ValueTransformer | Transform Map(From -50 : 0), Clamp

; Setting Index to other than 0
Index=7
; Will make this Child measure provide 0 as a value
```

---

<p id="transform" class="p-title"><b>Transform</b><b>Default: </b></p>

Specify a transformation to be applied to numerical values of this Child measure.<br/>
See [Transforms](/docs/discussions/transforms.md) discussion for full list of possible values.

_Examples:_

```ini
; Lets say you are getting a value in range 0 to 1 from a handler
Transform=Map(From 0 : 1, to 0 : 50), Clamp(Min 0, Max 50)
; Will convert it to range from 0 to 50
```

---

<p id="string-value" class="p-title"><b>StringValue</b><b>Default: Number</b></p>

Determines what kind of value this child measure will provide.

- `Number`: Child measure will provide the retrieved values from handler.
- `Info`: [InfoRequest](#info-request) option will determine what string value this Child measure will provide.

?>When setting `Info`, no need to specify `HandlerName` or other options, since you are going to use this child measure to retrieve infos only.

_Examples:_

```ini
StringValue=Number
; makes this Child measure provide a numerical value based on what it receives from the handler: 0.3, 0.78, etc..
```

Or

```ini
StringValue=Info
; Then
InfoRequest=Current Device, Name
; Will make this Child measure provide the name of current Audio device
; For example: Realtek High Definition Audio
```

---

<p id="info-request" class="p-title"><b>InfoRequest</b><b>Parameters: (See Below)</b></p>

When [StringValue](#string-value) is set to `Info`, this option will determine what infos this measure will provide.

?>This is similar to using [Section Variables](/docs/section-vars.md), but without a function call.

_Examples:_

Section Variables are used like this: `[&ParentMeasure:Resolve(Current Device, Name)]`

Instead of that, we will specify the arguments here:

```ini
InfoRequest=Current Device, Name
```

That will make This Child measure provide the infos we requested.

```ini
[!log "[ChildMeasure]"]
; Will log: Realtek High Definition Audio
```

?> A complete list of possible arguments can be found [here](/docs/section-vars.md).
