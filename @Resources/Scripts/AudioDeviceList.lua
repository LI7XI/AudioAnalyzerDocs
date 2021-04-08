--[[ 
  Special thanks to alatsombath (Github: alatsombath) for creating this method
  And to marcopixel (Github: marcopixel) for the inspiration
 ]]

function Initialize()
  ContextIndex = 1

  for i in string.gmatch(SKIN:ReplaceVariables('[&GetAudioDevices:Resolve(DeviceList)]'), "[^/]+") do
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