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

Since a user may have more than one audio device, we need a way to let them choose the one they want.

Luckily, the plugin will provide you with a list of connected audio devices, but first, you need to parse them with a lua script, and that's what we are going to do here.

?>You can find the full script at the very end of this tutorial. It's available in the [.rmskin]() as well.

<details>

`DeviceList` section variable will give us something like this:

```
{0.0.0.00000000}.{c73b9bf1-9f30-4a46-9786-c5d3d2c18aba};Realtek High Definition Audio;Speakers;Speakers;48000;fl,fr,;output;/<DeviceInfos2>/<DeviceInfos3>/...
```

We want to extract the DeviceID and DeviceName, but before we extract the name we need to unescape it.

Let's say your device name contains one of the following symbols: `%` `/` `;` <br/>
For example: `My%udio;DeviceN/me`

This will cause problems when parsing, because `/` symbol is used to separate audio devices (`DeviceInfos1/DeviceInfos2/...`), and `;` symbol is used to separate device infos (`DeviceID;DeviceName;...`), and `%` is used in lua regex.

To solve that problem, the plugin escapes these symbols as the following:

`%` is replaced with `%percent`<br/>
`;` is replaced with `%semicolon`<br/>
`/` is replaced with `%forwardslash`

So now your `DeviceName` is `My%percentudio%semicolonDeviceN%forwardslashme`

To unescape the name, we will make a function that takes a string, replace the words (`%percent`, `%semicolon`, `%forwardslash`) with symbols, then it gives us a new string.

```lua
function unescape(str)
  return str:gsub('%%percent', '%'):gsub('%%semicolon', ';'):gsub('%%forwardslash', '/')
end
```

Now let's start extracting the devices.<br/>
We will create another function, this function takes `DeviceList` string, extract each device, store it inside an array, then returns that array:

```lua
function CreateDevicesList(AudioDevices)
  local DevicesList = {}

  -- let's say the devices list looks like this:
  -- DeviceInfos1/DeviceInfos2/...

  for AudioDevice in AudioDevices:gmatch("([^/]+)/") do
    -- first time this loop  runs will give us DeviceInfos1
    -- second time DeviceInfos2
    -- and so on
  end
  return DevicesList
end
```

But before we insert the devices into that array, let's extract there infos.<br/>

Inside that loop, we will call a function that takes the `DeviceInfos` string, extract the infos, then store them into a table:

```lua
for AudioDevice in AudioDevices:gmatch("([^/]+)/") do
  local DeviceProperties = ParseDeviceProperties(AudioDevice)
  -- example: DeviceProperties = {id: "<DeviceID>", name: "<DeviceName>", ...}
end
```

Let's create that function.<br/>

```lua
function ParseDeviceProperties(DeviceProperties)
  local TempArray = {} -- after we extract the infos, we will store them temporarily in this array

  for property in DeviceProperties:gmatch("([^;]+);") do
  -- first time this loop runs will give us device id
  -- second time device name, and so on

  -- we will unescape the device infos then store them inside the temporary array
    property = unescape(property)
    table.insert(TempArray, property)
  end

  local DeviceInfos = {} -- we will make a table to store the device infos
  DeviceInfos.id = TempArray[1]
  DeviceInfos.name = TempArray[2]
  DeviceInfos.description = TempArray[3]
  DeviceInfos.formFactor = TempArray[4]
  DeviceInfos.sampleRate = TempArray[5]

  -- channels may be <unknown> if all channels of this device are not supported by the plugin
  if TempArray[6] == '<unknown>' then
    DeviceInfos.channels = '<unknown>'
  else
    DeviceInfos.channels = {} -- other wise we will store them into an array
    for channel in TempArray[6]:gmatch("([^,]+),") do
      table.insert(DeviceInfos.channels, channel)
    end
  end
  DeviceInfos.type = TempArray[7]

  return DeviceInfos
end
```

So, if we have the following DeviceList:

```
<DeviceID1>;<DeviceName1>;.../<DeviceID2>;<DeviceName2>;.../...
```

