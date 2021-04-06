## Tips and Code Snippets

Here we will share some tips to help you when creating skins.

## Fps Variable

You should make a framerate variable to help you when setting the update rate of your skins.<br/>
Also it will help other users to specify the update rate instead of guessing it.

Here is how you do it:

```ini
[Rainmeter]
Update=[#UpdateRate]

[Variables]
Fps=30
UpdateRate=(1000 / #Fps#)
; Formula is stolen from here: https://forum.rainmeter.net/viewtopic.php?t=26831#p140108
```

We will use that variable in some of the plugin options as well.

## Mistakes and Errors

If you made a mistake somewhere in the plugin options or parameters, the entire plugin will not work until you fix it. There is actually a pretty good reason for that.

If the plugin kept working normally you wouldn't notice that something is wrong, also you will waste performance since the error wouldn't make things work as expected, but the process that have that error is still running.

So it's better when the plugin stops working so you can figure out where is the problem.

Altho this doesn't include the errors made using [this](#unused-parameters) method.

## Child measures vs Section variables

If you want to get a value from a handler, you can either get it using a child measure:

```ini
[ChildMeasure]
Measure=plugin
Plugin=AudioAnalyzer
Type=Child
Parent=MeasureAudio
Channel=Auto
HandlerName=HandlerName
```

Or using section variables:

```ini
[&ParentMeasure:Resolve(Value, Handler HandlerName | Channel Auto)]
```

Both ways will give you the results you want, but it always recommended to use child measures. Why?<br/>
Mostly because the ease of use, you can use child measures in `MeasureName` option of any meter that supports it, while when using section variables, you have to figure out the proper way of using it.

Let's say you want to make a calculation, using a child measure would be: `(1 + [ChildMeasure])`<br/>
But with section variables: `(1 + [&ParentMeasure:Resolve(Value, Handler HandlerName | Channel Auto)])`

You can technically make a variable and set it to that long line `Value=[&ParentMeasure:Resolve(Value, Handler HandlerName | Channel Auto)]` then use that in your calculation: `(1 + #Value#)`. But why going through all that?

Section variables are intended to be used in logging and Lua scripts. Even though child measures can retrieve infos as well, it's recommended to use section variables for infos, and child measures to retrieve values.

Except when using Spectrogram or Waveform handlers, you should use a child measure to retrieve the path infos about the image they generate. But of course choose what fits your needs the most.

Now, performance wise, what's the difference?<br/>
They have almost identical performance. Child measures performance depends on how rainmeter handles them. Section variables performance depends on how the plugin handles them.

Most of the performance is taken in drawing the meters, not in retrieving values. So you wouldn't notice any performance difference between child measures and sections variables.

## Handlers Arrangement

In most cases this doesn't make much difference as long as you get the results you want. But there are few notes when using FFT handler type.

Lets say you have FFT handler:

```ini
Unit-Main=Channels ... | Handlers FFT
Handler-FFT=Type FFT
```

Don't use it as a source for any other handler than BandResampler:

```ini
Unit-Main=Channels ... | Handlers FFT, Resampler(FFT)
Handler-FFT=Type FFT
Handler-Resampler=Type BandResampler
```

If you did the following the plugin will log an error and stops working:

```ini
Unit-Main=Channels ... | Handlers FFT, AnotherHandler(FFT) Resampler(AnotherHandler)
Handler-FFT=Type FFT
Handler-AnotherHandler=Type ValueTransformer
Handler-Resampler=Type BandResampler
```

---

Another things, lets say you have this:

```ini
Unit-Main=Channels ... | Handlers FFT, Resampler(FFT), Transformer(Resampler)
Handler-FFT=Type FFT
Handler-Resampler=Type BandResampler
Handler-Transformer=Type BandCascadeTransformer
```

It's recommended to use TimeResampler after them, not between them (doing so will cause an error), because high and low frequencies don't update at same speed, and TimeResampler helps in providing a consistent output.

After that you can add other handlers like UniformBlur or Spectrogram.

## TimeResampler vs ValueTransformer

Both of these handlers can apply transformations on the source value. But TimeResampler can do other things beside them, what you should know it, TimeResampler does the filtering (`Attack`, `Decay`, etc..) before applying the transformations.

