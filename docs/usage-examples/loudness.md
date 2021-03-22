## Loudness Example

Here we will create a simple Loudness meter.

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
We will make 2 handlers, and set the first handler as a source for the second handler.

- `LoudnessdB` will process the audio signal and give us loudness levels in decibel.
- `LoudnessPercent` Will convert decibel to `[0, 1]` range to be used in meters.

Also we are going to use `like-a` filter, without it, the results will look totally different.

```ini
Unit-Main=Channels Auto | Handlers LoudnessdB, LoudnessPerecnt(LoudnessdB) | Filter like-a
```

Now lets specify the handlers description.

```ini
Handler-LoudnessdB=Type Loudness | Transform dB
Handler-LoudnessPerecnt=Type ValueTransformer | Transform Map(From -60 : 0), Clamp
```

That's it! as simple as that.<br/>
Of course you can specify more parameters in `LoudnessdB` handler and customize it however you like.

Better yet, you can even do everything in one handler, for example:

```ini
Unit-Main=Channels Auto | Handlers Loudness | Filter like-a
Handler-Loudness=Type Loudness | Transform dB, Map(From -60 : 0), Clamp | TimeWindow 500
```

But we wanna be extra fancy, so let's keep using 2 handlers ;)

Now lets create the child measures.<br/>
Each measure will get its data from a different handler.

```ini
[MeasureLoudnessdB]
Measure=plugin
Plugin=AudioAnalyzer
Type=Child
Parent=MeasureAudio
Channel=Auto
HandlerName=LoudnessdB

[MeasureLoudness]
Measure=plugin
Plugin=AudioAnalyzer
Type=Child
Parent=MeasureAudio
Channel=Auto
HandlerName=LoudnessPerecnt
```

Now your skin is ready to use.<br/>
Just make any meter you like (`Bar`, `Line`, `Shape`, `String`, etc..) and use these measures.

<img src="docs\usage-examples\resources\loudness.png" title="Loudness meter" />

## Loudness levels for different channels

So far we used the `Auto` channel to get loudness levels, which is more like average between audio channels.<br/>
But how about getting Loudness levels for each channel separately? lets do that!

The setup won't change that much, there are few things to change:

- Channels list in the processing unit.
- Channel option in child measures.
- HandlerName option in child measures.

Simply change `Channels Auto` in `Main` unit description and set it to `Channels Auto`, `FR, Right`, or any combination of channels you like.<br/>
In our case we want the `Left` and `Right` channels. Also we can do everything in one handler.

```ini
; We can keep the auto channel and just add left and right channels
Unit-Main=Channels Auto, FL, R | Handlers Loudness | Filter like-a
; Or just use the channels we exactly want
Unit-Main=Channels FL, R | Handlers Loudness | Filter like-a
```

Now lets make the child measures use these channels.<br/>
To do that, simply change `Channel` option in child measure to the target channel, like so:

```ini
Channel=FL
; Or
Channel=R
```

!>There are few things to note when dealing with channels.<i id="channels"></i>

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

Second, the channel name in `Channel` option should be exactly as specified in the process description:

```ini
; This is valid
[ParentMeasure]
Unit-Main=Channels FL, R | Handlers Loudness | Filter like-a

[ChildMeasure]
Channel=FL
; Or
Channel=R

; This is invalid
[ParentMeasure]
Unit-Main=Channels FL, R | Handlers Loudness | Filter like-a

[ChildMeasure]
Channel=L
; Or
Channel=Right
```

Lets change the `HandlerName` option and set it to `Loudness` since we removed the second handler and now both of child measures will get data from the same handler.

```ini
HandlerName=Loudness
```

Now your multi-channel setup is ready!

<img src="docs\usage-examples\resources\loudness-lr.png" title="LR Loudness meter" />

You can use the same approach for `5.1` and `7.1` audio channels.
