## FFT Spectrum Example

Here we will create a simple Spectrum visualizer.

?>There are some TL;DR sentences here, feel free to skip the ones you already know.

First let's setup the skin.

```ini
[Rainmeter]
Update=[#UpdateRate]
; To make a cool background
BackgroundMode=2
GradientAngle=-90
SolidColor=0,0,0,100
SolidColor2=0,0,0,0

[Variables]
Fps=40
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

Let's specify its description.<br/>
We will create 5 handlers, each handler we create will be the source for the handler after it.

Since we are interested in 20 to 2000kHz frequencies, we can decrease the `TargetRate` to 8000, in fact, it's still more than enough for our needs.

Since we are making a spectrum, it's recommended to use `like-a` filter preset. But you can also specify custom filters if you want to.

```ini
Unit-Main=Channels Auto | Handlers MainFFT -> MainBR -> MainBCT -> MainTR -> MainFinalOutput | TargetRate 8000 | Filter like-a
```

- `MainFFT`: Handler of type `FFT` to generate frequency bins. The parameters we will use are:

  - `BinWidth`: This is similar to `FFTSize` in AudioLevel, it let's us specify the width of FFT result bin. We will set it to `10`.
  - `OverlapBoost`: This is similar to `FFTOverlap` in AudioLevel, it let's us reuse old data to update results faster, but depending on your settings, it will increase the CPU load. Let's set it to `6`.
  - `CascadesCount`: Think of this parameter as a divider for `BinWidth` to make it smaller (which corresponds to higher resolution), but only in low frequencies. Let's set it to `4`.

    <details><summary>More infos about <code>CascadesCount</code> parameter:</summary>

    In Fourier transform, there is a limitation, high frequencies (e.g. 800Hz and up) always update faster and have a higher resolution than low frequencies. No matter how small your `BinWidth` is, high frequencies will always have a higher resolution and still update faster than low ones.

    If you want to have a high resolution in low frequencies, you must have a small `BinWidth`. But that will make low frequencies update even slower.

    Why Is that?<br/>
    The delay problem lies in not having enough data to analyze, which makes it update slower.<br/>
    You can read more about this [here](https://electronics.stackexchange.com/questions/239730/performing-fft-at-low-frequencies-but-high-resolution).

    Also while you can have a small `BinWidth` to get high resolution, this high resolution is not limited to low frequencies only, but for the entire 22kHz frequency range. So we will be wasting performance on frequencies that are already detailed enough.

    You may think you can have a high resolution in both high and low frequencies and just crank up the `OverlapBoost`, this may work, but we have the same problem, and a new problem. We are wasting performance with having small `BinWidth` in all frequencies;<br/>
    And high frequencies are already detailed and they update faster, so this will make them even more detailed, but still update way faster.

    Here's where `CascadesCount` comes in to play, first we can get rid of the small `BinWidth`, this way we will get a slow and not detailed low frequencies, but high frequencies will still have a high resolution and still update faster. Due to that, we will get a huge performance increase.

    Let's say you have `BinWidth 10`, all frequencies will have this resolution. Which makes values update faster and have less CPU usage.<br/>
    But then, if you set `CascadesCount` to 4 or 5, now you will have a high resolution in low frequencies, but high frequencies will still have <u>the same old resolution</u>, which is already high enough.<br/>

    Which means now low frequencies will have `BinWidth 2.5` (`BinWidth 10 / CascadesCount 4`).
    And high frequencies will still have `BinWidth 10`.

    But you won't see this improvement unless you used `BandCascadeTransformer` handler, we will talk about it later.

    </details>

  - `WindowFunction`: Let's us use a window function to make FFT results look better. We will set it to `Hann`.

```ini
Handler-MainFFT=Type FFT | BinWidth 10 | OverlapBoost 6 | CascadesCount 4 | WindowFunction Hann
```

---

- `MainBR`: Handler of type `BandResampler`, the source of this handler must be of type FFT.

  While you can use FFT handler without `BandResampler`, it's not very useful on it's own. `BandResampler` provides additional functionalities such as specifying how many bands you want and the exact frequency range you want.<br/>

  Also it can use [CubicInterpolation](/docs/handler-types/fft/band-resampler?id=cubic-interpolation), which makes bands transition smoother from the band with highest value to the band with lowest value.<br/>

  The parameters we will use are:

  - `Bands`: We will use linear method, with 120 bands, 20 FreqMin, 2000 FreqMax.

  - `CubicInterpolation`: We will set it to `true`, it's true by default but let's keep it there for clarity.

```ini
Handler-MainBR=Type BandResampler | Bands Linear(Count 120, FreqMin 20, FreqMax 2000) | CubicInterpolation true
```

---

- `MainBCT`: Handler of type `BandCascadeTransformer`, the source of this handler must be of type BandResampler.

  This handler allows you to combine several cascades into one set of final values. Which means we can have a detailed low frequencies, and combine them with the already detailed high frequencies.

  <details><summary>More infos about this handler:</summary>

  While now we are happy with having a detailed results through out the entire visualization, low frequencies will still update slower than high frequencies, actually they will be more slower than how they actually were, due to the increase in resolution.

  So what to do about that? simply let `OverlapBoost` take care of it, that's why we set it to `6` at the beginning. It will make all frequencies look like they are updating relatively faster.

  But now we have another problem, high frequencies update rate will look extremely faster, but that can be easily fixed, we will use another handler called `TimeResampler`, it has a parameter which let's us control the data flow. Which means, no matter how fast high frequencies are updating, we still can sync them with the low ones.

  And don't worry, it doesn't affect the performance at all, actually [FFT Cascades](/docs/discussions/fft-cascades.md) solution was proposed to fix these issues, an it done it surprisingly well (no need to crank up the FFT resolution and overlap anymore).

  </details>

  The parameters we are going to use are:

  - `MixFunction`: We will set it to `Product`.
  - `MinWeight`: We will set it to `0.01`.
  - `TargetWeight`: We will set it to `2`.

  You can read about these parameters [here](/docs/handler-types/fft/band-cascade-transformer.md).

```ini
Handler-MainBCT=Type BandCascadeTransformer | MixFunction Product | MinWeight 0.01 | TargetWeight 2
```

---

- `MainTR`: Handler of type `TimeResampler`, this handler will help us to filter out the results, since it has `Transform` parameter, we can target a specific decibels range (below `-27` to visualize loud "sounds" (not "frequencies"), above `-30` or `-40` to visualize both loud and quite sounds as well).

  Also it has parameters similar to AudioLevel `FFTAttack` and `FFTDecay`, so we can use them to make values transition smoother.

  ?>Note that this handler applies transformation <u>After</u> applying other parameters (`Attack`, `Decay`, etc), and not before them. This may result in a slight change in output values.

  But there is a parameter called `UpdateRate`, you remember that we have high frequencies that always updating faster than low frequencies right? this parameter will fix that issue for us.

  Simply, instead of outputting every value as soon as its handler provide it, we can get `UpdateRate` amount of values every second.

  This way, as long as we use the right settings, update rate will not matter in low/high frequencies or even when using large resolution in the FFT handler itself.<br/>
  Even if values are updating at incredibly low rate, using `Attack` and `Decay` parameters will make it look smoother and more natural.

  ?>To understand more what we did in the `Transform` parameter, please refer to [this discussion](/docs/discussions/transforms.md).

```ini
Handler-MainTR=Type TimeResampler | Attack 30 | Decay 80 | UpdateRate ([#UpdateRate]*2) | Transform dB, Map(From -51 : -0, to 5 : 100), Clamp(to 5 : 100)
; What we did in Transform parameter is the following:
; Step 1: Convert the signal to decibels
; Step 2: Select a specific range of loudness (similar to AudioLevel Sensitivity), and map it to a value between 5 and 100
; Step 3: Even though we mapped the value to a specfic range, it can go below 5, since we are still dealing with decibels
;         So we use Clamp to explicitly make 5 the minimum, and 100 the maximum

; We want child measures to have a value between 5 and 100 so we can use it for the height of shape meters
; Because instead of doing the math ourselves to convert [0, 1] range to the number we actually want, this plugin made it a looot easier
```

---

- `MainFinalOutput`: Handler of type `UniformBlur`, we named it like that to make it clear that this is the handler that will provide the values we want for child measures.<br/>
  Because child measures can get a value from any handler in the chain (`FFT`, `BandResampler`, `BandCascadeTransformer`, `TimeResampler` or `UniformBlur`).

  This handler will allow us to smooth values between bands.<br/>
  `Radius` parameter let's us control how smooth or how much the values will blend between bands.

```ini
Handler-MainFinalOutput=Type UniformBlur | Radius 2.2
```

Now the parent measure is ready :tada:

Btw, let's use variables instead of hard-coded values so it becomes easier to use and change:

```ini
Handler-MainFFT=Type FFT | BinWidth [#BinWidth] | OverlapBoost [#OverlapBoost] | CascadesCount [#CascadesCount] | WindowFunction Hann
; --------------------------------------------------------------------------------------
Handler-MainBR=Type BandResampler | Bands Linear(Count [#Bands], FreqMin [#FreqMin], FreqMax [#FreqMax]) | CubicInterpolation true
; --------------------------------------------------------------------------------------
Handler-MainBCT=Type BandCascadeTransformer | MixFunction Product | MinWeight 0.01 | TargetWeight 2 | ZeroLevelMultiplier 1
; --------------------------------------------------------------------------------------
Handler-MainTR=Type TimeResampler | Attack [#Attack] | Decay [#Decay] | UpdateRate ([#UpdateRate]*2) | Transform dB, Map(From -([#Sensitivity]) : -0, to [#MinHeight] : [#MaxHeight]), Clamp(to [#MinHeight] : [#MaxHeight])
; --------------------------------------------------------------------------------------
Handler-MainFinalOutput=Type UniformBlur | Radius [#BlurRadius]
```

Variables file:

```ini
[Variables]
BarWidth=5
BarsGab=0.2
; ------------
MaxHeight=100
Color=210,210,230,230
; ------------
FreqMin=20
FreqMax=2000
Bands=120
; ------------
Sensitivity=51
Attack=30
Decay=80
; ------------
BinWidth=10
OverlapBoost=6
CascadesCount=4
; ------------
BlurRadius=1
```

Now let's make the child measures.<br/>

We will create them as we normally do, except this time each band have will an index starting from `0` to `Bands-1`.

?>The only handler that provides an index range for child measures is FFT and the handlers that are using it as a source.

```ini
[MeasureBand0]
Measure=Plugin
Plugin=AudioAnalyzer
Parent=MeasureAudio
Type=Child
Index=0
Channel=Auto
HandlerName=MainFinalOutput
```

From here we are just going to create a measure for each band, we provided a lua script that can help you to generate bands quickly:

```lua
function Initialize()
  Bands = SELF:GetOption('BandsCount', 1)

-- FP stands for file path
  MeasureBandsFP  = SKIN:MakePathAbsolute(SKIN:ReplaceVariables("#@#Measures\\AudioAnalyzerBands.inc"))
  MeterSpectrumFP = SKIN:MakePathAbsolute(SKIN:ReplaceVariables("#@#Meters\\Spectrum\\AudioAnalyzer.inc"))

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
    MeasureBands:write("HandlerName=MainFinalOutput\n")
    MeasureBands:write("\n")
  end

  MeasureBands:close()
end

function GenerateMeterSpectrum(Bands)
  MeterSpectrum = io.open(MeterSpectrumFP, "w")

  MeterSpectrum:write("[MeterSpectrum]\n")
  MeterSpectrum:write("Meter=Shape\n")
  MeterSpectrum:write("X=0\n")
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
  Bands = Bands or 1 -- safety check
  GenerateMeasureBands(Bands)
  GenerateMeterSpectrum(Bands)
end
```

It will not just generate the bands, but will also make the shape meters to visualize them.<br/>
To use the script, simply make a measure of type Script, specify your options and you are good to go!

```ini
[BandsGenerator]
Measure=Script
ScriptFile=#@#Scripts/AudioAnalyzer.lua
BandsCount=#Bands#
Disabled=1
```

<video src="docs\usage-examples\resources\fft-spectrum.mp4" autoplay loop muted title="FFT Spectrum"></video>

?>In this example we only scratched the surface of what this plugin provides, so feel free to experiment with all the options.
