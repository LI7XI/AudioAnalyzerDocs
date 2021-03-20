## Plugin structure

First of all, this plugin contains a lot of meaningful error and warning messages. When you are writing a skin, have a Rainmeter log window open. If you have made some mistake with syntax, there is a good chance that log will have a message about it. It's very helpful.

This plugin doesn't have a fixed set of possible ways to calculate some values. Instead, it acts somewhat like a DSP-utility and provides you a set of building blocks called [Sound Handlers](/docs/handler-types/handler-types.md) as we saw [earlier](/docs/skin-setup.md) that may be combined in any amount into any tree-like graph.

?>Similar to AudioLevel, this plugin follows Parent Child paradigm.

### How to determine the measure Type?

Parent measures are distinguished from Child measures by `Type` option, which must be either `Parent` or `Child`.

```ini
Type=Parent
```

Or

```ini
Type=Child
```

## Using Math

This plugin supports math. In every place where number (either Float or Integer) is expected you can you math operations to calculate it.

Supported operations are `+ - * / ^ `, parentheses are allowed, all numbers are calculated as a floating point. If you try to divide something by zero, result will be replaced with 0.<br/>
For example, you can write `(5*10^2 + 10)*0.7` instead of `357`.

## Automatic Reconfiguring

If you want your skin to react to audio device properties, this plugin provides you with some information.

For example, there is a section variable called `Device List Output` that will give you a list of available audio devices, that you can parse with a Lua script, and then somehow show user a list of devices to choose from. We will go through that in [Tips](/tips-code.md) discussion.

Of course there is a `Current Device` or `Channels` section variable that will give you a list of available audio channels.

See [Section Variables](/docs/section-vars.md) discussion.
