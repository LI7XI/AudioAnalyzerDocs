## Parent Measure

Now after we know the difference between [Parent and Child](/docs/plugin-structure/plugin-structure.md) measures, it's time to know what options are available for each type.

?> Note that all options specified here are present only in Parent measure, Child measure options are specified [here](/docs/plugin-structure/child.md).

## Available Options

<p style="display: flex; justify-content: space-between;"><b>MagicNumber</b><b>Default: 0</b></p>

This plugin has an old version which is partially compatible with the new one. To avoid breaking changes while still delivering improved experience to old skin users, option MagicNumber was introduced. It is used to determine whether plugin should run in the new or in the legacy mode.

Always set MagicNumber to value 104, or else plugin will run in legacy mode which have many default values different from what is described in this documentation.

- `0`: Legacy Mode.
- `104`: Makes the plugin use the newest features.

_Examples:_

```ini
MagicNumber=104
```

---

<p style="display: flex; justify-content: space-between;"><b>Source</b><b>Default: DefaultOutput</b></p>

Specifies device from which to capture audio.

- `DefaultInput`: Plugin will grab audio from default input device (such as microphone).
- `DefaultOutput`: Plugin will grab audio from default output device, such as speakers.
- _`Device description`_: You can specify an exact device to capture data from it instead of default devices.

Device description Syntax is the following:

First we write the option name, followed by the parameter name:

```ini
Source=ID
```

Then we write the obtained ID from the [Section Variables]():

```ini
Source=ID {0.0.0.00000000}.{134d7830-179e-4748-9861-37967e8bda9e}
```

!> If you are distributing your skin, don't just set Source to some exact device ID, because other computers will have different devices with different IDs. If you want to provide user with a way to capture one exact device, create a Lua script that will read IDs from Section Variable and give user some way to select one of them.

See [Tips and Code Snippets]() discussion for how to achieve this using Lua and Rainmeter `[#Variables]`.

_Examples:_

```ini
Source=DefaultInput
```

Or

```ini
Source=ID: {0.0.0.00000000}.{134d7830-179e-4748-9861-37967e8bda9e}
```

_Todo: Testing examples validity._

---

<p style="display: flex; justify-content: space-between;"><b>Processing</b><b>Required</b></p>

Specify one or a list of processes separated by pipe symbol.

!>Names in this list must be unique.

_Examples:_

```ini
Processing=Main
```

Or

```ini
Processing=Main | AnotherProcess
```

---

<p style="display: flex; justify-content: space-between;"><b>Processing-<u>ProcessName</u></b><b>Required</b></p>

Specify the process description, what this process is going to do.

Parameters:

