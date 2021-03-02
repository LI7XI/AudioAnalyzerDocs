## FFT Cascades

Fourier transform is a mathematical transform that takes a sound wave and tells you which frequencies this wave consists of.

This has many applications, but for this discussion the important part is that it can be used to create fancy images or spectrum visualizers that respond to sounds you computer is producing.

This plugin uses FFT (Fast Fourier Transform) algorithm, and just to be short I will write FFT even when I should have probably written Fourier transform.

FFT has a fundamental math issue: you are trading frequency resolution for time resolution. You can have either a very detailed result that is updating very slowly, or a very fast result that is not detailed at all, or something in between.

That would not be a problem if not for the fact that humans have logarithmic frequency resolution: we can easily distinguish 100 Hz and 150 Hz, but good luck trying distinguish 10000 Hz and 10050 Hz.

So while low resolution in high frequencies is not a problem, low resolution in low frequencies is very noticeable. But FFT have a uniform frequency resolution across the whole frequency range.

To get high resolution you need an FFT of big size, and FFT with a big size need a lot of audio data, which flows at constant rate, so big FFTs update slowly.

There is a method of boosting FFT speed: overlapping. Why wait for the whole new big chunk of data when you can reuse old data and update results faster? Well, yes, but that also increases CPU load.

You may be thinking that maybe you could just go to you audio card settings and change Sampling Rate from cheap 44100 to glorious 192000 or even godlike 384000? There will be more audio data points, so big FFT will be updating faster? Well, no. It will be updating faster, but it will have terrible frequency resolution.

Total resolution will be fine, but most of the resulting data now will describe only very high frequencies, while we mostly care about low frequencies. And to get low frequencies resolution back we will need to increase FFT size even more, which will again make it slow. There is no point in high sample rate. Well, I won't argue where it is useful for some other tasks, but there is no point for FFT.

Speaking of increasing the resolution. FFT also have a performance concerns.

FFT has a complexity of `N*log(N)`<small id="i1">[1](#q)</small>. Also, if we need to process a constant time of audio, then complexity is proportional to the time of that data.
Let's say we have an FFT that updates 10 times per second, and over a minute of audio it consumes R1 amount of CPU time.

If we increase FFT size 10 times, it will have much better resolution, but also complexity of one FFT will increase 10\*log(10) times. However, it will only update 1 time per second, so 10 times less computations, so the actual increase in complexity is only log(10).

But now we have an FFT that updates only 1 time per second, which just looks kinda ugly. So we can use overlapping, and boost it 10 times, so that this FFT will still update 10 times per second, but now it will actually have that 10\*log(10) times CPU time consumed.

Also, while overlapping increases update rate, it doesn't lower latency. When your FFT updates 10 times per second, average time between hearing a sound and getting that sound on FFT is 50 ms. With FFT 10 times slow, no matter how fast it is updating, you will still wait about half a second before FFT actually shows that sound.

Complexity is a different story with changes in sample rate.<br/>
Lower sample rate is better in that regard. Period. The only requirement is to have sample rate twice as big as the maximum frequencies that you want to analyze.

So you are a human like me, so you only care about frequencies below 20KHz, then sample rate of 44100 Hz is more than enough for your FFT needs. That's why AudioAnalyzer have a default TargetRate option at 44100.

When I developed this plugin, I proposed a solution to FFT time-frequency issue: cascaded FFT.<br/>
We can't have both high time and frequency resolution in low frequencies but we can have it in high frequencies. So why not take small FFT for high frequencies and big FFT for low frequencies, and then combine them?

It's not ideal, but it's better than nothing. Moreover, internal optimizations of sampling rate allow for quite good complexity too.

If one singe FFT has size N and complexity O(FFT), and you are using T cascades, then my method:

1. Have effective FFT size `N * (2 ^ T)`.
2. Have average complexity less than `2 * O(FFT)`.
3. Have worst case complexity `T * O(FFT)`.

FFT cascades introduce some artifacts on the image caused by slowly updating cascades in low frequencies, but I would say that it still looks much better than a simple classic FFT.

## Documentation Questions <i id="q">

[Q1](#i1): Even though i've read about Big O notation many times, i still don't get it, is there a less precise but more understandable way to explain the concept? (i mean in the places where you mentioned it).<br/>
Q2: Now after we understand how FFT cascades work, how to use this knowledge? is it related to BandCascadeTransformer?

</i>
