## How to setup a skin

In this example, we will create a [Spectrum](/docs/examples/spectrum.md) Visualizer.<br/>
To keep it short and simple, it won't be as fancy as the one in the [.rmskin]() examples. Later on, we will show you [how to create it](/docs/usage-examples/fft-spectrum).

First of all, lets create a skin:

```ini
[Rainmeter]
Update=32
;To make a background for the skin
BackgroundMode=2
SolidColor=0,0,0,100
```

Simple skin with low update rate (`Update=32` = 30Fps). Low update rate is needed to make the skin update faster.

This is how you setup the plugin:

?>Note: all option names and parameters here are case-insensitive. Which means `Option=Something` is equal to `oPTioN=soMThInG`. <br/> We will keep using [CamelCase](https://en.wikipedia.org/wiki/Camel_case) easier reading.

!>Processing Unit names and Handler names can **only** contain Characters, Numbers and/or Underscores.

For example:

```ini
; This is valid:
MainHandler1, Main_Handler_1, mAin_HAnDlER1
; This is invalid:
M@in$h^&le-r
```

With that out of the way, Lets start!

We create a measure, and specify it as a [Parent](/docs/plugin-structure/plugin-structure?id=how-to-determine-the-measure-type).

```ini
[MeasureAudio]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Parent
```

Then we make a [Processing Unit](/docs/plugin-structure/parent?id=processing-units). Lets call it `Main`.

```ini
ProcessingUnits=Main
```

Then we specify its Description. Unlike other plugins, this plugin follows a syntax similar to [Shape meter](https://docs.rainmeter.net/manual-beta/meters/shape/).

First, to specify a process description we write "Unit", followed by a hyphen, then the process name.

```ini
Unit-Main=
```

Here we specify the [Process parameters](/docs/plugin-structure/parent?id=unit-unitname), Like [Channels](/docs/plugin-structure/parent?id=parent-channel-para), <i id="parent-handler-para"></i>[Handlers](/docs/plugin-structure/parent?id=parent-handler-para) and other parameters separated by a pipe symbol (`|`).

```ini
Unit-Main=Channels Auto | Handlers MainHandler | Filter Like-a
```

A parameter may have more than one value, we can write multiple comma-separated values. For example:

```ini
Unit-Main=Channels Left, Right | Handlers MainHandler1, MainHandler2 | Filter Like-a
```

Now lets specify what handlers do. <br/>
We write Handler, followed by a hyphen, then the handler name.

```ini
Handler-MainHandler1=
```

Then we specify its [Type](/docs/handler-types/handler-types.md).

There are many types available, in this example we will choose [FFT](/docs/handler-types/fft/fft.md) type, since we are going to create a Spectrum.

```ini
Handler-MainHandler1=Type FFT
```

After we set the type, we need to specify its parameters.

```ini
Handler-MainHandler1=Type FFT | BinWidth 5 | OverlapBoost 5 | CascadesCount 1
```

Handler of type FFT is not very useful on its own.<br/>
So handlers can be chained to modify how the signal is outputted.

We do that by specifying a second handler, then we specify its parameters like any other type.

```ini
Handler-MainHandler1=Type FFT | BinWidth 5 | OverlapBoost 5 | CascadesCount 1
Handler-MainHandler2=Type BandResampler | Bands Log(Count 5, Min 20, Max 4000)
```

And then we set the first handler as its source. To do that, we go back to the process description, and right after the name of the handler we want to set its source, we open parentheses and inside them we specify the name of source handler.

```ini
Unit-Main=Channels Auto | Handlers MainHandler1, MainHandler2(MainHandler1) | Filter Like-a
```

To make a finer output, we can chain more handlers together.

!> Don't forget to add there names in the Process [Handlers](#parent-handler-para) list.<br/>
If you forgot to add them, the plugin will stop working after outputting an error in Rainmeter log window.

Also Lets rename them to keep things more descriptive.

```ini
Unit-Main=Channels Auto | Handlers MainFFT, MainResampler(MainFFT), MainTransform(MainResampler), MainFilter(MainTransform), MainMapper(MainFilter) | Filter like-a

Handler-MainFFT=Type FFT | BinWidth 5 | OverlapBoost 5 | CascadesCount 3
Handler-MainResampler=Type BandResampler | Bands log(Count 5, Min 20, Max 4000)
Handler-MainTransform=Type BandCascadeTransformer | MinWeight 0 | TargetWeight 100
Handler-MainFilter=Type TimeResampler | Attack 100
Handler-MainMapper=Type ValueTransformer | Transform dB, Map(From -50 : -0), Clamp
```

Now the Parent measure is ready.:tada:

Lets create the Child measures.<br/>
Child measure grab processed data from Parent measure.

We make a Child measure, and specify its Parent.

```ini
[MeasureBand0]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Child
Parent=MeasureAudio
```

Then we specify the Channel to get data from.

```ini
Channel=Auto
```

Then we specify the Index.

Since we used `FFT` Type then a `BandResampler`, it will provides an Index range starting from `0` to `Bands-1`. (Bands here means the `BandsCount` we specified in [`MainResampler` handler parameter](/docs/handler-types/fft/band-resampler?id=bands)).

```ini
Index=0
```

?>Now notice the following.

Even though we specified the Parent Measure, Child measures still need to know which value to retrieve.<br/>
That's because a Parent measure may have more than one Process or multiple Handlers.

So to tell the Child measure which data handler to read values from, we use an option called [HandlerName](/docs/plugin-structure/child?id=handler-name).

In this option we specify which handler to read data from.<br/>
It can be any handler, in our case we will use the last handler (`MainMapper`).
Because it has the values we want to visualize.

```ini
HandlerName=MainMapper
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
Plugin=AudioAnalyzer
Type=Parent
MagicNumber=104

ProcessingUnits=Main
Unit-Main=Channels Auto | Handlers MainFFT, MainResampler(MainFFT), MainTransform(MainResampler), MainFilter(MainTransform), MainMapper(MainFilter) | Filter like-a

Handler-MainFFT=Type FFT | BinWidth 5 | OverlapBoost 5 | CascadesCount 3
Handler-MainResampler=Type BandResampler | Bands log(Count 5, Min 20, Max 4000)
Handler-MainTransform=Type BandCascadeTransformer | MinWeight 0 | TargetWeight 100
Handler-MainFilter=Type TimeResampler | Attack 100
Handler-MainMapper=Type ValueTransformer | Transform dB, Map(From -50 : -0), Clamp

[MeasureBand0]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Child
Parent=MeasureAudio
Channel=Auto
Index=0
HandlerName=MainMapper

[MeasureBand1]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Child
Parent=MeasureAudio
Channel=Auto
Index=1
HandlerName=MainMapper

[MeasureBand2]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Child
Parent=MeasureAudio
Channel=Auto
Index=2
HandlerName=MainMapper

[MeasureBand3]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Child
Parent=MeasureAudio
Channel=Auto
Index=3
HandlerName=MainMapper

[MeasureBand4]
Measure=Plugin
Plugin=AudioAnalyzer
Type=Child
Parent=MeasureAudio
Channel=Auto
Index=4
HandlerName=MainMapper

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

## Results

<video src="docs/examples/resources/simple-spectrum.mp4" autoplay loop muted title="Simple Spectrum"></video>

This example is also available in the .rmskin package.
