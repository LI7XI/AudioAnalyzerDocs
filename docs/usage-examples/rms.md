## RMS Example

Here we will create a simple RMS meter.

First lets setup the skin.

```ini
[Rainmeter]
Update=[#UpdateRate]

[Variables]
Fps=30
UpdateRate=(1000 / #Fps#)
; Formula is stolen from here: https://forum.rainmeter.net/viewtopic.php?t=26831#p140108
```

Now lets create the parent measure.

```ini
[MeasureAudio]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Parent
MagicNumber=104
```

Lets make a new processing unit. We will call it Main.

```ini
ProcessingUnits=Main
```

Lets specify its description.<br/>
We will use `Left` and `Right` channels since we want there RMS levels. But you can also use `Auto` channel to get the average RMS level of both channels.

```ini
Unit-Main=Channels Left, Right | Handlers RMS | Filter like-a
```

Now lets specify the handler description.

```ini
Handler-RMS=Type RMS | Transform dB, Map(From -50 : 0), Clamp | Attack 20 | Decay 40 | UpdateRate #Fps#
```

That's it, pretty simple!

Now lets create the child measures.<br/>
Both handlers will get there data from the same handler, but using different channels.

?>The same note about [channel names](/docs/usage-examples/loudness?id=channels) in Loudness meter applies here.

```ini
[MeasureRMSL]
Measure=Plugin
Plugin=AudioAnalyzer
Parent=MeasureAudio
Type=Child
Channel=Left
HandlerName=RMS

[MeasureRMSR]
Measure=Plugin
Plugin=AudioAnalyzer
Parent=MeasureAudio
Type=Child
Channel=Right
HandlerName=RMS
```

Now your skin is ready to use.<br/>
Just make any meter you like (`Bar`, `Line`, `Shape`, `String`, etc..) and use these measures.

![RMS](/examples/rms.png "RMS meter")
