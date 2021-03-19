## Loudness meter

<img src="resources\loudness.PNG" title="Loudness" />

Digital loudness is always measured in decibels relative to full scale, or dBFS. Simply, this means that 0 dB is the loudest possible sound, -20 dB is something quieter, and -70 dB is something almost inaudible.

This skin shows something that roughly correlates with perceived loudness. Measuring real loudness is a very complex and challenging topic (and actually this can't be done digitally without special equipment). This skin uses an approximation, and in my opinion this approximation is good enough.

This skin displays both numeric value of current loudness and a bar that shows relative loudness, where empty bar indicates silence and full bar indicated a very loud sound.

To do this, it converts decibels in some range (particularly, in range from -50 dB to 0 dB) into range from 0.0 to 1.0 and clamps them to that range so that Bar meter can display it.

However, numeric values are not converted and not clamped, so they can show that there is some sound that is too quiet to be displayed on Mar meter.

?>Note that for loudness calculations there is a `Filter like-a` parameter specified. Without this parameter the values it displays would be very-very different from perceived loudness.

There is also a peak meter in the [.rmskin file](). It acts similar to loudness meter, except what it shows doesn't correlate with perceived loudness.

In sound industry, peak meters are usually used to detect possible clipping. It just a showcase that you can detect sound peaks, don't use it when you need loudness.

Note that for loudness calculations there is a no `Filter` parameter specified, which means that there is no filtering done on sound wave. If you were to specify some filter, then it wouldn't measure actual sound peaks anymore. It would measure peaks on some filtered values instead, which is probably not what you want.
