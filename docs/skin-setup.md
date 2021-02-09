## How to setup a skin

First of all, lets create a skin:

```ini
[Rainmeter]
Update=32
```

Simple skin with low update rate (`Update=32` = 30Fps). Low update rate is needed to make values update faster.

This is how you setup the plugin:

!> Note: all option names and properties here are case-insensitive. Which means `Option=Something` is equal to `oPTioN=soMThInG` . <br/> We will keep using Upper Case letter of each word just for convention.

We create a measure, and specify it as a parent.

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
Processing-Main=Channels auto | Handlers HandlerName | Filter like-a
```

a property may have more than one option, we can write multible comma-separated options. Like so:

```ini
Processing-Main=Channels Left, Right | Handlers HandlerName1, HandlerName2 | Filter like-a
```