We will pass it to `CreateDeviceList` function to extract each device, then we pass each device to `ParseDeviceProperties` function to extract device infos, so we will end up with something like this:

```lua
{{id: "<DeviceID1>", name: "<DeviceName1>", ...}, -- DeviceInfos1
 {id: "<DeviceID2>", name: "<DeviceName2>", ...}, -- DeviceInfos2
 -- and so on
}
```

Now we need a way to display the devices to the user, to do that, we will use a skin as a context menu, then we will loop through the devices list, and for each device we will add its name to that menu.

?>The following skin is inspired by [@marcopixel](https://github.com/marcopixel) and [@alatsombath](https://github.com/alatsombath), a special thanks for them.

```ini
[Rainmeter]
Update=-1

; tell rainmeter: hay, we will use this skin as a context menu
OnRefreshAction=[!SkinCustomMenu]

; when clicking away, menu will close
OnUnfocusAction=[!DeactivateConfig]

; a parent measure to get DeviceList from
[GetAudioDevices]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Parent

; if a device is disconnected, connected, changed, menu will close
; because you need to reopne the menu to see the changes
OnDeviceListChange=[!DeactivateConfig]

; the actual script that will parse the DeviceList
[AudioDeviceList]
Measure=Script
ScriptFile=#@#Scripts\AudioDeviceList.lua

; rainmeter won't open skins with no meters
[DummyMeter]
Meter=String
```

But how we will add the devices to that menu? we will use bangs.<br/>
Also we will make these bangs run when the skin is opened.

1. We need a bang to add the device name to the context menu.
2. We need to run a bang when a device name is clicked.

The second bang will do few things:

- It will set the new device id in the active skins then updates them, to avoid refreshing the skins.
- It will store the device name and id to a variables file.

Since we want to change the device id in the active skins, we need to make a group so we can target them more easily.

Let's make a "common variables" file and add it to our skin:

```ini
[Variables]
GroupName=Examples
AudioDeviceName=
AudioDeviceID=
```

```ini
; in context menu skin
[Variables]
@IncludeC=#@#Variables/Common.inc
```

Now, how to use these variables?<br/>
Let's say you have the following skin:

```ini
[Rainmeter]
Update=[#UpdateRate]

[Variables]
Fps=30
UpdateRate=(1000 / #Fps#)

[MeasureAudio]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Parent
```

First you include the common variables inside it, then set the group option to `GroupName` variable.

And for parent measure, you set the source option to `AudioDeviceID`.

Now every time a user change the device using that menu, the skins will automatically reflect that change, without the need for a skin refresh.

```ini
[Rainmeter]
Update=[#UpdateRate]
Group=[#GroupName]

[Variables]
Fps=30
UpdateRate=(1000 / #Fps#)

@IncludeC=#@#Variables/Common.inc

[MeasureAudio]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Parent
Source=[#AudioDeviceID]
```

Now let's start making the bangs. Instead of creating them one by one, we will create a function that does that for us:

```lua
function CreateBang(GroupName, VarName, VarValue, VarFile)
  local  Bang =  ''
  Bang = Bang .. '[!SetVariableGroup "'        .. VarName .. '" "' .. VarValue .. '" '  .. GroupName .. ']'
  Bang = Bang .. '[!WriteKeyValue Variables "' .. VarName .. '" "' .. VarValue .. '" "' .. VarFile   .. '"]'
  return Bang
end
```

We will pass the group name, the variable name, the value of that variable, the location to where to store it, and it will give us a bang that looks like this:

```ini
[!SetVariableGroup "AudioDeviceName" "<DeviceName>" Examples][!WriteKeyValue Variables "AudioDeviceName" "<DeviceName>" "#@#Variables/Common.inc"]
[!SetVariableGroup "AudioDeviceID" "ID: <DeviceID>" Examples][!WriteKeyValue Variables "AudioDeviceID" "ID: <DeviceID" "#@#Variables/Common.inc"]
```

Last thing we need is creating a function that will generate the context menu items.

```lua
function CreateDevicesMenu(DevicesList)
end
```

Inside this function, we will need some local variables:

```lua
local GroupName = SKIN:GetVariable('GroupName') -- to get the group name you used in common variables
local VarDevName = 'AudioDeviceName'
local VarDevId = 'AudioDeviceID'
local VarFile = '#@#Variables/Common.inc' -- common variables file path
local Bang -- we will need this in a moment
```

First 2 items we are going to make are the default input and default output.

```lua
-- "Default Input" Option
Bang = ''
Bang = Bang    CreateBang(GroupName, VarDevName, 'Default Input', VarFile)
Bang = Bang .. CreateBang(GroupName, VarDevId  , 'DefaultInput' , VarFile)
SKIN:Bang("!SetOption", "Rainmeter", "ContextTitle", 'Default Input')
SKIN:Bang("!SetOption", "Rainmeter", "ContextAction", Bang)

-- "Default Output" Option
Bang = ''
Bang = Bang    CreateBang(GroupName, VarDevName, 'Default Output', VarFile)
Bang = Bang .. CreateBang(GroupName, VarDevId  , 'DefaultOutput' , VarFile)
SKIN:Bang("!SetOption", "Rainmeter", "ContextTitle2", 'Default Output')
SKIN:Bang("!SetOption", "Rainmeter", "ContextAction2", Bang)
```

Now for each device in the array that `CreateDevicesList` gave us, we will create a menu item.

But there is something we need to account for:

In `ParseDeviceProperties` function, when we were storing the device infos, we checked if the device channels are `<unknown>`, if that's the case then device channels will be `<unknown>`.

But we can't display a device with unknown channels to the user, because when they select it they may not know why it's not working.

So we need to add a note beside the device name, something like "Unsupported Channels".

```lua
-- Audio Devices
for i, DeviceProperties in pairs(CreateDevicesList(DevicesList)) do
  local DeviceName = DeviceProperties.description -- for some reason, the windows api gives device name instead of device description and vise versa
  local DeviceId   = DeviceProperties.id

  if DeviceProperties.channels == '<unknown>' then
    DeviceName = DeviceName .. '(Unsupported Channels)'
  end

  Bang = ''
  Bang = Bang .. CreateBang(GroupName, VarDevName,        DeviceName, VarFile, VarDevName)
  Bang = Bang .. CreateBang(GroupName, VarDevId, 'ID: ' .. DeviceId, VarFile, VarDevId)

  SKIN:Bang("!SetOption", "Rainmeter", "ContextTitle"  .. (i + 2), DeviceName)
  SKIN:Bang("!SetOption", "Rainmeter", "ContextAction" .. (i + 2), Bang)
end
```

Finally to create the menu when the skin is opened, we are going to use `Initialize` function, and call `CreateDeviceMenu` inside it.

`CreateDeviceMenu` takes a DeviceList as an argument, we are going to use the `SKIN` object that rainmeter provides to get the `DeviceList` from the parent measure.

```lua
function Initialize()
  CreateDevicesMenu(SKIN:ReplaceVariables('[&GetAudioDevices:Resolve(DeviceList)]'))
end
```

Here is the full script:

```lua
--[[
  Special thanks to both of alatsombath (Github: alatsombath)
  and marcopixel (Github: marcopixel) for the context menu inspiration
]]

function Initialize()
  CreateDevicesMenu(SKIN:ReplaceVariables('[&GetAudioDevices:Resolve(DeviceList)]'))
end

function unescape(str)
  return str:gsub('%%percent', '%'):gsub('%%semicolon', ';'):gsub('%%forwardslash', '/')
end

function ParseDeviceProperties(DeviceProperties)
  local TempArray = {}
  for property in DeviceProperties:gmatch("([^;]+);") do
    property = unescape(property)
    table.insert(TempArray, property)
  end

  if TempArray[6] == '<unknown>' then
    return nil
  end

  local DeviceInfos = {}
  DeviceInfos.id = TempArray[1]
  DeviceInfos.name = TempArray[2]
  DeviceInfos.description = TempArray[3]
  DeviceInfos.formFactor = TempArray[4]
  DeviceInfos.sampleRate = TempArray[5]
  if TempArray[6] == '<unknown>' then
    DeviceInfos.channels = '<unknown>'
  else
    DeviceInfos.channels = {}
    for channel in TempArray[6]:gmatch("([^,]+),") do
      table.insert(DeviceInfos.channels, channel)
    end
  end
  DeviceInfos.type = TempArray[7]

  return DeviceInfos
end

function CreateBang(GroupName, VarName, VarValue, VarFile)
  local  Bang =  ''
  Bang = Bang .. '[!SetVariableGroup "'        .. VarName .. '" "' .. VarValue .. '" '  .. GroupName .. ']'
  Bang = Bang .. '[!WriteKeyValue Variables "' .. VarName .. '" "' .. VarValue .. '" "' .. VarFile   .. '"]'
  return Bang
end

function CreateDevicesMenu(DevicesList)
  local GroupName = SKIN:GetVariable('GroupName')
  local VarDevName = 'AudioDeviceName'
  local VarDevId = 'AudioDeviceID'
  local VarFile = '#@#Variables/Common.inc'
  local Bang

  -- "Default Input" Option
  Bang = ''
  Bang = Bang    CreateBang(GroupName, VarDevName, 'Default Input', VarFile)
  Bang = Bang .. CreateBang(GroupName, VarDevId  , 'DefaultInput' , VarFile)
  SKIN:Bang("!SetOption", "Rainmeter", "ContextTitle", 'Default Input')
  SKIN:Bang("!SetOption", "Rainmeter", "ContextAction", Bang)

  -- "Default Output" Option
  Bang = ''
  Bang = Bang    CreateBang(GroupName, VarDevName, 'Default Output', VarFile)
  Bang = Bang .. CreateBang(GroupName, VarDevId  , 'DefaultOutput' , VarFile)
  SKIN:Bang("!SetOption", "Rainmeter", "ContextTitle2", 'Default Output')
  SKIN:Bang("!SetOption", "Rainmeter", "ContextAction2", Bang)

  -- Audio Devices
  for i, DeviceProperties in pairs(CreateDevicesList(DevicesList)) do
    local DeviceName = DeviceProperties.description
    local DeviceId   = DeviceProperties.id

    if DeviceProperties.channels == '<unknown>' then
      DeviceName = DeviceName .. '(Unsupported Channels)'
    end

    Bang = ''
    Bang = Bang .. CreateBang(GroupName, VarDevName,        DeviceName, VarFile, VarDevName)
    Bang = Bang .. CreateBang(GroupName, VarDevId, 'ID: ' .. DeviceId, VarFile, VarDevId)

    SKIN:Bang("!SetOption", "Rainmeter", "ContextTitle"  .. (i + 2), DeviceName)
    SKIN:Bang("!SetOption", "Rainmeter", "ContextAction" .. (i + 2), Bang)
  end
end

function CreateDevicesList(AudioDevices)
  local DevicesList = {}
  for AudioDevice in AudioDevices:gmatch("([^/]+)/") do

    local DeviceProperties = ParseDeviceProperties(AudioDevice)
    if DeviceProperties ~= nil then
      table.insert(DevicesList, DeviceProperties)
    end

  end
  return DevicesList
end
```

The context menu skin:

```ini
[Rainmeter]
Update=-1
OnRefreshAction=[!SkinCustomMenu]
OnUnfocusAction=[!DeactivateConfig]

[Variables]
@IncludeC=#@#Variables/Common.inc

[GetAudioDevices]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Parent
OnDeviceListChange=[!DeactivateConfig]

[AudioDeviceList]
Measure=Script
ScriptFile=#@#Scripts\AudioDeviceList.lua

[DummyMeter]
Meter=String
```

</details>

## Unused Parameters

When experemnitning with the plugin, you don't need to remove and readd the parameter to see what it does. Instead, you can just change it's name, for example add another character or a number to it so that the plugin wouldn't recognize it.

For example:

```ini
Unit-UnitName=Channels ... | Handlers ... | TargetRate 44100 | Filter like-a
```

You don't need to remove `TargetRate` or `Filter` parameter to see the difference they make. Simply change there names a bit:

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
