## Handler Types

There are to types of handlers:

- [Signal processors]().
- [Value manipulators]().

### Signal processors

These handler types take the audio data and extract a specific audio signal from it.

!>Note that first handler of any process must be a Signal processors.

```ini
Processing-Main=Channels Auto | Handlers Handler1, Handler2 | Filter Like-a
Handler-Handler1=Type FFT | SetOfOptions
; Or any other "Signal processor" type
Handler-Handler1=Type Loudness | SetOfOptions
Handler-Handler1=Type Peak | SetOfOptions

```

### Value manipulators

These handler types will apply transformation on that raw audio signal.

But what is a transformation?<br/>
It's a chain of math operations on a value, that change it.

_Description of this page is WIP, infos here may not be correct._
_I may even rewrite everything here._

But before we get into them, lets understand [what is a Handler](/docs/handler-types/what-is-a-handler.md).