Now here is the thing, let's say you have this:

```ini
Unit-UnitName=Channels ... | Handlers SourceHandler -> TR -> VT
Handler-SourceHandler=Type ...
Handler-TR=Type TimeResampler
Handler-VT=Type ValueTransformer | Transform ...
```

In this case ValueTransformer is not needed, Since you could use the transforms in TimeResampler.

```ini
Unit-UnitName=Channels ... | Handlers SourceHandler -> TR
Handler-SourceHandler=Type ...
Handler-TR=Type TimeResampler | Transform ...
```

But if you have this:

```ini
Unit-UnitName=Channels ... | Handlers SourceHandler -> VT -> TR
Handler-SourceHandler=Type ...
Handler-VT=Type ValueTransformer | Transform ...
Handler-TR=Type TimeResampler
```

Then it would be different, since in first case, TimeResampler applies the transforms at the end, whereas now the transformations are applied before the filtering. In some cases, the difference can be very noticeable.

## Handlers Order

Lets say you want to make 3 handlers, and set the first one as a source for the second one, here is what you would do:

```ini
Unit-UnitName=Channels ... | Handlers HandlerA, HandlerB(HandlerA), HandlerC(HandlerB)
; Or
Unit-UnitName=Channels ... | Handlers HandlerA, HandlerB(HandlerA), HandlerC(HandlerA)
```

Pretty simple.

But if you changed the order:

```ini
Unit-UnitName=Channels ... | Handlers HandlerC(HandlerB), HandlerA, HandlerB(HandlerA)
```

Then it won't work because the plugin is expecting to find `HandlerB` before `HandlerC`.

## Parameters Order

In any handler type, you can arrange the parameters in any way you like.

```ini
Handler-HandlerName=Type ... | ParaA ... | ParaB ... | ParaC ...
```

Or

```ini
Handler-HandlerName=Type ... | ParaC ... | ParaA ... | ParaB ...
```

## Filtering

In some cases (TimeResampler handler as example) we mentioned that it does filtering, we don't mean the same filtering that `Filter` parameter in `Unit` option does.

What Filter parameter does is it affects certain frequencies of the audio, like you could remove high frequencies, or make low frequencies more noticeable.<br/>
What ValueTransformer or TimeResampler does (in case of using transform parameter) is that it affects audio levels, not specific frequencies.

For example: `dB, Map(From -70 : 0), Clamp` will show quieter sounds, whereas `dB, Map(From -20 : 0), Clamp` will show the loud sounds only.

## Using Filters

In some cases you may want to adjust sound frequencies, you can use `Filters` parameter in `Unit` option to specify the filters.

But there are few notes when using filters:

When you are using a loudness handler, you should always use a `like-a` filter preset, otherwise the value you will see would be very different from perceived loudness.

When using waveform, most likely you shouldn't use filters. At least, `like-a` and `like-d` presets will probably not give you good results.

If you are using waveform **beside** other handlers, and you want to apply custom filters on the waveform, it's better to make a new processing unit for the waveform handler, and use filters in that process.

When using peak, it must not use any filters.

For spectrum and spectrogram, it's recommended to use filters that mimics human hearing.

Using filters depends on what you want to visualize, and it's totally optional. But in some cases it's necessary to use filters.

## Settings Skin

It's not convenient to use variables to change settings since sometimes, the measures and meters are generated dynamically, so at least you need to refresh the skin twice to see the effect.

Instead of that, you could make a skin for settings, this is needed to create a menu for audio devices so that users can choose the audio device.

You have few options:

