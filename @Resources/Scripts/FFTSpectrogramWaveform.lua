function Initialize()
  Bands = tonumber(SELF:GetOption('BandsCount', 1))

  MeasureBandsFP  = SKIN:MakePathAbsolute(SKIN:ReplaceVariables("#@#Measures\\FFTSpectrogramWaveform.inc"))
  MeterSpectrumFP = SKIN:MakePathAbsolute(SKIN:ReplaceVariables("#@#Meters\\FFTSpectrogramWaveform.inc"))

  GenerateAll(Bands)
end

function GenerateMeasureBands(Bands)
  MeasureBands = io.open(MeasureBandsFP, "w")

  for i = 0, (Bands - 1) do
    MeasureBands:write("[MeasureBand" .. i .. "]\n")
    MeasureBands:write("Measure=Plugin\n")
    MeasureBands:write("Plugin=AudioAnalyzer\n")
    MeasureBands:write("Parent=MeasureAudio\n")
    MeasureBands:write("Type=Child\n")
    MeasureBands:write("Index=" .. i .. "\n")
    MeasureBands:write("Channel=Auto\n")
    MeasureBands:write("HandlerName=ReMaper\n")
    MeasureBands:write("\n")
  end

  MeasureBands:close()
end

function GenerateMeterSpectrum(Bands)
  MeterSpectrum = io.open(MeterSpectrumFP, "w")

  MeterSpectrum:write("[MeterSpectrum]\n")
  MeterSpectrum:write("Meter=Shape\n")
  MeterSpectrum:write("X=300\n")
  MeterSpectrum:write("Y=0\n")

  MeterSpectrum:write("; ---------------------------------------------------------------------------------------------\n")
  MeterSpectrum:write("Shape=Rectangle #BarX#,#MaxHeight#,#BarWidth#,(Neg([MeasureBand0])),#Radius# | #Fill# | #Stroke#\n")
  MeterSpectrum:write("; ---------------------------------------------------------------------------------------------\n")
  
  for i = 1, (Bands - 1) do
    MeterSpectrum:write("Shape"..(i + 1).."=Rectangle #BarX#,#MaxHeight#,#BarWidth#,(Neg([MeasureBand".. i .."])),#Radius# | #Fill# | #Stroke# | Offset (#BarXR#*" .. i .. "),(#BarYR#)\n")
    MeterSpectrum:write("; ---------------------------------------------------------------------------------------------\n")
  end

  MeterSpectrum:write("DynamicVariables=1\n")
  MeterSpectrum:close()
end

function GenerateAll(Bands)
  Bands = Bands or 1
  GenerateMeasureBands(Bands)
  GenerateMeterSpectrum(Bands)
end