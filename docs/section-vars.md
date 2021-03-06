## Section Variables

You can get properties of handlers and information about parent measure and audio devices using section variable.

Syntax is like the following:

```ini
Variable=[&ParentMeasureName:Resolve(FirstArgument, SecondArgument)]
```

_Variable here is used as an example, you can use Section Variables directly anywhere in your skin or even inside a Lua script. See [Tips and Code Snippets]() discussion._

We will show you examples on how to use them, as well as which arguments are available.

## Usage

To illustrate this, we gonna make a simple measure:

```ini
[InfosLogger]
Measure=Calc
Formula=0
UpdateDivider=-1
; UpdateDivider=-1 will make this measure update only when the skin is loaded or refreshed
DynamicVariables=1
OnUpdateAction=[!Delay 1500][!Log "[&MeasureAudio:Resolve(Current Device, Name)]"]
; Sometimes Delay is needed, infos may take a bit of time to be retrieved
```

The example above will log the Audio device name in [Rainmeter Logs window](https://docs.rainmeter.net/manual-beta/user-interface/about/#LogTab) every time you load or refresh the skin.

The Resolve Function takes 1 or 2 arguments:

- `FirstArgument`: Specifies the Type of information you want to get. Like: `Current Device`, `Device List`, `Value` (of a handler), `HandlerInfo` (infos about the handler proprieties).

  - `SecondArgument`: Specifies which infos `FirstArgument` should provide about its Type. Like: `FirstArg: Current Device` `SecondArg: Name`

## Available Arguments

?> Notice, the arguments are documented in a bullet list style:

- `ArgumentA`: _Description._
  - `ArgumentB`: _Description._

You will use these arguments like like so: `[&ParentMeasure:Resolve(ArgumentA, ArgumentB)]`

---

- `Current Device`: Information about the current audio device.

  - `Name`: Provides the Name of current device. For example: "Realtek High Definition Audio".
  - `Type`: Provides the Type of current device. Possible values are "Input" and "Output".<span id="current-device-type"></span>
  - `ID` : Provides the ID of current audio device. Can be used in [Source](/docs/plugin-structure/parent#source) option in Parent measure.

  - `Status`: Provides 1 if everything works, 0 otherwise.
  - `Status String`: Same as `Status`, but instead of giving 0 and 1, it gives 'Active' and 'Down'.

  - `DetailedState`: Provides the following based on the condition:

    - `1`: If everything works.
    - `2`: If there is some unknown connection error.
    - `3`: If current device was disconnected for some reason (for example, invalid options on parent measure).
    - `4`: If current device operates in [exclusive mode](/docs/plugin-structure/parent#exclusive-mode) right now.

  - `DetailedStateString`: Same as `DetailedState`, but instead of giving 1, 2, 3, and 4, it gives "Ok", "ConnectionError", "Disconnected" and "Exclusive".

  - `Description`: Provides a specific type of current device. For example, "Speakers".
  - `Format`: Provides a human readable description of format of current device. For example: "2.0 stereo, 192000Hz"
  - `Channels`: Provides a comma-separated list of technical names of channels that exist in current layout. For example: [5.1 layout]() will have "FL, FR, C, LFE, BL, BR"
  - `Sample Rate`: Provides the sample rate of current device. For example: 48000

_Examples:_

```ini
[!Log [&ParentMeasure:Resolve(Current Device, Name)]]
[!Log [&ParentMeasure:Resolve(Current Device, Sample Rate)]]
```

---

- `Device List Input`: Provides a list of existing input devices.
- `Device List Output`: Provides a list of existing output devices.
- `Device List`: Provides a maps to one of the 2 values above. Input or output is decided based on [current device type](#current-device-type).

?>The three values above are not meant to be human readable. Grab and process them with a Lua script before showing to user.

The value of these arguments consists of several lines. Each line has the following format:

`ID`;`Name`;`Description`;`Form factor`;`Sample rate`;`Channels`;

```ini
[!Log [&ParentMeasure:Resolve(Device List Output)]]
; Will output: {0.0.0.00000000}.{c73b9bf1-9f30-4a46-9786-c5d3d2c18aba};Realtek High Definition Audio;Speakers;Speakers;48000;fl,fr;
```

Many devices have `Description` and `Form factor` values the same, but there are also devices with different values. For example, my monitor have monitor name as a description and DigitalAudioDisplayDevice as a form factor. Also, form factor is a well known set of values, while description may be an arbitrary human readable string.

Possible values of `Form factor` are: `RemoteNetworkDevice`, `Speakers`, `LineLevel`, `Headphones`, `Microphone`, `Headset`, `Handset`, `UnknownDigitalPassthrough`, `SPDIF`, `DigitalAudioDisplayDevice`, `<unknown>`.

Sample rate and channels may also be represented as `<unknown>` for some devices when it's impossible to determine that audio device format.

---

- `Value`: Allows you to get number values without child measures.

  - `Channel`: Specify name of the channel. Default name is Auto.
  - `Handler`: Specify name of the desired Handler.
  - `Proc`: Specify name of the processing that contains desired handler.
  - `Index`: Specify integer index of the value of data generated by handler. If index is not specified, then default 0 is used.

See [Tips](/docs/tips-code.md) discussion.

_Examples:_

```ini
[!Log [&ParentMeasure:Resolve(Value, Handler Loudness | Channel Left)]]
[!Log [&ParentMeasure:Resolve(Value, Proc Process1 | Channel Auto | Handler Resampler | Index 10)]]
```

---

- `HandlerInfo`: Allows you to get additional information from sound handlers.

  Syntax is as in `Value` argument, except instead of integer `Index` you have to specify `Data`. Syntax for Data property is handler-dependent, see [certain handler's]() description for possible values of data.

_Examples:_

```ini
[!Log [&ParentMeasure:Resolve(HandlerInfo, Proc Process1 | Channel Auto | Handler Resampler | Data Bands Count)]]
```
