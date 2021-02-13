## Section Variables

You can get properties of handlers and information about parent measure using section variable.

Syntax is like the following:

```ini
Variable=[&ParentMeasureName:Resolve(FirstArgument, SecondArgument)]
```

_Variable here is used as an example, you can use Section Variables directly anywhere in your skin or even inside a Lua script. See [Tips and Code Snippets] discussion._

We will show you examples on how to use them, as well as which arguments are available.

## Usage

To illustrate this, we gonna make a simple measure:

```ini
[InfosLogger]
Measure=Calc
Formula=0
UpdateDivider=-1
; UpdateDivider=-1 will make this measure update only when the skin is loaded or refreshed
DynamicVariables=1
OnUpdateAction=[!Delay 1500][!Log "[&MeasureAudio:Resolve(Current Device, Name)]"]
; Delay is needed, sometimes infos take a bit of time to be retrieved
```

The example above will log the Audio device name in [Rainmeter Logs window]() every time you load or refresh the skin.

The Resolve Function (Function?) takes 2 arguments:

- `FirstArgument`: (?, sorry i can't find an example :c )
  - `SecondArgument`: Is what infos you want to know about the `FirstArgument`.

## Available Arguments

?> Notice, the arguments are documented in a bullet list style:

- `ArgumentA`: _Description._
  - `ArgumentB`: _Description._

You will use these arguments like like so: `[&ParentMeasure:Resolve(ArgumentA, ArgumentB)]`

---

- `Current Device`: Information about the current audio device.

  _Should i say "makes the child measure return/give 'something', otherwise 'something else'?_

  - `Status`: Gives(?, gives, returns, provide, which one fits more here?, related to the note above) 1 if everything works, 0 otherwise.
  - `Status String`: Same as `Status`, but instead of giving 0 and 1, it gives 'Active' and 'Down'.
  - `DetailedState`(2 words without spaces): Gives the following based on the condition:
    - `1`: If everything works.
    - `2`: If there were some unknown connection error.
    - `3`: If device was disconnected for some reason (for example, invalid options on parent measure).
    - `4`: If device operates in [exclusive mode]() right now.
  - ``:
  - ``:

- ``:

  - ``:

- ``:

  - ``:

- ``:
  - ``:
