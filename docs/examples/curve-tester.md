## Curve Tester

<div><video src="\docs\examples\resources\curve-tester.mp4" autoplay loop muted title="Curve Tester"></div>

A simple tester to show you how different handler chains affect values.

Orange line shows raw RMS value.<br/>
Green line shows RMS values converted to decibels. Its purpose is to show that you should always convert your values to decibels, because orange line only reacts to very strong sound.

There are quiet sound that you can still clearly hear, and which are you can see on green line but can not see on orange line. If you were to just ramp up value of RMS then it would show you quiet sounds but then loud sounds would just clip on the upper edge of the graph.

There are also blue and white lines. Their purpose is to show that order of handlers matter. Blue line shows RMS values that were first converted into decibels and then filtered/smoothed. White line shows values that were first filtered/smoothed and then converted into decibels. As you can see, the difference is very noticeable. It's up to you to decide which way of calculations suits you better.
