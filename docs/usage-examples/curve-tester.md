## Curve Tester Example

The purpose of this example is showing you how different handler chains affect values.

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

Let's make a new processing unit. We will call it Main.

```ini
ProcessingUnits=Main
```

Let's specify its description.

?>For a better understanding of what's going on, we will make the full skin, then explain everything.

```ini
Unit-Main=Channels Auto | Handlers RMS -> RMSdB -> RMSFiltered, RMSFilteredDB(RMS) | Filter None
```

Now let's specify the handlers description.

```ini
Handler-RMS=Type RMS
Handler-RMSdB=Type ValueTransformer | Transform dB, Map(From -50 : 0), Clamp
Handler-RMSFiltered=Type TimeResampler | Attack 200
Handler-RMSFilteredDB=type TimeResampler | Attack 200 | Transform dB, Map(From -50 : 0), Clamp
```

Now let's create the child measures.<br/>

```ini
[MeasureRMS]
Measure=Plugin
Plugin=AudioAnalyzer
Parent=MeasureAudio
Type=Child
Channel=Auto
HandlerName=RMS

[MeasureRMSdB]
Measure=Plugin
Plugin=AudioAnalyzer
Parent=MeasureAudio
Type=Child
Channel=Auto
HandlerName=RMSdB

[MeasureRMSFiltered]
Measure=Plugin
Plugin=AudioAnalyzer
Parent=MeasureAudio
Type=Child
Channel=Auto
HandlerName=RMSFiltered

[MeasureRMSFilteredDB]
Measure=Plugin
Plugin=AudioAnalyzer
Parent=MeasureAudio
Type=Child
Channel=Auto
HandlerName=RMSFilteredDB
```

Let's make a background for the skin using a shape meter.

```ini
[MeterBG]
Meter=Shape
X=0
Y=0
Shape=Rectangle 0,0,300,150,10 | Fill Color 0,0,0 | StrokeWidth 0
UpdateDivider=-1
```

Now let's make a line meter to visualize the values.

```ini
[MeterRMS]
Meter=Line
X=0
Y=0
W=300
H=150
; ----------------------------
MeasureName=MeasureRMS
LineColor=255,100,0,255
; ----------------------------
MeasureName2=MeasureRMSdB
LineColor2=0,200,0,255
; ----------------------------
MeasureName3=MeasureRMSFiltered
LineColor3=0,180,255,255
; ----------------------------
MeasureName4=MeasureRMSFilteredDB
LineColor4=200,200,200,255
; ----------------------------
SolidColor=20,20,30,255
Container=MeterBG
AntiAlias=1
LineCount=4
```

And here is the results:

<img src="docs\usage-examples\resources\curve-tester.png" title="Curve tester" />

<span style="color: #ec9a53" >Orange</span> line (`RMS` handler) shows raw RMS value.

<span style="color: #64de78" >Green</span> line (`RMSdB` handler) shows RMS values converted to decibels. Its purpose is to show that you should always convert your values to decibels, because <span style="color: #ec9a53" >orange</span> line only reacts to very strong sound.

There are quiet sounds that you can still clearly hear, and which are you can see on <span style="color: #64de78" >green</span> line but can not see on <span style="color: #ec9a53" >Orange</span> line.<br/>
If you were to just ramp up value of RMS then it would show you quiet sounds but then loud sounds would just clip on the upper edge of the graph.

There are also <span style="color: #88b8ff" >blue</span> (`RMSFiltered` handler) and <span style="color: #fff" >white</span> (`RMSFilteredDB` handler) lines. Their purpose is to show that order of handlers matter.

<span style="color: #88b8ff" >Blue</span> line shows RMS values that were first converted into decibels and then filtered/smoothed. <span style="color: #fff" >White</span> line shows values that were first filtered/smoothed and then converted into decibels.<br/>
Sometimes the difference can be very noticeable. It's up to you to decide which way of calculations suits you better.

This example is available in the [.rmskin]() file.
