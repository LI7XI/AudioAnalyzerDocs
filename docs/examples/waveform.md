## Waveform

<div><video src="docs/examples/resources/waveform.mp4" autoplay loop muted title="Waveform"></video></div>

This plugin can draw the waveform of an audio signal.

On each skin `Update` cycle, the plugin will generate an image and write it to local drive (it is optimized not to write when there are no changes), so that rainmeter can read it from disk to display it.

You can see where is the problem here, it's your hard drive lifespan. The issue is that rainmeter doesn't support in-memory image-transfer.

For example instead of reading/writing to disk, rainmeter could read and display the image directly from RAM, that would be way faster and significantly better than writing then reading from disk, because doing that for lets say 30 times per second will decrease your drive lifespan by a large margin.

A temporary solution would be to create a small RAM-drive (in case you have an SSD), and then making the plugin use that location to output the image using [Folder](/docs/handler-types/waveform?id=folder) parameter. It's not ideal, but this is what we have until rainmeter api start supporting in-memory image-transfer.

If you are a C++ developer and you are familiar with rainmeter API maybe you can look into this issue and discuss how to fix it with rainmeter team.
