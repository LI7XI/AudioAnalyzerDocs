## Curve Tester

<div><video src="docs/examples/resources/curve-tester.mp4" autoplay loop muted title="Curve Tester"></div>

A simple tester to show you how different handler chains affect values.

<span style="color: #ec9a53" >Orange</span> line shows raw RMS value.<br/>
<span style="color: #64de78" >Green</span> line shows RMS values converted to decibels. Its purpose is to show that you should always convert your values to decibels, because orange line only reacts to very strong sound.

There are quiet sound that you can still clearly hear, and which are you can see on green line but can not see on orange line. If you were to just ramp up value of RMS then it would show you quiet sounds but then loud sounds would just clip on the upper edge of the graph.

There are also <span style="color: #88b8ff" >blue</span> and <span style="color: #fff" >white</span> lines. Their purpose is to show that order of handlers matter. Blue line shows RMS values that were first converted into decibels and then filtered/smoothed. White line shows values that were first filtered/smoothed and then converted into decibels. As you can see, there are some differences. It's up to you to decide which way of calculations suits you better.

Check out how this skin was made [here](/docs/usage-examples/curve-tester.md)
