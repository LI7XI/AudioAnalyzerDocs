## Parent Measure

Here we will explain the available options for Parent measure.<br/>
Reference used to illustrate the options are linked at the [bottom](#Reference) of this page.

## Jump list

- [Source](#source).
- [ProcessingUnits](#processing-units).
- [Unit-UnitName](#unit-unitname).
- [Handler-HandlerName](#handler-handlername).
- [Threading](#threading).
- [LogUnusedOptions](#log-unused-options).
- [LockCaptureVolumeOnMax](#lock-capture-volume-on-max).
- [Callback-OnDeviceChange](#callback-ondevicechange).
- [Callback-OnDeviceDisconnected](#ondevice-disconnected).
- [Callback-OnDeviceListChange](#ondevice-listchange).

## Available Options

<p id="source" class="p-title"><b>Source</b><b>Default: DefaultOutput</b></p>

Specifies device from which to capture audio.

- `DefaultInput`: Plugin will grab audio from default input device (such as microphone).
- `DefaultOutput`: Plugin will grab audio from default output device, such as speakers.
- `ID: <DeviceID>`: You can specify an exact device to capture data from it instead of default devices.

DeviceID Syntax is the following:

First we write the option name, followed by the parameter name then a colon:

```ini
Source=ID:
```

Then we write the obtained ID from the [Section Variables](/docs/section-vars.md):

```ini
Source=ID: {0.0.0.00000000}.{134d7830-179e-4748-9861-37967e8bda9e}
```

!> If you are distributing your skin, don't just set Source to some exact device ID, because other computers will have different devices with different IDs. So you should let the user choose the audio device.

See [Tips and Code Snippets](/docs/tips-code?id=audio-devices-list) discussion for how to achieve this using Lua and Rainmeter `[#Variables]`.

_Examples:_

```ini
Source=DefaultOutput
```

Or

```ini
Source=ID: {0.0.0.00000000}.{134d7830-179e-4748-9861-37967e8bda9e}
```

---

<p id="processing-units" class="p-title"><b>ProcessingUnits</b><b>Default: None</b></p>

Specify one or a list of processing units separated by a comma.

!>Names in this list must be unique, and can **only contain** [ASCII](https://en.wikipedia.org/wiki/ASCII) characters, digits and underscores.

_Examples:_

```ini
ProcessingUnits=Main
```

Or

```ini
ProcessingUnits=Main, Another_Process1
```

---

<p id="unit-unitname" class="p-title"><b>Unit-<u>UnitName</u></b><b>Required</b></p>

Specify the process description, how this process is going to capture audio.

Parameters:

- `Channels`**(Required)**:<i id="parent-channel-para"></i> Specify one or a list of comma-separated channel names to tell this process which channel to get audio data from.

  ?>If you specified a [Channel](#channel-list) that this process can't find in the audio device, the handlers will return 0 as a value, and handlers that draw images will draw an empty image for one time, then stop updating until this channel is available (if the channel became available again then the plugin will connect to it automatically. No skin refresh required).<br/>
  Also No error log messages will be generated for this.<br/><br/>
  But if you specified channels that aren't present in [Unit channels list](#channel-list) (e.g. `Channel SomeUnsupportedChannel`), then there will be a log message.

  Different Audio devices have different Audio Channels.
  Most common are just stereo devices that have `Left` and `Right` channels, but there are also audio systems with more channels.

  This plugin supports the following channels (with optional name aliases):<i id="channel-list"></i>

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

- `Handlers`**(Required)**: A list of handlers that this process must call in the specified order.<i id="parent-handler-para"></i><br/>

  !>Names in this list must be unique, and can **only contain** [ASCII](https://en.wikipedia.org/wiki/ASCII) characters, digits and underscores.

  See [Handlers](/docs/handler-types/handler-types.md) discussion.

- `TargetRate`(Optional): Specify the sample rate of the processed audio stream.<span class="d">Default: 44100</span>

  !>**Avoid** changing this value **Unless** you need to.<br/>
  Increasing TargetRate above 44100 could in some cases significantly increase CPU load without any difference in the result.<br/>
  Decreasing TargetRate below 44100 will affect results, and it's probably not the result you want. Because if target rate is 8000, then any sounds above 4000 Hz won't be detected.

  First, what is Sample Rate?<br/>
  The sample rate, in a nutshell, is the number of samples per second in a piece of audio. It is measured in Hertz (Hz) or Kilohertz (kHz).

  <img class="img" src="docs\examples\resources\sample_rate.png" title="Sample Rate">

  Very high sample rates aren't very helpful, because humans only hear sounds below 22 KHz, and 44.1 KHz sample rate is enough to describe any wave with frequencies below 22.05 KHz.

  Also high sample rates significantly increase CPU demands, so it makes sense to down-sample sound wave. That's why `TargetRate` option is used.<br/>
  Typical modern PC is capable of running 192 KHz, which is totally redundant for visualization. Final rate is always >= than TargetRate.

  So if your audio device sample rate is 48000 and TargetRate is 44100, then nothing will happen. If you sampling rate is less than TargetRate then nothing will happen.<br/>
  Setting `TargetRate` to 0 disables down-sampling completely.<br/>
  See [Performance](/docs/performance?id=target-rate) discussion.

- `Filter`(Optional): Performs signal filtering on the audio using the specified Filter. <span class="d">Default: None</span><br/>

  !>Except predefined filters (`like-a`, `like-d`), custom filters are intended for advanced usage, use them only if you have something specific in mind.<br/>

  See [Filters](/docs/discussions/filters.md) and [Tips](/docs/tips-code?id=using-filters) discussion.

_Examples:_

```ini
Unit-Main=Channels Auto | Handlers SourceHandler, AnotherHandler(SourceHandler) | Filter like-a
```

Or

```ini
Unit-Main=Channels Auto | Handlers MainFFT, Main_Resampler1(MainFFT) | Filter like-a
Unit-AnotherProcess=channels Auto | Handlers Loudness, LoudnessPercent(Loudness) | TargeRate 44100 | filter like-a
```

---

<p id="handler-handlername" class="p-title"><b>Handler-<u>HandlerName</u></b><b>Required</b></p>

Specify description of a sound handler.

This option contains handler types, each type has specific parameters.<br/>
See [Handler Types](/docs/handler-types/handler-types.md) discussion.

_Examples:_

```ini
Unit-Main=Channels Auto | Handlers MainFFT, MainResampler(MainFFT), MainTransform(MainResampler), MainFilter(MainTransform), MainMapper(MainFilter) | Filter like-a

Handler-MainFFT=Type FFT | BinWidth 30 | OverlapBoost 2 | CascadesCount 3
Handler-MainResampler=Type BandResampler | Bands log(Count 5, Min 20, Max 4000)
Handler-MainTransform=Type BandCascadeTransformer | MinWeight 0 | TargetWeight 100
Handler-MainFilter=Type TimeResampler | Attack 100
Handler-MainMapper=Type ValueTransformer | Transform dB, Map(From -50 : -0), Clamp
```

Or

```ini
Unit-Main=Channels Left, Right | Handlers Peak | Filter none

Handler-Peak=Type Peak | Transform db, Map(From -70 : 0), Clamp | UpdateRate 30 | Attack 20 | Decay 40
```

Or

```ini
Unit-Main=Channels Auto | Handlers LoudnessdB, LoudnessPerecnt(LoudnessdB) | Filter like-a

Handler-LoudnessdB=Type Loudness | Transform dB
Handler-LoudnessPerecnt=Type ValueTransformer | Transform Map(From -60 : 0), Clamp
```

---

<p id="log-unused-options" class="p-title"><b>LogUnusedOptions</b><b>Default: true</b></p>

A boolean value, specify whether the plugin should log error messages in Rainmeter log window.

- `true`(Recommended): The plugin will log a warning message if some of the Parameters in `Unit` option or in handlers aren't recognized.

  ?> If you see such messages in your log, then maybe you have made a mistake in option name, or tried to use option that doesn't exist.

- `false`: Disables error logs.

  See [Tips](/docs/tips-code?id=unused-parameters) discussion.

_Examples:_

```ini
LogUnusedOptions=true
```

Or

```ini
LogUnusedOptions=false
```

?>`LogUnusedOptions` only affects options that the plugin didn't read.<br/>
Other log messages are not suppressed with `LogUnusedOptions`.

Which means only if you did the following:

```ini
Unit-UnitName=Channels auto | Handlers Wave | speed fast
```

Then there will be a log message that says `Unit UnitName: unused options: [speed]`.<br/>
And `LogUnusedOptions=false` will make such log messages not appear.

---

<p id="threading" class="p-title"><b>Threading</b><b>Parameters: (See below)</b></p>

Configuration of a computing thread.

Parameters:

- Policy: Specify the way the plugin will work.

  - `UiThread`: Means only using main rainmeter thread.

  - `SeparateThread`**(Default and Recommended)**: Means that the audio will be processed in background thread.

- `UpdateRate`: A number in range from 1 to 200.<span class="d">Default: 60</span>
  <br/>Specify how many times per second plugin will update its values when running separate thread.

  "UpdateRate 60" means that 60 times per second plugin will try to fetch new data from windows and then transfer that data to handlers for them to update. See [Tips](/docs/tips-code?id=plugin-updaterate) discussion.

- `WarnTime`: Time specified in milliseconds.<span class="d">Default: -1</span>

  When processing time exceeds WarnTime, a warning message in the log will be generated. You can use it to check how much of a CPU time the plugin consumes with your settings.<br/>
  Negative values disables logging.

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

<p id="lock-capture-volume-on-max" class="p-title"><b>LockCaptureVolumeOnMax</b><b>Default: Never</b></p>

- `ForApp`: Sets application volume level to maximum and prevents its change.
- `Never`: Application volume can be set to any level.

_Examples:_

```ini
LockCaptureVolumeOnMax=ForApp
```

---

<p id="callback-ondevicechange" class="p-title"><b>Callback-OnDeviceChange</b><b>Default: None</b></p>

Specify a bang to be called every time device has changed. This include first connection to audio device.

Events that cause `OnDeviceChange` include, but are not limited to:

- There was no device, but now there is.
- Plugin captures audio stream from default device, and default device has changed.
- Device settings were changed.

_Examples:_

```ini
Callback-OnDeviceChange=[!Log "Audio Device is changed"]
```

---

<p id="ondevice-disconnected" class="p-title"><b>Callback-OnDeviceDisconnected</b><b>Default: None</b></p>

Specify a bang to be called every time device has been disconnected.

There are several ways this can happen:

- Plugin was capturing a default device, and all devices of that type became unavailable.

  For example, let's say you have speakers and headphones, and you have set `Source=DefaultOutput`, then if you pull the headphone jack from the PC, the plugin will automatically connect to speakers.<br/>
  But then, if you also pull speakers jack, there will be no audio devices available, and `onDeviceDisconnected` will be called.

- You were capturing data from some specific device, but this device is no longer available.
- Device that was being captured is now in [exclusive mode](https://answers.microsoft.com/en-us/windows/forum/windows_7-pictures/what-is-exclusive-mode-and-what-does-it-do/26922597-f6c8-4080-a675-199e37f37a0b).<span id="exclusive-mode"></span><br/>

  ?>Exclusive mode is when some application gets an exclusive ownership of the audio device. When device is in exclusive mode, no other application can connect to this device.

- Attempt to connect to this device ended with some unknown error.

_Examples:_

```ini
Callback-OnDeviceDisconnected=[!Log "An Audio Device has been disconnected"]
```

---

<p id="ondevice-listchange" class="p-title"><b>Callback-OnDeviceListChange</b><b>Default: None</b></p>

Specify a bang to be called every time something happens to any audio device in the system.

Events that cause `OnDeviceListChange` include, but are not limited to:

- New device was added.
- Device settings changed.
- Device was disabled or disconnected.<br/>

?>Differences between `OnDeviceListChange` and `OnDeviceDisconnected`: <br/><br/>
OnDeviceDisconnected is called when the device you are using was disconnected from the plugin. Nothing to do with the device physical disconnection, it's just that plugin can no longer connect to it.<br/><br/>
OnDeviceDisconnected is only called when the plugin become disconnected from the device. When one device is disconnected but another is available, then plugin seamlessly switches to that second device and only OnDeviceChange is called.<br/><br/>
OnDeviceListChange is called when any device changed. Changes include, for example, when user pulled the headphone jack from the PC.<br/><br/>
When OnDeviceDisconnected is called, then OnDeviceListChange is also likely to be called, but it's not guaranteed, and it doesn't work the other way around.

_Examples:_

```ini
Callback-OnDeviceListChange=[!Log "New audio device is connected!"]
```

Or

```ini
Callback-OnDeviceListChange=[!Log "Audio device settings are changed"]
```

Or

```ini
Callback-OnDeviceListChange=[!Log "Audio Device was disabled or disconnected"]
```

---

## Reference

Here are links for the Reference used to illustrate the options:

- [Sample Rate](https://www.masteringthemix.com/blogs/learn/113159685-sample-rates-and-bit-depth-in-a-nutshell)
