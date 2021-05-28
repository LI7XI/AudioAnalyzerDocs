## RMS, Peak and Loudness

Here we will create a simple skin to visualize the difference between RMS, Peak and Loudness.

First let's setup the skin.

```ini
[Rainmeter]
Update=[#UpdateRate]

[Variables]
Fps=30
UpdateRate=(1000 / #Fps#)
; Formula is stolen from here: https://forum.rainmeter.net/viewtopic.php?t=26831#p140108
```

Now let's create the parent measure.

```ini
[MeasureAudio]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Parent
```

Let's make 2 processing units.<br/>
First one for loudness, and second one for rms and peak.

```ini
ProcessingUnits=Loudness, RMS_Peak
```

Loudness unit will have one handler, and it will use `like-a` filter preset.<br/>
RMS_Peak unit will have 2 handlers for RMS and Peak, but it won't use any filters.

```ini
Unit-Loudness=Channels Auto | Handlers Loudness  | Filter like-a
Unit-RMS_Peak=Channels Auto | Handlers RMS, Peak | Filter None
```

Now let's specify the handlers description.

```ini
Handler-Loudness=Type Loudness | Transform dB, Map(From -60 : 0), Clamp | UpdateRate [#Fps] | TimeWindow [#UpdateRate] | GatingLimit 0
Handler-Peak=    Type Peak     | Transform dB, Map(From -50 : 0), Clamp | UpdateRate [#Fps]
Handler-RMS=     Type RMS      | Transform dB, Map(From -50 : 0), Clamp | UpdateRate [#Fps]
```

That's all!

Let's create the child measures.

```ini
[MeasureLoudness]
Measure=Plugin
Plugin=AudioAnalyzer
Parent=MeasureAudio
Type=Child
Channel=Auto
HandlerName=Loudness

[MeasurePeak]
Measure=Plugin
Plugin=AudioAnalyzer
Parent=MeasureAudio
Type=Child
Channel=Auto
HandlerName=Peak

[MeasureRMS]
Measure=Plugin
Plugin=AudioAnalyzer
Parent=MeasureAudio
Type=Child
Channel=Auto
HandlerName=RMS
```

let's make a simple background using shape meter.

```ini
[MeterBG]
Meter=Shape
X=0
Y=0
Shape=Rectangle 0,0,300,148,10 | Fill Color 0,0,0 | StrokeWidth 0
UpdateDivider=-1
```

Now let's make a line meter to visualize the values.

```ini
[MeterLine]
Meter=Line
X=0
Y=0
W=300
H=150
; ----------------------------
MeasureName=MeasureLoudness
LineColor=255,160,0,255
; ----------------------------
MeasureName2=MeasurePeak
LineColor2=0,200,0,255
; ----------------------------
MeasureName3=MeasureRMS
LineColor3=0,180,255,255
; ----------------------------
SolidColor=10,10,20,255
Container=MeterBG
AntiAlias=1
LineCount=3
```

Now the skin is complete.

<img src="docs\usage-examples\resources\rms-peak-loudness.png" title="RMS, Peak and loudness" />
