## Settings Skin

In this example we are going to create a settings panel for our skins.<br/>
To keep it short, we only gonna explain how to let the user choose which audio device the plugin should use, but it's pretty easy to add your own options.

?>This example is inspired by [@marcopixel](https://github.com/marcopixel) Lano-Visualizer, and the context menu code used in the lua script is inspired by [@alatsombath](https://github.com/alatsombath). A special thanks for them.

!>If something looks unclear, take a look at this [tutorial](/docs/tips-code?id=audio-devices-list).

First let's setup the skin.

```ini
[Rainmeter]
Update=200
Group=[#GroupName]
```

Let's make some variables, we will use them to make the background and position the meters.

```ini
[Variables]
SkinW=520
SkinH=105

@IncludeC=#@#Variables/Common.inc
```

Now let's make a background for our skin.<br/>
We will use a shape meter and set it's `UpdateDivider` to -1, then we will make a rectangle and set it's width and height to the variables we created earlier.

```ini
[MeterBG]
Meter=Shape
X=0
Y=0
Shape=Rectangle 0,0,#SkinW#,#SkinH#,5 | Fill Color 0,0,0,100 | StrokeWidth 0
UpdateDivider=-1
```

Also let's add a close button.

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

Now let's make some reusable styles. Since we may want to make more than one option.

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

Let's create a label.

```ini
[Lable1]
Meter=String
MeterStyle=LableStyle
Y=15R
Text=Audio Device
```

Now let's create an option.

```ini
[Option1]
Meter=String
MeterStyle=OptionStyle
Y=-19R
Text=Current: [#AudioDeviceName]
LeftMouseDownAction=[!ActivateConfig "#RootConfig#\Settings\AudioDevices" "AudioDevices.ini"]
```

This option will display the current audio device name. When clicking on it, it will open another skin as a drop down to select the audio device.

Now let's create the drop down list.<br/>
We will use the skin and script we made [here](/docs/tips-code?id=audio-devices-list) to create the menu.

The skin:

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

The script:

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

That's all!

<img src="docs\usage-examples\resources\settings-skin.png" title="Settings Skin" />
