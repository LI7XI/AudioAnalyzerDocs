## How to setup a skin

In this example, we will create a [Specturm]() Visualizer.

First of all, lets create a skin:

```ini
[Rainmeter]
Update=32
;To make a background for the skin
BackgroundMode=2
SolidColor=0,0,0,100
```

Simple skin with low update rate (`Update=32` = 30Fps). Low update rate is needed to make values update faster.

This is how you setup the plugin:

!> Note: all option names and properties here are case-insensitive. Which means `Option=Something` is equal to `oPTioN=soMThInG` . <br/> We will keep using Upper Case letter of each word just for convention.

We create a measure, and specify it as a [Parent]().

```ini
[MeasureAudio]
Measure=Plugin
Plugin=AudioAnalyzer_1_1
Type=Parent
```

Then we specify the [MagicNumber]().

```ini
MagicNumber=104
```

Then we make a [Process](). Lets call it Main.

```ini
Processing=Main
```

Then we specify its Description.

Unlike other plugins, this plugin follows a syntax similar to [Shape meter]().

First, to speceify a process description we write processing, followed by a hyphen, then the process name.

```ini
Processing-Main=
```

Here we speceify the [process properties](), Like [Channels](), [Handlers]() and other properties seperated by a '|' (pipe symbol).

```ini
Processing-Main=Channels Auto | Handlers MainHandler | Filter Like-a
```

a property may have more than one option, we can write multible comma-separated options. Like so:

```ini
Processing-Main=Channels Left, Right | Handlers MainHandler1, MainHandler2 | Filter Like-a
```

Now lets speceify what handlers do. <br/>
We write Handler, followed by a hyphen, then the handler name.

```ini
Handler-MainHandler1=
```

Then we speceify its [Type]().

There are many types avalible, in this example we will choose [fft]() type, since we are going to create a [Specturm]().

```ini
Handler-MainHandler1=Type fft
```

After we set the type, we need to speceify its properties.

```ini
Handler-MainHandler1=Type fft | binWidth 10 | overlapBoost 10 | cascadesCount 3
```

Handler of type fft is not very useful on its own.<br/>
So handlers can be chained to modify how the signal is outputted.

We do that by speceifing a second handler, and set the first handler as its source. <br/>
Then we speceify its properties like any other type.

```ini
Handler-MainHandler1=Type fft | BinWidth 5 | OverlapBoost 10 | CascadesCount 3
Handler-MainHandler2=Type BandResampler | source MainHandler1 | bands log 5 20 4000
```

To make a finer output, we can chain more handlers together.

!> Don't forget to add there names in the [process properties]().<br/>
If you forgot to add them, The plugin will simply output a warning in Rainmeter log window.

Also Lets rename them to keep things more descriptive.

```ini
Processing-Main=Channels Auto | Handlers Mainfft, MainResampler, MainTransform, MainFilter, MainMapper | filter like-a

Handler-Mainfft=Type fft | BinWidth 5 | OverlapBoost 10 | CascadesCount 3
Handler-MainResampler=Type BandResampler | Source Mainfft | Bands log 5 20 4000
Handler-MainTransform=Type BandCascadeTransformer | Source MainResampler | MinWeight 0 | TargetWeight 100
Handler-MainFilter=Type TimeResampler | Source MainTransform | Attack 100
Handler-MainMapper=Type ValueTransformer | Source MainFilter | Transform db map[from -50 : -0] clamp
```

_Todo: Does the handlers arrangement matter? (in performance and output quality)._

Now the Parent measure is ready.:tada:

Lets create the Child measures.<br/>
Child measures grab processed data from Parent measures.

We make a Child measure, and specify its Parent.

```ini
[MeasureBand0]
Measure=Plugin
Plugin=AudioAnalyzer_1_1
Type=Child
Parent=MeasureAudio
```

Then we specify the Channel to get data from.

```ini
Channel=Auto
```

Then we specify the Index.

Since we used fft Type then a BandResampler, it provides an Index range starting from 0 to Bands-1. (Bands here means the bands we specified in [`Mainftt` handler properties]()).

```ini
Index=0
```

?> Now notice the following.

Even though we specified the Parent Meausre, Child measures still need to know which value to retrieve.<br/>
That's because a Parent measure may have more than one process or multible handlers.

So to tell the Child measure which value to read data from, we use an option called `ValueID`.

In this option specify which handler to read data from.<br/>
It can be any handler, But you should always use the last handler specified in the [process description](). In our case it would be `MainMapper`.

```ini
ValueID=MainMapper
```

Now we are ready to make the spectrum.:tada:

It's just a matter of making bar meters, and set there `MeasureName` option to the target band.

Here is the full skin:

```ini
[Rainmeter]
Update=32
;To make a background for the skin
BackgroundMode=2
SolidColor=0,0,0,100

[MeasureAudio]
Measure=Plugin
Plugin=AudioAnalyzer_1_1
Type=Parent
MagicNumber=104

Processing=Main
Processing-Main=Channels Auto | Handlers Mainfft, MainResampler, MainTransform, MainFilter, MainMapper | filter like-a

Handler-Mainfft=Type fft | BinWidth 5 | OverlapBoost 10 | CascadesCount 3
Handler-MainResampler=Type BandResampler | Source Mainfft | Bands log 5 20 4000
Handler-MainFilter=Type TimeResampler | Source MainTransform | Attack 100
Handler-MainMapper=Type ValueTransformer | Source MainFilter | Transform db map[from -50 : -0] clamp

[MeasureBand0]
Measure=Plugin
Plugin=AudioAnalyzer_1_1
Type=Child
Parent=MeasureAudio
Channel=Auto
Index=0
ValueID=MainMapper

[MeasureBand1]
Measure=Plugin
Plugin=AudioAnalyzer_1_1
Type=Child
Parent=MeasureAudio
Channel=Auto
Index=1
ValueID=MainMapper

[MeasureBand2]
Measure=Plugin
Plugin=AudioAnalyzer_1_1
Type=Child
Parent=MeasureAudio
Channel=Auto
Index=2
ValueID=MainMapper

[MeasureBand3]
Measure=Plugin
Plugin=AudioAnalyzer_1_1
Type=Child
Parent=MeasureAudio
Channel=Auto
Index=3
ValueID=MainMapper

[MeasureBand4]
Measure=Plugin
Plugin=AudioAnalyzer_1_1
Type=Child
Parent=MeasureAudio
Channel=Auto
Index=4
ValueID=MainMapper

[MeterStyles]
X=15r
Y=0
W=10
H=100
BarColor=255,255,255,255
BarOrientation=Vertical

[MeterBand0]
Meter=Bar
MeasureName=MeasureBand0
X=0
Y=0
W=10
H=100
BarColor=255,255,255,255
BarOrientation=Vertical

[MeterBand1]
Meter=Bar
MeterStyle=MeterStyles
MeasureName=MeasureBand1

[MeterBand2]
Meter=Bar
MeterStyle=MeterStyles
MeasureName=MeasureBand2

[MeterBand3]
Meter=Bar
MeterStyle=MeterStyles
MeasureName=MeasureBand3

[MeterBand4]
Meter=Bar
MeterStyle=MeterStyles
MeasureName=MeasureBand4
```

## Results:

<img src="resources\skin-setup.PNG" title="Specturm Visualizer" />

_Todo: Add a gif._
