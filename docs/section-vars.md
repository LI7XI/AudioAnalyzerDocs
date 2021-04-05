## Section Variables

You can get properties of handlers and information about parent measure and audio devices using section variable.

Syntax is like the following:

```ini
Variable=[&ParentMeasureName:Resolve(FirstArgument, SecondArgument)]
```

_Variable here is used as an example, you can use Section Variables directly anywhere in your skin or even inside a Lua script. See [Tips](/docs/tips-code?id=child-measures-vs-section-variables) discussion._

Here, we will show you examples on how to use them, as well as which arguments are available.

## Usage

To illustrate this, we will use `OnRefreshAction` option in Rainmeter section:

```ini
[Rainmeter]
OnRefreshAction=[!Delay 1500][!Log "[&MeasureAudio:Resolve(Current Device, Name)]"]
; Sometimes Delay is needed, infos may take a bit of time to be retrieved
```

The example above will log the Audio device name in [Rainmeter Logs window](https://docs.rainmeter.net/manual-beta/user-interface/about/#LogTab) every time you load or refresh the skin.

?>Alternatively, you can use [OnDeviceChange](/docs/plugin-structure/parent?id=callback-ondevicechange) callback, it won't require any `Delay`, because `OnDeviceChange` will only be called when the plugin has connected to the audio device.

For example:

```ini
; In parent measure
Callback-OnDeviceChange=[!Log "[&MeasureAudio:Resolve(Current Device, Name)]"]
; Delay is not needed
```

The Resolve Function takes 1 or 2 arguments:

- `FirstArgument`: Specifies the Type of information you want to get. Like: `Current Device`, `Device List`, `Value` (of a handler), `HandlerInfo` (infos about the handler proprieties).

  - `SecondArgument`: Specifies which infos `FirstArgument` should provide about its Type. Like: `FirstArg: Current Device` `SecondArg: Name`

## Available Arguments

?>Notice that the arguments are documented in a bullet list style:

- `ArgumentA`: _Description._
  - `ArgumentB`: _Description._

You will use these arguments like like so: `[&ParentMeasure:Resolve(ArgumentA, ArgumentB)]`

!>Note that `Resolve` function is case-sensitive, which means if you wrote other than `Resolve` or `resolve`, it will not work.

!>When `ArgumentA` is `Value` or `HandlerName`, `ArgumentB` will have a different syntax, it would be a list of pipe-separated parameters.

---

- `Current Device`: Information about the current audio device.

  - `Name`: Provides the Name of current audio device. For example: "Realtek High Definition Audio".
  - `Type`: Provides the Type of current audio device. Possible values are "Input" and "Output".<span id="current-device-type"></span>
  - `ID` : Provides the ID of current audio device. It can be used in [Source](/docs/plugin-structure/parent?id=source) option in Parent measure.

  - `Status`: Provides 1 if everything works, 0 otherwise.

  - `DetailedState`: Provides the following based on the condition:

    - `1`: If everything works.
    - `2`: If there is some unknown connection error.
    - `3`: If current device was disconnected for some reason (for example, invalid options on parent measure).
    - `4`: If current device operates in [exclusive mode](/docs/plugin-structure/parent#exclusive-mode) right now.

  - `DetailedStateString`: Same as `DetailedState`, but instead of giving 1, 2, 3, and 4, it gives "Ok", "ConnectionError", "Disconnected" and "Exclusive".

  - `Description`: Provides a specific type of current device. For example, "Speakers".
  - `Format`: Provides a human readable description of format of current device. For example: "2.0 stereo, 192000Hz"
  - `Channels`: Provides a comma-separated list of technical names of channels that exist in current layout. For example: 5.1 layout will have "FL, FR, C, LFE, BL, BR"
  - `Sample Rate`: Provides the sample rate of current device. For example: 48000

_Examples:_

```ini
[!Log "[&ParentMeasure:Resolve(Current Device, Name)]"]
[!Log "[&ParentMeasure:Resolve(Current Device, Sample Rate)]"]
```

---

- `DeviceList`: Provides a list of existing audio devices.

?>`DeviceList` value is not meant to be human readable. Process it with the provided [Lua script](/docs/tips-code?id=audio-devices-list) before showing to user.

The value of this argument is a string that contains audio devices separated by a forward slash (`/`). Each audio devices has the following format:

`ID`;`Name`;`Description`;`Form factor`;`Sample rate`;`Channels`;`Type`;

There are few notes:

- `Channels` may be `<unknown>` if all channels of this device are not supported by the plugin.
- `Type` can be either `Input` or `Output`.
- No values except channels can be empty.

```ini
[!Log "[&ParentMeasure:Resolve(DeviceList)]"]
; Will output: {0.0.0.00000000}.{c73b9bf1-9f30-4a46-9786-c5d3d2c18aba};Realtek High Definition Audio;Speakers;Speakers;48000;fl,fr,;output;/
```

Many devices have `Description` and `Form factor` values the same, but there are also devices with different values. For example, my monitor have monitor name as a description and "DigitalAudioDisplayDevice" as a form factor. Also, form factor is a well known set of values, while description may be an arbitrary human readable string.

Possible values of `Form factor` are: `RemoteNetworkDevice`, `Speakers`, `LineLevel`, `Headphones`, `Microphone`, `Headset`, `Handset`, `UnknownDigitalPassthrough`, `SPDIF`, `DigitalAudioDisplayDevice`, `<unknown>`.

Sample rate and channels may also be represented as `<unknown>` for some devices when it's impossible to determine the audio device format.

---

- `Value`: Allows you to get number values without child measures.

  - `Channel`: Specify name of the channel. Default name is Auto.
  - `HandlerName`: Specify name of the desired Handler.
  - `Proc`: Specify name of the processing unit that contains desired handler.
  - `Index`: Specify integer index of the value of data generated by handler. If index is not specified, then default (`0`) is used.

    !>If you specified an invalid index (for example you set it to 3 while the handler doesn't provide indexing) it will result in full parent measure stop until skin refresh.

See [Tips](/docs/tips-code?id=child-measures-vs-section-variables) discussion.

_Examples:_

```ini
[!Log "[&ParentMeasure:Resolve(Value, HandlerName Loudness | Channel Left)]"]
[!Log "[&ParentMeasure:Resolve(Value, Proc Process1 | Channel Auto | HandlerName Resampler | Index 10)]"]
```

---

- `HandlerInfo`: Allows you to get additional information from sound handlers.

  Syntax is same as `Value` argument, except instead of integer `Index` you have to specify `Data`. Syntax for Data property is handler-dependent, see [certain handler's](/docs/handler-types/handler-types?id=handler-infos-and-section-variables) description for possible values of data.

_Examples:_

```ini
[!Log "[&ParentMeasure:Resolve(HandlerInfo, Proc Process1 | Channel Auto | HandlerName Resampler | Data Bands Count)]"]
```
