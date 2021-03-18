## Settings Skin

In this example we are going to create a settings panel for our skins.<br/>
To keep it short, we only gonna explain how to let the user choose which audio device the plugin should use, but it's pretty easy to add your own options.

?>This example is highly inspired by [@marcopixel](https://github.com/marcopixel) Lano-Visualizer, also a lot of the code used in the lua script is inspired by [@alatsombath](https://github.com/alatsombath). A special thanks for both of them.

First lets setup the skin.

```ini
[Rainmeter]
Update=200
Group=[#GroupName]
```

Lets make some variables, we will use them to make the background and place the meters.

```ini
[Variables]
SkinW=520
SkinH=105

@IncludeC=#@#Variables/Common.inc
```

Now make a new file called Common, we will include it in every skin.<br/>
This is what it contains:

```ini
[Variables]
GroupName=Examples
AudioDeviceName=Default
AudioDeviceID=DefaultOutput
```

Since we are going to retrieve the audio device name/id dynamically, it makes sense to make a variable for it, and just use that variable in every parent measure.

Also after the user chooses a device, we want to reflect those changes, to do that, the skins must be refreshed (because we gonna use `!WriteValueKey` bang), so we gonna execute another bang that refreshes the skin group called "Examples".

The reason we made a variable for the group name is to make it easier for later changes, for example if you wanted to use it in your skin.

Now lets make a background for our skin.<br/>
We will use a shape meter and set it's `UpdateDivider` to -1. Then we will make a rectangle and set it's width and height to the variables we created earlier.

```ini
[MeterBG]
Meter=Shape
X=0
Y=0
Shape=Rectangle 0,0,#SkinW#,#SkinH#,5 | Fill Color 0,0,0,100 | StrokeWidth 0
UpdateDivider=-1
```

Also lets add a close button as a nice addition.

We used [Character Reference Variables](https://docs.rainmeter.net/manual-beta/variables/character-variables/) to use an icon instead of text.<br/>
Check this straightforward [guide](https://forum.rainmeter.net/viewtopic.php?t=33765#p167081).

```ini
[CloseButton]
Meter=String
; To place the button at top right corner
X=(#SkinW#-(12*2.5))
Y=0
FontColor=255,255,255,230
FontSize=12
Padding=5,5,5,5
InlineSetting=Face | Font Awesome 5 Free
InlinePattern=[\xf057]
Text=[\xf057]
AntiAlias=1
MouseOverAction=[!SetOption #CurrentSection# FontColor "255,255,255,255"]
MouseLeaveAction=[!SetOption #CurrentSection# FontColor "255,255,255,200"]
LeftMouseDownAction=[!DeactivateConfig]
```

Now lets make some reusable styles. Since we may want to make more than one option.

```ini
[LabelStyle]
X=(#SkinW#/12)
FontColor=255,255,255,230
FontSize=12
AntiAlias=1

[OptionStyle]
X=(#SkinW#/2.3)
FontColor=255,255,255,190
FontSize=12
AntiAlias=1
```

Lets create a label.

```ini
[Lable1]
Meter=String
MeterStyle=LableStyle
Y=15R
Text=Audio Device
```

Now lets create an option.

```ini
[Option1]
Meter=String
MeterStyle=OptionStyle
Y=-19R
Text=Current: [#AudioDeviceName]
LeftMouseDownAction=[!ActivateConfig "#RootConfig#\Settings\AudioDevices" "AudioDevices.ini"]
```

This option will display the current audio device name. When clicking on it, it will open another skin as a drop down to select the audio device.<br/>
That skin has one purpose only, listing the available audio devices, and when a user chooses one of them, it refreshes all skins to reflect the changes.

Settings skin is completed :tada:

Now lets create the drop down list.

```ini
[Rainmeter]
Update=-1
OnRefreshAction=[!SkinCustomMenu]
OnUnfocusAction=[!DeactivateConfig]
; ------------------------------------
ContextTitle="Default"
ContextAction=[!WriteKeyValue Variables AudioDeviceName "Default" "#@#Variables/Common.inc"][!WriteKeyValue Variables AudioDeviceID "DefaultOutput" "#@#Variables/Common.inc"][!RefreshGroup [#GroupName]]
```

Since we don't know how many audio devices a user may have, we will make an option for the default one. It will update the variables and refreshes the skins.

We will include the common variables here as well.

```ini
[Variables]
@includeC=#@#Variables/Common.inc
```

Now lets make a parent measure.<br/>
It's a pretty simple one, the only need for it is to retrieve the available audio devices and there infos.

```ini
[GetAudioDevices]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Parent
MagicNumber=104
```

And lastly, we need a script measure, and a dummy meter because rainmeter will consider the skin invalid if no meters were found.

```ini
[ParseAudioDeviceList]
Measure=Script
ScriptFile=#@#Scripts\AudioDeviceList.lua

[DummyMeter]
Meter=String
```

Now let's make the script, for easier reading, we will use inline comments.

```lua
-- Initialize function will always run once each time the skin is refreshed
function Initialize()
  ContextIndex = 1

  -- We will use section variables in parent measure to get a list of audio devices
  -- The plugin will output each device infos in a new line
  for i in string.gmatch(SKIN:ReplaceVariables('[&GetAudioDevices:Resolve(Device List Output)]'), "[^\n]+") do
    -- Now each line contains something like this:
    -- {0.0.0.00000000}.{c73b9bf1-9f30-4a46-9786-c5d3d2c18aba};Realtek High Definition Audio;Speakers;Speakers;48000;fl,fr;
    -- For each line we gonna do the following

    -- First, increase the context index (since the context with index 1 is the "Default" we created earlier)
    ContextIndex = ContextIndex + 1

    -- Then we will create a new array to hold the infos of each device
    AudioDeviceInfos = {}

    -- Now, we will extract the infos using ; as a separator
    for j in string.gmatch(i, "[^;]+") do
    -- Then we store each info in AudioDeviceInfos array
      table.insert(AudioDeviceInfos, j)
    end
    -- The array now contains the following:
    -- AudioDeviceInfos = {"{0.0.0.00000000}.{c73b9bf1-9f30-4a46-9786-c5d3d2c18aba}", "Realtek High Definition Audio", "Speakers", "Speakers", "48000", "fl,fr"}

    -- We can access the infos using there index, 0 will be "nil" value so we will start from 1
    AudioDeviceID = AudioDeviceInfos[1]
    AudioDeviceName = AudioDeviceInfos[2]

    -- Since we are in a loop, and that loop is determined by how many audio devices the user may have, we will create a new option for each audio device
    SKIN:Bang("!SetOption", "Rainmeter", "ContextTitle" .. ContextIndex, AudioDeviceName)
    -- And when the user click on a device, we write the device name/id to there variables in Common file, then we refresh all skins
    SKIN:Bang("!SetOption", "Rainmeter", "ContextAction" .. ContextIndex, '[!WriteKeyValue Variables AudioDeviceName "' .. AudioDeviceName .. '" "#@#Variables/Common.inc"][!WriteKeyValue Variables AudioDeviceID "ID: ' .. AudioDeviceID .. '" "#@#Variables/Common.inc"][!RefreshGroup [#GroupName]]')

  end
  -- And we do that for each audio device the user might have.
end
```

And with that, we finished the settings skin!

<img src="docs\usage-examples\examples\settings-skin.png" title="Settings Skin" />