- Using [RainForms](https://forum.rainmeter.net/viewtopic.php?t=34276) plugin to make a user interface.
- Using [AutoIt](https://www.youtube.com/playlist?list=PL4Jcq5zn02jKpjX0nqI1_fS7mEEb5tw6z) to make a user interface.
- Creating the user interface from scratch.

We will go with the last one since it's the easiest for now, Check out [this](/docs/usage-examples/settings-skin.md) examples to see how we made it.

## Audio Devices List

_WIP_

<!-- Since a user may have more than one audio device, we need a way to let them choose the one they want. Luckily, the plugin will provide you with a list of connected audio devices, but you need to parse them with a lua script first, and that's what we are going to do:

?>To keep it short, we are going to explain the code part only, but the full example and a tutorial on how we made it is available [here](/docs/usage-examples/settings-skin.md)

?>Code used here is inspired by [@marcopixel](https://github.com/marcopixel) and [@alatsombath](https://github.com/alatsombath), a special thanks for them.

<details>

We will do everything inside `Initialize` function since it will run once the skin is loaded.

```lua
function Initialize()
end
```

We will display them using a context menu, each context has an index, (`ContextTitle`, `ContextTitle2`, `ContextTitle3`, etc).

When we request audio devices list from the plugin using section variables, the plugin will give us the infos of each device in a new line.

We will use the first context as the default, and for each audio device we gonna increment a variable so we can use it as an index.

```lua
function Initialize()
  ContextIndex = 1
  -- This variable will be used for the context indices

  -- We will use section variables in parent measure to get a list of audio devices
  -- The plugin will output each device infos in a new line
  for i in string.gmatch(SKIN:ReplaceVariables('[&GetAudioDevices:Resolve(Device List Output)]'), "[^\n]+") do
    -- For each line we gonna do the following
  end
end
```

Now, for each line in our loop, we will do the following:

First, increase the context index (since we used the context with index 1 as the "Default" option).

```lua
ContextIndex = ContextIndex + 1
```

Then we will create a new array to hold the infos of each device. For each audio device, this array will be overridden with the new audio device infos.

```lua
AudioDeviceInfos = {}
-- Each time we loop, the infos here will be overridden
```

The infos of an audio device will look like the following:<br/>

```
{0.0.0.00000000}.{c73b9bf1-9f30-4a46-9786-c5d3d2c18aba};Realtek High Definition Audio;Speakers;Speakers;48000;fl,fr;
```

We will extract the infos we want using semicolon as a separator. Then store them in the array.

```lua
for j in string.gmatch(i, "[^;]+") do
-- Then we store each info in AudioDeviceInfos array
  table.insert(AudioDeviceInfos, j)
end
```

Now our array contains the infos as the following:

```lua
AudioDeviceInfos = {"{0.0.0.00000000}.{c73b9bf1-9f30-4a46-9786-c5d3d2c18aba}", "Realtek High Definition Audio", "Speakers", "Speakers", "48000", "fl,fr"}
```

We can access the infos using there index, 0 will be "nil" value so we will start from 1

```lua
AudioDeviceID = AudioDeviceInfos[1]
AudioDeviceName = AudioDeviceInfos[2]
```

Since we are in a loop, and that loop is determined by how many audio devices the user may have, we will create a new option for each audio device.

```lua
SKIN:Bang("!SetOption", "Rainmeter", "ContextTitle" .. ContextIndex, AudioDeviceName)
```

And when the user click on a device, we write the device name/id to there variables in Common file, then we refresh all skins

```lua
SKIN:Bang("!SetOption", "Rainmeter", "ContextAction" .. ContextIndex, '[!WriteKeyValue Variables AudioDeviceName "' .. AudioDeviceName .. '" "#@#Variables/Common.inc"][!WriteKeyValue Variables AudioDeviceID "ID: ' .. AudioDeviceID .. '" "#@#Variables/Common.inc"][!RefreshGroup [#GroupName]]')
```

And the process will be repeated for each audio device. Here is the full code

```lua
function Initialize()
  ContextIndex = 1

  for i in string.gmatch(SKIN:ReplaceVariables('[&GetAudioDevices:Resolve(Device List Output)]'), "[^\n]+") do

    ContextIndex = ContextIndex + 1
    AudioDeviceInfos = {}

    for j in string.gmatch(i, "[^;]+") do
      table.insert(AudioDeviceInfos, j)
    end

    AudioDeviceID = AudioDeviceInfos[1]
    AudioDeviceName = AudioDeviceInfos[2]

    SKIN:Bang("!SetOption", "Rainmeter", "ContextTitle" .. ContextIndex, AudioDeviceName)
    SKIN:Bang("!SetOption", "Rainmeter", "ContextAction" .. ContextIndex, '[!WriteKeyValue Variables AudioDeviceName "' .. AudioDeviceName .. '" "#@#Variables/Common.inc"][!WriteKeyValue Variables AudioDeviceID "ID: ' .. AudioDeviceID .. '" "#@#Variables/Common.inc"][!RefreshGroup [#GroupName]]')

  end
end
```

</details> -->

## Unused Parameters

When experemnitning with the plugin, you don't need to remove and readd the parameter to see what it does. Instead, you can just change it's name, for example add another character or a number to it so that the plugin wouldn't recognize it.

For example:

```ini
Unit-UnitName=Channels ... | Handlers ... | TargetRate 44100 | Filter like-a
```

You don't need to remove `TargetRate` nor `Filter` parameters to see the difference they make. Simply change there names a bit:

```ini
Unit-UnitName=Channels ... | Handlers ... | Target Rate 44100 | Filter1 like-a
```

Now the plugin will use the default value of these parameters, and will send a log message about unused parameters `Target` and `Filter1`. If you want to use them again just fix there names.

?>You can use this method with any handler, but it only works if the parameter has a default value.

## Plugin UpdateRate

In `Threading` option, there is a parameter called `Policy`, when using `SeparateThread`, you can specify at which update rate the plugin updates it's values.

We mentioned that `UpdateRate 60` in threading means that 60 times per second plugin will try to fetch new data from windows and then transfer that data to handlers for them to update.

Handlers can be updated several times per one update request (update request here is determined by `Threading` update rate), and they will keep their data as if there were more updates.

_"Effectively"_ handlers update at infinite speed, because they don't lose any intermediate values when you update them rarely, you just sample their values at your own not-so-high rate (determined by update rate in threading and update rate of the skin).

`UpdataRate 1000` in a handler (for example, in waveform) will mean that 1000 times per second handler will draw a new line on the image.<br/>
If threading have `UpdateRate 60`, then there will be 60 requests for update, during most of which handler will draw 17 lines.

---

Most of the time, increasing `UpdateRate` parameter above lets say.. 60 wouldn't make much difference.

But when using FFT with a lot of measures running in the skin, increasing `UpdateRate` further may help.

Remember the [Fps variable](/docs/tips-code?id=fps-variable) we made earlier? we can use it to specify the `UpdateRate`. Simply do this:

```ini
Threading=Policy SeparateThread | UpdateRate ([#Fps]*3)
```

About `*3`, we know that Fps variable won't be more than 60, also `UpdateRate` parameter only accepts from 1 to 200. Lets say Fps actually equals 60, that would make the `UpdateRate` 180. In some cases, this will give a bit better results in heavy skins.

---

Some handlers have UpdateRate parameter, don't confuse between that and the `Threading` UpdateRate.

## Channels in child measures

Lets take Loudness handler as an example.

First, `Channel` option in child measure should only have one channel:

```ini
; This is valid
Channel=Auto
; Or
Channel=FL

; This is invalid
Channel=Auto, R
; Or
Channel=FL, R
```

Second, channels are just values, so the name of the channel won't make any difference:

```ini
; This is fine
[ParentMeasure]
Unit-Main=Channels FL, R | Handlers ... | Filter ...

[ChildMeasure]
Channel=FL
; Or
Channel=R

; This is also fine
[ParentMeasure]
Unit-Main=Channels FL, R | Handlers ... | Filter ...

[ChildMeasure]
Channel=Left
; Or
Channel=Right
```

## Sound equalizers and Visualization

If you are using a sound equalizer, for example, to adjust the bass levels in your speakers, you should know that these changes affect visualization as well.<br>
Which means, the sounds is not visualized exactly as it is, what gets visualized the the sounds you actually hear.

For example, this is when using sound equalizer:

<img src="docs/examples/resources/eq-on.png">

And this is when it's disabled:

<img src="docs/examples/resources/eq-off.png">

## Helpful Websites

[Here](https://www.szynalski.com/tone-generator/) is a cool website that can generate frequencies, it can be very helpful when you are making a spectrum. Just remember to keep the volume under 90%, above that it will create some noise in frequencies.