- `Channels`**(Required)**:<i id="parent-channel-para"></i> Specify one or a list of comma-separated channel names to tell this process which channel to get audio data from.

  ?>If you specified a [Channel](#channel-list) that this process can't find in the audio device, the handlers will return 0 as a value, and handlers that draw images will draw an empty image for one time, then stop updating until this channel is available (if the channel became available again then the plugin will connect to it automatically. No skin refresh required).<br/>
  Also No error log messages will be generated for this.<br/><br/>
  But if you specified channels that aren't present in [Processing channel list](#channel-list) (e.g. `Channel SomeUnsupportedChannel`), then there will be a log message.

  _Todo:_

  - _Is this explanation correct?_

  Different Audio devices have different Audio Channels.
  Most common are just stereo devices that have `Left` and `Right` channels, but there are also audio systems with more channels.

  This plugin supports the following channels (with optional name aliases):<i id="channel-list"></i>

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

- `Handlers`**(Required)**: A list of handlers that this process must call in the specified order.<br/>
  See [Handlers]() discussion.
- `TargetRate`(Optional): Specify the sample rate of the processed audio stream.
  <span class="d">Default: 44100</span>

  !>**Avoid** changing this value **Unless** you need to.<br/>
  Increasing TargetRate above 44100 could in some cases significantly increase CPU load without any difference in the result.<br/>
  Even a small increase, like from 0.5% to 3%, I don't think it's good.<br/><br/>
  Decreasing TargetRate below 44100 will affect results, and it's probably not the result you want. <br/>
  Because if target rate is 8000, then any sounds above 4000 Hz won't be detected.

  Very high sample rates aren't very helpful, because humans only hear sounds below 22 KHz, and 44.1 KHz sample rate is enough to describe any wave with frequencies below 22.05 KHz.

  But high sample rates significantly increase CPU demands, so it makes sense to downsample sound wave. And typical modern PC is capable of running 192 KHz, which is totally redundant.
  Final rate is always >= than TargetRate.

  So if you rate is 48000 and TargetRate is 44100, then nothing will happen. If you sampling rate is less than TargetRate then nothing will happen.
  Setting this to 0 disables downsampling completely.<br/>
  See [Performance]() discussion.

- `Filter`(Optional): Performs signal filtering on the audio using the specified Filter. <span class="d">Default: None</span><br/>
  See [Filters]() discussion.

_Examples:_

```ini
Processing-Main=Channels Auto | Handlers Mainfft, MainResampler | Filter like-a
```

Or

```ini
Processing-Main=channels FL, Right | Handlers PeakRaw, PeakFiltered, Peak, peakPercent
Processing-AnotherProcess=channels Auto | Handlers Loudness, LoudnessPercent | TargeRate 44100 | filter like-a
```

---

<p style="display: flex; justify-content: space-between;"><b>Handler-<u>HandlerName</u></b><b>Required</b></p>

Specify description of a sound [handler](#what-is-a-handler).<br/>
Contains handler types, each type has specific parameters.

See [Handler Types](/docs/handler-types/handler-types.md) discussion.

_Examples:_

```ini
Handler-Mainfft=Type fft | BinWidth 5 | OverlapBoost 10 | CascadesCount 3
Handler-MainResampler=Type BandResampler | Source Mainfft | Bands log 5 20 4000
```

Or

```ini
Handler-PeakRaw=Type Peak
Handler-PeakFiltered=Type TimeResampler | source PeakRaw | attack 0 | decay 200
Handler-Peak=Type ValueTransformer | source PeakFiltered | transform db
Handler-PeakPercent=Type ValueTransformer | source Peak | transform map[from -50 : 0] clamp
```

Or

```ini
Handler-loudness=Type Loudness | Transform db
Handler-lodnessPercent=Type ValueTransformer | Source Loudness | Transform map[from -50 : 0] clamp
```

---

<p style="display: flex; justify-content: space-between;"><b>UnusedOptionsWarning</b><b>Default: true</b></p>

A boolean value, specify whether the plugin should log error messages in Rainmeter log window.

- `true`(Recommended): The plugin will log a warning message if some of the Parameters in `Processing` option or handlers aren't recognized.

  ?> If you see such messages in your log, then maybe you have made a mistake in option name, or tried to use option that doesn't exist.

- `false`: Disables error logs.

  See [Tips]() discussion.

_Examples:_

```ini
UnusedOptionsWarning=true
```

Or

```ini
UnusedOptionsWarning=false
```

?>`UnusedOptionsWarning` only affects options that the plugin didn't read.<br/>
Other log messages are not suppressed with `UnusedOptionsWarning`.

Which means only if you did the following:

```ini
Processing-ProcessName=channels auto | handlers wave | speed fast
```

Then there will be a log message that says `Processing proc2: unused options: [speed]`.<br/>
And `UnusedOptionsWarning=false` will make such log messages not appear.

---

<p style="display: flex; justify-content: space-between;"><b>Threading</b><b>Parameters: (See below)</b></p>

Configuration of a computing thread.

Parameters:

- Policy: Specify the way the plugin will work.

  - `UiThread`: Means only using main rainmeter thread

  - `SeparateThread`**(Default and Recommended)**: Means that the audio will be processed in background thread.

- `UpdateRate`: A number in range from 1 to 200. <span class="d">Default: 60</span>

  Specify how many times per second plugin will update its values when running separate thread.

- `WarnTime`: Time specified in milliseconds. <span class="d">Default: -1</span>

  When processing time exceeds WarnTime, a warning message in the log will be generated. You can use it to check how much of a CPU time the plugin consumes with your settings.<br/>
  Negative values disables logging.

See [Performance]() discussion.

_Examples:_

```ini
Threading=Policy UiThread
```

Or

```ini
Threading=Policy UiThread | WarnTime -1
```

Or

```ini
Threading=Policy SeparateThread | UpdateRate 90
```

Or

```ini
Threading=Policy SeparateThread | UpdateRate 90 | WarnTime -1
```

!>When `UiThread` is used, `UpdateRate` won't have any effect.

```ini
Threading=Policy UiThread | UpdateRate 90
; UpdateRate here will have no effect. UpdateRate will be controlled internally by rainmeter.
```

---

<p style="display: flex; justify-content: space-between;"><b>Callback-OnUpdate</b><b>Default: None</b></p>

Specify a bang to be called every time values are updated.

_Examples:_

```ini
Callback-OnUpdate=[!Log "Logs Spam!"]
```

---

<p style="display: flex; justify-content: space-between;"><b>Callback-OnDeviceChange</b><b>Default: None</b></p>

Specify a bang to be called every time device has changed. This include first connection to audio device.

Events that cause `OnDeviceChange` include, but are not limited to:

- There was no device, but now there is
- Plugin captures audio stream from default device, and default device has changed
- Device settings were changed

_Examples:_

```ini
Callback-OnDeviceChange=[!Log "Audio Device is changed"]
```

---

<p style="display: flex; justify-content: space-between;"><b>OnDeviceDisconnected</b><b>Default: None</b></p>

Specify a bang to be called every time device has been disconnected.

There are several ways this can happen:

- Plugin was capturing a default device, and all devices of that type became unavailable.

  For example, lets say you have speakers and headphones, and you have set `Source=defaultoutput`, then if you pull the headphone jack from the PC, the plugin will automatically connect to speakers.<br/>
  But then, if you also pull speakers jack, there will be no audio devices available, and onDeviceDisconnected will be called.

- You were capturing data from some specific device, but this device is no longer available.
- Device that was being captured is not in [exclusive mode](https://answers.microsoft.com/en-us/windows/forum/windows_7-pictures/what-is-exclusive-mode-and-what-does-it-do/26922597-f6c8-4080-a675-199e37f37a0b).<br/>

  ?>Exclusive mode is when some application gets an exclusive ownership of the audio device. When device is in exclusive mode, no other application can connect to this device.

- Attempt to connect to this device ended with some unknown error.

_Examples:_

```ini
OnDeviceDisconnected=[!Log "An Audio Device has been disconnected"]
```

---

<p style="display: flex; justify-content: space-between;"><b>OnDeviceListChange</b><b>Default: None</b></p>

Specify a bang to be called every time something happens to any audio device in the system.

Events that cause `OnDeviceListChange` include, but are not limited to:

- New device was added.
- Device settings changed.
- Device was disabled or disconnected.<br/>

?>Differences between `OnDeviceListChange` and `OnDeviceDisconnected`: <br/><br/>
OnDeviceDisconnected is called when the device you are using was disconnected from the plugin. Nothing to do with the device physical disconnection, it's just that plugin can no longer connect to it.<br/><br/>
OnDeviceDisconnected is only called when the plugin become disconnected from the device. When one device is disconnected but another is available, then plugin seamlessly switches to that second device and only onDeviceChange is called.<br/><br/>
OnDeviceListChange is called when any device changed. Changes include, for example, when user pulled the headphone jack from the PC.<br/><br/>
When OnDeviceDisconnected is called, then OnDeviceListChange is also likely to be called, but it's not guaranteed, and it doesn't work the other way around.

_Examples:_

```ini
OnDeviceListChange=[!Log "New audio device is connected!"]
```

Or

```ini
OnDeviceListChange=[!Log "Audio device settings are changed"]
```

Or

```ini
OnDeviceListChange=[!Log "Audio Device was disabled or disconnected"]
```
